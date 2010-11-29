#include "GetSurroundingBox_BasicMesh.h"
#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplay.h"
#include "MathBasicVec.h"
#include "CudaMetil.h"

#define NB_PIX_RASTER_BOX 32
#define NB_BLOCKS_FOR_ELEM_COUNT 32
#define MAX_WH ( 1600 * 1200 )
#define NB_THREADS_FOR_RASTER 64
#define NB_THREADS_FOR_PROJ 64

BEG_METIL_NAMESPACE;

typedef DisplayTrans::T3 T3;
typedef DisplayTrans::T T;

DisplayItem_BasicMesh::DisplayItem_BasicMesh( Ps<BasicMesh_Compacted> mesh ) : mesh( mesh ) {
    for( int d = 0; d < 3; ++d )
        proj[ d ] = 0;

    size_elem_count = 0;
    elem_count_gpu = 0;

    size_elem_data = 0;
    elem_data_gpu = 0;

    num_coloring_field = -1;
    dim_coloring_field = 0;
}

DisplayItem_BasicMesh::~DisplayItem_BasicMesh() {
    for( int d = 0; d < 3; ++d )
        cudaFree( proj[ d ] );
    cudaFree( elem_count_gpu );
    cudaFree( elem_data_gpu  );
}

__inline__ ST rese_elem_count_for_one_group( int sb ) {
    return ( NB_BLOCKS_FOR_ELEM_COUNT + 1 ) * sb + 1 /*offset list needs n + 1 terms...*/;
}

unsigned *DisplayItem_BasicMesh::get_elem_count_gpu_ptr( ST nb_types, int sb ) {
    int needed_size = nb_types * rese_elem_count_for_one_group( sb ) + 1 /*size for total nb elements*/;
    if ( size_elem_count < needed_size ) {
        if ( elem_count_gpu )
            cudaFree( elem_count_gpu );
        CSC( cudaMalloc( &elem_count_gpu, sizeof( unsigned ) * needed_size ) );
        size_elem_count = needed_size;
    }
    return elem_count_gpu;
}

int *DisplayItem_BasicMesh::get_elem_data_gpu_ptr( ST needed_size ) {
    if ( size_elem_data < needed_size ) {
        needed_size = needed_size * 8 / 7;
        if ( elem_data_gpu )
            cudaFree( elem_data_gpu );
        CSC( cudaMalloc( &elem_data_gpu, sizeof( int ) * needed_size ) );
        size_elem_data = needed_size;
    }
    return elem_data_gpu;
}

void DisplayItem_BasicMesh::update_p_min_p_max( GenericDisplay *display, T3 &p_min, T3 &p_max, bool use_trans ) {
    T3 t_min;
    T3 t_max;
    get_surrounding_box( t_min.ptr(), t_max.ptr(), mesh.ptr(), use_trans ? display->get_trans_gpu() : 0, display->get_w(), display->get_h() );
    for( int i = 0; i < 3; ++i ) {
        p_min[ i ] = min( p_min[ i ], t_min[ i ] );
        p_max[ i ] = max( p_max[ i ], t_max[ i ] );
    }
}

void DisplayItem_BasicMesh::set_coloring_field( int n, T mi, T ma, int dimension ) {
    num_coloring_field = n;
    dim_coloring_field = dimension;
    min_coloring_field = mi;
    max_coloring_field = ma;
}


__global__
void make_proj_kernel( T *x, T *y, T *z, const DisplayTrans *trans_ptr, int w, int h, BasicMesh_Compacted *m ) {
    DisplayTrans::Buf trans = trans_ptr->make_buf( w, h );

    int n = blockIdx.x * NB_THREADS_FOR_PROJ + threadIdx.x;
    if ( n < m->pos_nodes[ 0 ].size() ) {
        const T *n_x = m->pos_nodes[ 0 ].ptr();
        const T *n_y = m->pos_nodes[ 1 ].ptr();
        const T *n_z = m->pos_nodes[ 2 ].ptr();

        T3 B = trans.proj( T3( n_x[ n ], n_y[ n ], n_z[ n ] ) );

        x[ n ] = round( B[ 0 ] );
        y[ n ] = round( B[ 1 ] );
        z[ n ] = B[ 2 ];
    }
}

__global__
void make_elem_count_kernel( unsigned *elem_count, int wb, int hb, int sb, const BasicMesh_Compacted *m, const T *n_x, const T *n_y ) {
    elem_count += blockIdx.x * sb;

    for( int num_type = 0; num_type < m->elem_groups.size(); ++num_type, elem_count += rese_elem_count_for_one_group( sb ) ) {
        __shared__ unsigned local_count[ MAX_WH / NB_PIX_RASTER_BOX / NB_PIX_RASTER_BOX ];
        for( int i = threadIdx.x; i < sb; i += blockDim.x )
            local_count[ i ] = 0;
        __syncthreads(); //wait until local_count is ok

        int nb_elem = m->elem_groups[ num_type ].connec[ 0 ].size();
        const int *c_0 = m->elem_groups[ num_type ].connec[ 0 ].ptr();
        const int *c_1 = m->elem_groups[ num_type ].connec[ 1 ].ptr();
        const int *c_2 = m->elem_groups[ num_type ].connec[ 2 ].ptr();

        int be = ( blockIdx.x + 0 ) * nb_elem / gridDim.x;
        int ee = ( blockIdx.x + 1 ) * nb_elem / gridDim.x;

        for( int i = be + threadIdx.x; i < ee; i += blockDim.x ) {
            int n_0 = c_0[ i ];
            int n_1 = c_1[ i ];
            int n_2 = c_2[ i ];

            T x_0 = n_x[ n_0 ], y_0 = n_y[ n_0 ];
            T x_1 = n_x[ n_1 ], y_1 = n_y[ n_1 ];
            T x_2 = n_x[ n_2 ], y_2 = n_y[ n_2 ];

            int x_m = int( min( min( x_0, x_1 ), x_2 ) ) / NB_PIX_RASTER_BOX;
            int y_m = int( min( min( y_0, y_1 ), y_2 ) ) / NB_PIX_RASTER_BOX;

            int x_M = int( max( max( x_0, x_1 ), x_2 ) ) / NB_PIX_RASTER_BOX;
            int y_M = int( max( max( y_0, y_1 ), y_2 ) ) / NB_PIX_RASTER_BOX;

            for( int yb = max( 0, y_m ); yb <= min( hb - 1, y_M ); ++yb )
                for( int xb = max( 0, x_m ); xb <= min( wb - 1, x_M ); ++xb )
                    atomicAdd( local_count + wb * yb + xb, 1 );
        }

        // copy local count in global memory
        __syncthreads();
        for( int i = threadIdx.x; i < sb; i += blockDim.x )
            elem_count[ i ] = local_count[ i ];
    }
}


__global__
void make_sum_elem_count_kernel( unsigned *elem_count, int wb, int hb, int nb_types ) {
    int sb = wb * hb;
    for( int num_type = 0; num_type < nb_types; ++num_type, elem_count += rese_elem_count_for_one_group( sb ) ) {
        int n = blockIdx.x * blockDim.x + threadIdx.x;
        if ( n < sb ) {
            unsigned acc = 0;
            for( int i = n; i < sb * NB_BLOCKS_FOR_ELEM_COUNT; i += sb ) {
                unsigned val = elem_count[ i ];
                elem_count[ i ] = acc;
                acc += val;
            }
            elem_count[ sb * NB_BLOCKS_FOR_ELEM_COUNT + n ] = acc;
        }
    }
}

// elem_count will be a list of offset. total number of elements is stored at the end of elem_count
__global__
void make_off_elem_count_kernel( unsigned *elem_count, int wb, int hb, int nb_types ) {
    int sb = wb * hb;
    int offset = sb * NB_BLOCKS_FOR_ELEM_COUNT;

    unsigned acc = 0;
    for( int num_type = 0; num_type < nb_types; ++num_type, elem_count += rese_elem_count_for_one_group( sb ) ) {
        for( int i = 0; i < sb; ++i ) {
            unsigned val = elem_count[ offset + i ];
            elem_count[ offset + i ] = acc;
            acc += val;
        }
        elem_count[ offset + sb ] = acc;
    }

    *elem_count = acc;
}

///
__global__
void make_elem_data_kernel( unsigned *elem_count, int *elem_data, const DisplayTrans *trans_ptr, int wb, int hb, int sb, BasicMesh_Compacted *m, const T *n_x, const T *n_y ) {
    __shared__ unsigned local_count[ MAX_WH / NB_PIX_RASTER_BOX / NB_PIX_RASTER_BOX ];

    // int size_for_1t = ( NB_BLOCKS_FOR_ELEM_COUNT + 1 ) * sb + 1;
    for( int num_type = 0; num_type < m->elem_groups.size(); ++num_type, elem_count += rese_elem_count_for_one_group( sb ) ) {
        __syncthreads();
        for( int i = threadIdx.x; i < sb; i += blockDim.x )
            local_count[ i ] = elem_count[ NB_BLOCKS_FOR_ELEM_COUNT * sb + i ] + elem_count[ blockIdx.x * sb + i ];

        int nb_elem = m->elem_groups[ num_type ].connec[ 0 ].size();
        const int *c_0 = m->elem_groups[ num_type ].connec[ 0 ].ptr();
        const int *c_1 = m->elem_groups[ num_type ].connec[ 1 ].ptr();
        const int *c_2 = m->elem_groups[ num_type ].connec[ 2 ].ptr();

        int be = ( blockIdx.x + 0 ) * nb_elem / gridDim.x;
        int ee = ( blockIdx.x + 1 ) * nb_elem / gridDim.x;

        __syncthreads();
        for( int i = be + threadIdx.x; i < ee; i += blockDim.x ) {
            int n_0 = c_0[ i ];
            int n_1 = c_1[ i ];
            int n_2 = c_2[ i ];

            T x_0 = n_x[ n_0 ], y_0 = n_y[ n_0 ];
            T x_1 = n_x[ n_1 ], y_1 = n_y[ n_1 ];
            T x_2 = n_x[ n_2 ], y_2 = n_y[ n_2 ];

            int x_m = int( min( min( x_0, x_1 ), x_2 ) ) / NB_PIX_RASTER_BOX;
            int y_m = int( min( min( y_0, y_1 ), y_2 ) ) / NB_PIX_RASTER_BOX;

            int x_M = int( max( max( x_0, x_1 ), x_2 ) ) / NB_PIX_RASTER_BOX;
            int y_M = int( max( max( y_0, y_1 ), y_2 ) ) / NB_PIX_RASTER_BOX;

            for( int yb = max( 0, y_m ); yb <= min( hb - 1, y_M ); ++yb ) {
                for( int xb = max( 0, x_m ); xb <= min( wb - 1, x_M ); ++xb ) {
                    unsigned index = atomicAdd( local_count + wb * yb + xb, 1 );
                    elem_data[ index + 0 ] = i;
                }
            }
        }
    }
}

__global__
void DisplayItem_BasicMesh_render_kernel( unsigned *img, const unsigned *elem_count, int w, int h, int wb, int hb ) {
    int sb = wb * hb;
    elem_count += sb;
    for( int y = 0; y < h; ++y )
        for( int x = 0; x < w; ++x )
            img[ y * w + x ] = 0xFF000000 + elem_count[ y / NB_PIX_RASTER_BOX * wb + x / NB_PIX_RASTER_BOX ] * 25;
}

__inline__
unsigned shader( float z_n, float c ) {
    if ( z_n < 0 or z_n > 1 ) {
        int r = 200 * c;
        int g = r;
        int b = r;
        int a = 255;
        return ( r << 0 ) + ( g << 8 ) + ( b << 16 ) + ( a << 24 );
    }
    int r = ( z_n * 255 ) * c;
    int g = ( 0         ) * c;
    int b = ( 255 - r   ) * c;
    int a = 255;
    return ( r << 0 ) + ( g << 8 ) + ( b << 16 ) + ( a << 24 );
}

///// use 2 unsigned to store a T ( 2 because of tha alpha chanel that must be == 0xFF )
//__inline__ void copy_T_as_I( unsigned *res, float src ) {
//    int e, s = src < 0;
//    unsigned m = abs( frexpf( src, &e ) * 0x01000000 );
//    res[ 0 ] = 0xFF000000 + m;
//    res[ 1 ] = 0xFF000000 + ( s << 16 ) + ( e + 32768 );
//}

__global__
void raster_gpu_kernel( unsigned *rgba, unsigned *zznv, unsigned *nnnn, int wb, int hb, int sb, int w, int h, const unsigned *elem_offsets, const int *elem_data, const BasicMesh_Compacted *m, const T *n_x, const T *n_y, const T *n_z, float z_min, float z_mul, bool first_item,
                       float min_coloring_field, float max_coloring_field, int num_coloring_field, int dim_coloring_field ) {
    int bx = blockIdx.x * NB_PIX_RASTER_BOX;
    int by = blockIdx.y * NB_PIX_RASTER_BOX;

    // initialization of the z buffer
    __shared__ unsigned rgba_buffer[ NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX ];
    __shared__ unsigned zznv_buffer[ NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX ];
    __shared__ unsigned nnnn_buffer[ NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX ];
    if ( first_item ) {
        for( int i = threadIdx.x; i < NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX; i += NB_THREADS_FOR_RASTER ) {
            rgba_buffer[ i ] = 0x00000000;
            zznv_buffer[ i ] = 0xFFFFFFFF;
            nnnn_buffer[ i ] = 0xFFFFFFFF;
        }
    } else {
        for( int i = threadIdx.x; i < NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX; i += NB_THREADS_FOR_RASTER ) {
            int x = bx + i % NB_PIX_RASTER_BOX;
            int y = by + i / NB_PIX_RASTER_BOX;
            if ( x < w and y < h ) {
                rgba_buffer[ i ] = rgba[ w * y + x ];
                zznv_buffer[ i ] = zznv[ w * y + x ];
                nnnn_buffer[ i ] = nnnn[ w * y + x ];
            }
        }
    }

    const float *n_v = num_coloring_field >= 0 ? m->nodal_fields[ num_coloring_field ].data[ dim_coloring_field ].ptr() : 0;

    int size_for_1t = ( NB_BLOCKS_FOR_ELEM_COUNT + 1 ) * sb + 1;
    for( int num_type = 0; num_type < m->elem_groups.size(); ++num_type, elem_offsets += size_for_1t ) {
        const int *c_0 = m->elem_groups[ num_type ].connec[ 0 ].ptr();
        const int *c_1 = m->elem_groups[ num_type ].connec[ 1 ].ptr();
        const int *c_2 = m->elem_groups[ num_type ].connec[ 2 ].ptr();

        // swwep elem list
        __syncthreads(); //wait until z_buffer is ok
        unsigned beg_elem = elem_offsets[ wb * blockIdx.y + blockIdx.x + 0 ];
        unsigned end_elem = elem_offsets[ wb * blockIdx.y + blockIdx.x + 1 ];
        for( int num_elem = beg_elem + threadIdx.x; num_elem < end_elem; num_elem += NB_THREADS_FOR_RASTER ) {
            int ind_elem = elem_data[ num_elem ];

            int n_0 = c_0[ ind_elem ];
            int n_1 = c_1[ ind_elem ];
            int n_2 = c_2[ ind_elem ];

            T x_0 = n_x[ n_0 ] - bx, y_0 = n_y[ n_0 ] - by, z_0 = n_z[ n_0 ], v_0 = -1;
            T x_1 = n_x[ n_1 ] - bx, y_1 = n_y[ n_1 ] - by, z_1 = n_z[ n_1 ], v_1 = -1;
            T x_2 = n_x[ n_2 ] - bx, y_2 = n_y[ n_2 ] - by, z_2 = n_z[ n_2 ], v_2 = -1;

            if ( n_v ) {
                T d = 1.0 / ( max_coloring_field - min_coloring_field );
                v_0 = ( n_v[ n_0 ] - min_coloring_field ) * d;
                v_1 = ( n_v[ n_1 ] - min_coloring_field ) * d;
                v_2 = ( n_v[ n_2 ] - min_coloring_field ) * d;
            }

            T3 normal = normalized( cross( T3( x_1, y_1, z_1 ) - T3( x_0, y_0, z_0 ), T3( x_2, y_2, z_2 ) - T3( x_0, y_0, z_0 ) ) );

            // sort points and values by y
            if ( y_0 > y_1 ) { swap( x_0, x_1 ); swap( y_0, y_1 ); swap( z_0, z_1 ); swap( v_0, v_1 ); }
            if ( y_0 > y_2 ) { swap( x_0, x_2 ); swap( y_0, y_2 ); swap( z_0, z_2 ); swap( v_0, v_2 ); }
            if ( y_1 > y_2 ) { swap( x_1, x_2 ); swap( y_1, y_2 ); swap( z_1, z_2 ); swap( v_1, v_2 ); }

            int dx_01 = x_1 - x_0, dy_01 = y_1 - y_0; float dz_01 = z_1 - z_0, dv_01 = v_1 - v_0;
            int dx_02 = x_2 - x_0, dy_02 = y_2 - y_0; float dz_02 = z_2 - z_0, dv_02 = v_2 - v_0;

            float cx_0 = dx_01 / float( dy_01 + not dy_01 ), cz_0 = dz_01 / float( dy_01 + not dy_01 ), cv_0 = dv_01 / float( dy_01 + not dy_01 );
            float cx_1 = dx_02 / float( dy_02 + not dy_02 ), cz_1 = dz_02 / float( dy_02 + not dy_02 ), cv_1 = dv_02 / float( dy_02 + not dy_02 );

            if ( cx_0 > cx_1 ) {
                swap( cx_0, cx_1 );
                swap( cz_0, cz_1 );
                swap( cv_0, cv_1 );
            }

            for( int y_b = max( 0, (int)y_0 ); y_b < min( NB_PIX_RASTER_BOX, (int)y_1 ); ++y_b ) {
                int xl_0 = x_0 + ( y_b - y_0 ) * cx_0;
                int xl_1 = x_0 + ( y_b - y_0 ) * cx_1;

                float zl_0 = z_0 + ( y_b - y_0 ) * cz_0;
                float zl_1 = z_0 + ( y_b - y_0 ) * cz_1;
                float vl_0 = v_0 + ( y_b - y_0 ) * cv_0;
                float vl_1 = v_0 + ( y_b - y_0 ) * cv_1;
                float c_z = xl_1 - xl_0; c_z = ( zl_1 - zl_0 ) / ( c_z + not c_z );
                float c_v = xl_1 - xl_0; c_v = ( vl_1 - vl_0 ) / ( c_v + not c_v );

                for( int x_b = max( 0, xl_0 ); x_b < min( NB_PIX_RASTER_BOX, xl_1 + 1 ); ++x_b ) {
                    float z_b = zl_0 + ( x_b - xl_0 ) * c_z;
                    unsigned z_bi = z_mul * ( z_b - z_min );
                    unsigned z_re = atomicMin( zznv_buffer + NB_PIX_RASTER_BOX * y_b + x_b, z_bi );
                    if ( z_re > z_bi ) {
                        float v = vl_0 + ( x_b - xl_0 ) * c_v;
                        float n = normal[ 2 ]; // dot( normal, trans.eye_dir( x_b + bx, y_b + by ) );
                        // if ( n < 0 ) continue;
                        rgba_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = shader( v, abs( n ) ); // + ( ( 150 * ( x_b == xl_0 or x_b == xl_1 ) ) << 8 );
                        nnnn_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = ind_elem;
                    }
                }
            }

            int dx_21 = x_1 - x_2, dy_21 = y_1 - y_2; float dz_21 = z_1 - z_2, dv_21 = v_1 - v_2;
            int dx_22 = x_0 - x_2, dy_22 = y_0 - y_2; float dz_22 = z_0 - z_2, dv_22 = v_0 - v_2;

            float cx_2 = dx_21 / float( dy_21 + not dy_21 ), cz_2 = dz_21 / float( dy_21 + not dy_21 ), cv_2 = dv_21 / float( dy_21 + not dy_21 );
            float cx_3 = dx_22 / float( dy_22 + not dy_22 ), cz_3 = dz_22 / float( dy_22 + not dy_22 ), cv_3 = dv_22 / float( dy_22 + not dy_22 );
            if ( cx_2 < cx_3 ) {
                swap( cx_2, cx_3 );
                swap( cz_2, cz_3 );
                swap( cv_2, cv_3 );
            }

            for( int y_b = max( 0, (int)y_1 ); y_b < min( NB_PIX_RASTER_BOX, (int)y_2 + 1 ); ++y_b ) {
                int xl_0 = x_2 + ( y_b - y_2 ) * cx_2;
                int xl_1 = x_2 + ( y_b - y_2 ) * cx_3;

                float zl_0 = z_2 + ( y_b - y_2 ) * cz_2;
                float zl_1 = z_2 + ( y_b - y_2 ) * cz_3;
                float vl_0 = v_2 + ( y_b - y_2 ) * cv_2;
                float vl_1 = v_2 + ( y_b - y_2 ) * cv_3;
                float c_z = xl_1 - xl_0; c_z = ( zl_1 - zl_0 ) / ( c_z + not c_z );
                float c_v = xl_1 - xl_0; c_v = ( vl_1 - vl_0 ) / ( c_v + not c_v );

                for( int x_b = max( 0, xl_0 ); x_b < min( NB_PIX_RASTER_BOX, xl_1 + 1 ); ++x_b ) {
                    float z_b = zl_0 + ( x_b - xl_0 ) * c_z;
                    unsigned z_bi = z_mul * ( z_b - z_min );
                    unsigned z_re = atomicMin( zznv_buffer + NB_PIX_RASTER_BOX * y_b + x_b, z_bi );
                    if ( z_re > z_bi ) {
                        float v = vl_0 + ( x_b - xl_0 ) * c_v;
                        float n = normal[ 2 ]; // dot( normal, trans.eye_dir( x_b + bx, y_b + by ) );
                        // if ( n < 0 ) continue;
                        rgba_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = shader( v, abs( n ) ); // + ( ( 150 * ( x_b == xl_0 or x_b == xl_1 ) ) << 8 );
                        nnnn_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = ind_elem;
                    }
                }
            }
        }
    }

    // declare local_z_min / max
    __shared__ unsigned local_z_min[ NB_THREADS_FOR_RASTER ];
    __shared__ unsigned local_z_max[ NB_THREADS_FOR_RASTER ];
    local_z_min[ threadIdx.x ] = 0xFFFFFFFF;
    local_z_max[ threadIdx.x ] = 0;

    // save result in img
    __syncthreads();
    for( int i = threadIdx.x; i < NB_PIX_RASTER_BOX * NB_PIX_RASTER_BOX; i += NB_THREADS_FOR_RASTER ) {
        int ox = i % NB_PIX_RASTER_BOX;
        int oy = i / NB_PIX_RASTER_BOX;
        int x = bx + ox;
        int y = by + oy;

        if ( x < w and y < h ) {
            rgba[ w * y + x ] = rgba_buffer[ i ] + 50 * ( oy == 0 or ox == 0 );
            zznv[ w * y + x ] = 0xFF000000 + zznv_buffer[ i ];
            nnnn[ w * y + x ] = nnnn_buffer[ i ];
            //
            if ( zznv_buffer[ i ] != 0xFFFFFFFF ) {
                local_z_min[ threadIdx.x ] = min( local_z_min[ threadIdx.x ], zznv_buffer[ i ] );
                local_z_max[ threadIdx.x ] = max( local_z_max[ threadIdx.x ], zznv_buffer[ i ] );
            }
        }
    }

    // save z_min z_max
    for( int m = NB_THREADS_FOR_RASTER / 2; m; m /= 2 ) {
        __syncthreads();
        if ( threadIdx.x < m ) {
            local_z_min[ threadIdx.x ] = min( local_z_min[ threadIdx.x ], local_z_min[ threadIdx.x + m ] );
            local_z_max[ threadIdx.x ] = max( local_z_max[ threadIdx.x ], local_z_max[ threadIdx.x + m ] );
        }
    }
}

void DisplayItem_BasicMesh::render_to( BitmapDisplay *display ) {
    ASSERT( mesh.pos->is_a_gpu(), "render works only with data on gpu" );

    // get various data
    int w = display->get_w();
    int h = display->get_h();
    int wb = iDivUp( w, NB_PIX_RASTER_BOX );
    int hb = iDivUp( h, NB_PIX_RASTER_BOX );
    int sb = wb * hb;

    DisplayTrans *trans = display->get_trans_gpu();

    ST nb_types = 0;
    CSC(( cudaMemcpy( &nb_types, &mesh->elem_groups.size_, sizeof( ST ), cudaMemcpyDeviceToHost ) ));

    ST nb_nodes = 0;
    CSC(( cudaMemcpy( &nb_nodes, &mesh->pos_nodes.data_, sizeof( ST ), cudaMemcpyDeviceToHost ) ));
    CSC(( cudaMemcpy( &nb_nodes, &reinterpret_cast<const BasicVecRef<T> *>( nb_nodes )->size_, sizeof( ST ), cudaMemcpyDeviceToHost ) ));
    for( int d = 0; d < 3; ++d )
        if ( not proj[ d ] )
            cudaMalloc( proj + d, sizeof( T ) * nb_nodes );

    // make projection (integer values, stored in floating point numbers)
    CSC(( make_proj_kernel<<<iDivUp(nb_nodes,NB_THREADS_FOR_PROJ),NB_THREADS_FOR_PROJ>>>(
            proj[ 0 ], proj[ 1 ], proj[ 2 ], trans, w, h, mesh.ptr() ) ));

    // fill elem_count
    unsigned *elem_count = get_elem_count_gpu_ptr( nb_types, sb );
    CSC(( make_elem_count_kernel<<<NB_BLOCKS_FOR_ELEM_COUNT,128>>>( elem_count, wb, hb, sb, mesh.ptr(), proj[ 0 ], proj[ 1 ] ) ));
    CSC(( make_sum_elem_count_kernel<<<Metil::iDivUp(sb,64),64>>>( elem_count, wb, hb, nb_types ) ));
    CSC(( make_off_elem_count_kernel<<<1,1>>>( elem_count, wb, hb, nb_types ) ));

    // find size of elem_data list
    unsigned tot_nb_elems;
    CSC(( cudaMemcpy( &tot_nb_elems, elem_count + nb_types * rese_elem_count_for_one_group( sb ),
                      sizeof( unsigned ), cudaMemcpyDeviceToHost ) ));


    // fill elem_data
    int *elem_data = get_elem_data_gpu_ptr( tot_nb_elems );
    CSC(( make_elem_data_kernel<<<NB_BLOCKS_FOR_ELEM_COUNT,128>>>( elem_count, elem_data, trans, wb, hb, sb, mesh.ptr(), proj[ 0 ], proj[ 1 ] ) ));

    // fill image
    dim3 grid_size_raster( wb, hb );
    CSC(( raster_gpu_kernel<<<grid_size_raster,NB_THREADS_FOR_RASTER>>>(
             display->img_rgba.get_gpu_ptr(),
             display->img_zznv.get_gpu_ptr(),
             display->img_nnnn.get_gpu_ptr(),
             wb, hb, sb, w, h,
             elem_count + sb * NB_BLOCKS_FOR_ELEM_COUNT, elem_data,
             mesh.ptr(), proj[ 0 ], proj[ 1 ], proj[ 2 ],
             display->p_min[ 2 ], 65534.0 / plus_one_if_eqz( display->p_max[ 2 ] - display->p_min[ 2 ] ), display->first_item(),
             min_coloring_field, max_coloring_field,
             num_coloring_field, dim_coloring_field
    ) ));
}

void DisplayItem_BasicMesh::render_to( VectorDisplay * ) {
    TODO;
}

END_METIL_NAMESPACE;
