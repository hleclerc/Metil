#include "GetSurroundingBox_BasicMesh.h"
#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplay.h"
#include "MathBasicVec.h"
#include "CudaMetil.h"

#define NB_PIX_RASTER_BOX 32
#define NB_BLOCKS_FOR_ELEM_COUNT 32
#define MAX_WH ( 1600 * 1200 )
#define NB_THREADS_FOR_RASTER 64

BEG_METIL_NAMESPACE;

DisplayItem_BasicMesh::DisplayItem_BasicMesh( Ps<BasicMesh_Compacted> mesh ) : mesh( mesh ) {
    size_elem_count = 0;
    elem_count_gpu = 0;

    size_elem_data = 0;
    elem_data_gpu = 0;
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

void DisplayItem_BasicMesh::update_p_min_p_max( GenericDisplay *display, T3 &p_min, T3 &p_max ) {
    T3 t_min;
    T3 t_max;
    get_surrounding_box( t_min.ptr(), t_max.ptr(), mesh.ptr(), display->get_trans_gpu(), display->get_w(), display->get_h() );
    for( int i = 0; i < 3; ++i ) {
        p_min[ i ] = min( p_min[ i ], t_min[ i ] );
        p_max[ i ] = max( p_max[ i ], t_max[ i ] );
    }
}

__global__
void make_elem_count_kernel( unsigned *elem_count, DisplayTrans *trans_ptr, int wb, int hb, int w, int h, BasicMesh_Compacted *m ) {
    typedef BasicVec<float,3> T3;

    int sb = wb * hb;
    elem_count += blockIdx.x * sb;

    DisplayTrans::Buf trans = trans_ptr->make_buf( w, h );

    const float *n_x = m->pos_nodes[ 0 ].ptr();
    const float *n_y = m->pos_nodes[ 1 ].ptr();
    const float *n_z = m->pos_nodes[ 2 ].ptr();

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

            T3 B_0 = trans.proj( n_x[ n_0 ], n_y[ n_0 ], n_z[ n_0 ] );
            T3 B_1 = trans.proj( n_x[ n_1 ], n_y[ n_1 ], n_z[ n_1 ] );
            T3 B_2 = trans.proj( n_x[ n_2 ], n_y[ n_2 ], n_z[ n_2 ] );

            int x_m = int( min( min( B_0[ 0 ], B_1[ 0 ] ), B_2[ 0 ] ) ) / NB_PIX_RASTER_BOX;
            int x_M = int( max( max( B_0[ 0 ], B_1[ 0 ] ), B_2[ 0 ] ) ) / NB_PIX_RASTER_BOX;
            int y_m = int( min( min( B_0[ 1 ], B_1[ 1 ] ), B_2[ 1 ] ) ) / NB_PIX_RASTER_BOX;
            int y_M = int( max( max( B_0[ 1 ], B_1[ 1 ] ), B_2[ 1 ] ) ) / NB_PIX_RASTER_BOX;

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
void make_elem_data_kernel( unsigned *elem_count, int *elem_data, const DisplayTrans *trans_ptr, int wb, int hb, int sb, int w, int h, BasicMesh_Compacted *m ) {
    typedef BasicVec<float,3> T3;
    __shared__ unsigned local_count[ MAX_WH / NB_PIX_RASTER_BOX / NB_PIX_RASTER_BOX ];

    DisplayTrans::Buf trans = trans_ptr->make_buf( w, h );

    const float *n_x = m->pos_nodes[ 0 ].ptr();
    const float *n_y = m->pos_nodes[ 1 ].ptr();
    const float *n_z = m->pos_nodes[ 2 ].ptr();

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

            T3 B_0 = trans.proj( n_x[ n_0 ], n_y[ n_0 ], n_z[ n_0 ] );
            T3 B_1 = trans.proj( n_x[ n_1 ], n_y[ n_1 ], n_z[ n_1 ] );
            T3 B_2 = trans.proj( n_x[ n_2 ], n_y[ n_2 ], n_z[ n_2 ] );

            int x_m = int( min( min( B_0[ 0 ], B_1[ 0 ] ), B_2[ 0 ] ) ) / NB_PIX_RASTER_BOX;
            int x_M = int( max( max( B_0[ 0 ], B_1[ 0 ] ), B_2[ 0 ] ) ) / NB_PIX_RASTER_BOX;
            int y_m = int( min( min( B_0[ 1 ], B_1[ 1 ] ), B_2[ 1 ] ) ) / NB_PIX_RASTER_BOX;
            int y_M = int( max( max( B_0[ 1 ], B_1[ 1 ] ), B_2[ 1 ] ) ) / NB_PIX_RASTER_BOX;

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

__global__
void init_raster_GPU_kernel( unsigned *res, int w, int h ) {
    unsigned *info = res + 3 * w * h;
    info[ 4 ] = 0xFFFFFFFF;
    info[ 5 ] = 0xFF000000;
}


__inline__
unsigned shader( float z_n ) {
    int r = z_n * 200;
    int g = r;
    int b = r;
    int a = 255;
    return ( r << 0 ) + ( g << 8 ) + ( b << 16 ) + ( a << 24 );
}

/// use 2 unsigned to store a T ( 2 because of tha alpha chanel that must be == 0xFF )
__inline__ void copy_T_as_I( unsigned *res, float src ) {
    int e, s = src < 0;
    unsigned m = abs( frexpf( src, &e ) * 0x01000000 );
    res[ 0 ] = 0xFF000000 + m;
    res[ 1 ] = 0xFF000000 + ( s << 16 ) + ( e + 32768 );
}

__global__
void raster_gpu_kernel( unsigned *res, const DisplayTrans *trans_ptr, int wb, int hb, int sb, int w, int h, const unsigned *elem_offsets, const int *elem_data, const BasicMesh_Compacted *m, float z_min, float z_max, bool first_item ) {
    typedef DisplayTrans::T3 T3;

    int bx = blockIdx.x * NB_PIX_RASTER_BOX;
    int by = blockIdx.y * NB_PIX_RASTER_BOX;

    unsigned *rgba = res + 0 * w * h;
    unsigned *zznv = res + 1 * w * h;
    unsigned *nnnn = res + 2 * w * h;
    unsigned *info = res + 3 * w * h;


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

    DisplayTrans::Buf trans = trans_ptr->make_buf( w, h );

    const float *n_x = m->pos_nodes[ 0 ].ptr();
    const float *n_y = m->pos_nodes[ 1 ].ptr();
    const float *n_z = m->pos_nodes[ 2 ].ptr();

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

            T3 P_0( n_x[ n_0 ], n_y[ n_0 ], n_z[ n_0 ] );
            T3 P_1( n_x[ n_1 ], n_y[ n_1 ], n_z[ n_1 ] );
            T3 P_2( n_x[ n_2 ], n_y[ n_2 ], n_z[ n_2 ] );
            T3 normal = normalized( cross( P_1 - P_0, P_2 - P_0 ) );

            T3 B_0 = trans.proj( P_0 );
            T3 B_1 = trans.proj( P_1 );
            T3 B_2 = trans.proj( P_2 );

            swap_if( B_0, B_1, B_0[ 1 ] > B_1[ 1 ] );
            swap_if( B_0, B_2, B_0[ 1 ] > B_2[ 1 ] );
            swap_if( B_1, B_2, B_1[ 1 ] > B_2[ 1 ] );

            int x_0 = int( B_0[ 0 ] ) - bx, y_0 = int( B_0[ 1 ] ) - by;
            int x_1 = int( B_1[ 0 ] ) - bx, y_1 = int( B_1[ 1 ] ) - by;
            int x_2 = int( B_2[ 0 ] ) - bx, y_2 = int( B_2[ 1 ] ) - by;

            int dx_01 = x_1 - x_0, dy_01 = y_1 - y_0; float dz_01 = B_1[ 2 ] - B_0[ 2 ];
            int dx_02 = x_2 - x_0, dy_02 = y_2 - y_0; float dz_02 = B_2[ 2 ] - B_0[ 2 ];

            float cx_0 = dx_01 / float( dy_01 + not dy_01 ), cz_0 = dz_01 / float( dy_01 + not dy_01 );
            float cx_1 = dx_02 / float( dy_02 + not dy_02 ), cz_1 = dz_02 / float( dy_02 + not dy_02 );
            bool cond_0 = cx_0 > cx_1;
            swap_if( cx_0, cx_1, cond_0 );
            swap_if( cz_0, cz_1, cond_0 );

            for( int y_b = max( 0, y_0 ); y_b < min( NB_PIX_RASTER_BOX, y_1 ); ++y_b ) {
                int xl_0 = x_0 + ( y_b - y_0 ) * cx_0;
                int xl_1 = x_0 + ( y_b - y_0 ) * cx_1;

                float zl_0 = B_0[ 2 ] + ( y_b - y_0 ) * cz_0;
                float zl_1 = B_0[ 2 ] + ( y_b - y_0 ) * cz_1;
                float c_z = xl_1 - xl_0; c_z = ( zl_1 - zl_0 ) / ( c_z + not c_z );

                for( int x_b = max( 0, xl_0 ); x_b < min( NB_PIX_RASTER_BOX, xl_1 + 1 ); ++x_b ) {
                    float z_b = zl_0 + ( x_b - xl_0 ) * c_z;
                    unsigned z_bi = ( z_b - z_min ) * 65534 / ( z_max - z_min );
                    unsigned z_re = atomicMin( zznv_buffer + NB_PIX_RASTER_BOX * y_b + x_b, z_bi );
                    if ( z_re > z_bi ) {
                        float c = abs( dot( normal, trans.eye_dir( x_b + bx, y_b + by ) ) );
                        rgba_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = shader( c );
                        nnnn_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = ind_elem;
                    }
                }
            }

            int dx_21 = x_1 - x_2, dy_21 = y_1 - y_2, dz_21 = B_1[ 2 ] - B_2[ 2 ];
            int dx_22 = x_0 - x_2, dy_22 = y_0 - y_2, dz_22 = B_0[ 2 ] - B_2[ 2 ];

            float cx_2 = dx_21 / float( dy_21 + not dy_21 ), cz_2 = dz_21 / float( dy_21 + not dy_21 );
            float cx_3 = dx_22 / float( dy_22 + not dy_22 ), cz_3 = dz_22 / float( dy_22 + not dy_22 );
            bool cond_1 = cx_2 < cx_3;
            swap_if( cx_2, cx_3, cond_1 );
            swap_if( cz_2, cz_3, cond_1 );

            for( int y_b = max( 0, y_1 ); y_b < min( NB_PIX_RASTER_BOX, y_2 + 1 ); ++y_b ) {
                int xl_0 = x_2 + ( y_b - y_2 ) * cx_2;
                int xl_1 = x_2 + ( y_b - y_2 ) * cx_3;

                float zl_0 = B_2[ 2 ] + ( y_b - y_2 ) * cz_2;
                float zl_1 = B_2[ 2 ] + ( y_b - y_2 ) * cz_3;
                float c_z = xl_1 - xl_0; c_z = ( zl_1 - zl_0 ) / ( c_z + not c_z );

                for( int x_b = max( 0, xl_0 ); x_b < min( NB_PIX_RASTER_BOX, xl_1 + 1 ); ++x_b ) {
                    float z_b = zl_0 + ( x_b - xl_0 ) * c_z;
                    unsigned z_bi = ( z_b - z_min ) * 65534 / ( z_max - z_min );
                    unsigned z_re = atomicMin( zznv_buffer + NB_PIX_RASTER_BOX * y_b + x_b, z_bi );
                    if ( z_re > z_bi ) {
                        float c = abs( dot( normal, trans.eye_dir( x_b + bx, y_b + by ) ) );
                        rgba_buffer[ NB_PIX_RASTER_BOX * y_b + x_b ] = shader( c );
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
        int x = bx + i % NB_PIX_RASTER_BOX;
        int y = by + i / NB_PIX_RASTER_BOX;

        if ( x < w and y < h ) {
            rgba[ w * y + x ] = rgba_buffer[ i ];
            zznv[ w * y + x ] = 0xFF000000 + zznv_buffer[ i ];
            nnnn[ w * y + x ] = 0xFF000000 + nnnn_buffer[ i ];
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

    if ( threadIdx.x == 0 ) {
        if ( blockIdx.x == 0 ) {
            copy_T_as_I( info + 0, z_min );
            copy_T_as_I( info + 2, z_max );
        }
        if ( *local_z_min != 0xFFFFFFFF )
            atomicMin( info + 4, 0xFF000000 + ( *local_z_min/* >> 8*/ ) );
        if ( *local_z_max != 0x0 )
            atomicMax( info + 5, 0xFF000000 + ( *local_z_max/* >> 8*/ ) );
    }
}


void DisplayItem_BasicMesh::render_to( BitmapDisplay *display ) {
    ASSERT( mesh.pos.is_a_gpu(), "render works only with data on gpu" );

    int w = display->get_w();
    int h = display->get_h();
    int wb = iDivUp( w, NB_PIX_RASTER_BOX );
    int hb = iDivUp( h, NB_PIX_RASTER_BOX );
    int sb = wb * hb;

    ST nb_types;
    cudaMemcpy( &nb_types, &mesh->elem_groups.size_, sizeof( ST ), cudaMemcpyDeviceToHost );

    // fill elem_count
    unsigned *elem_count = get_elem_count_gpu_ptr( nb_types, sb );
    DisplayTrans *trans = display->get_trans_gpu();
    CSC(( make_elem_count_kernel<<<NB_BLOCKS_FOR_ELEM_COUNT,128>>>( elem_count, trans, wb, hb, w, h, mesh.ptr() ) ));
    CSC(( make_sum_elem_count_kernel<<<Metil::iDivUp(sb,64),64>>>( elem_count, wb, hb, nb_types ) ));
    CSC(( make_off_elem_count_kernel<<<1,1>>>( elem_count, wb, hb, nb_types ) ));

    // find size of elem_data list
    unsigned tot_nb_elems;
    CSC(( cudaMemcpy( &tot_nb_elems, elem_count + nb_types * rese_elem_count_for_one_group( sb ),
                      sizeof( unsigned ), cudaMemcpyDeviceToHost ) ));


    // fill elem_data
    int *elem_data = get_elem_data_gpu_ptr( tot_nb_elems );
    CSC(( make_elem_data_kernel<<<NB_BLOCKS_FOR_ELEM_COUNT,128>>>( elem_count, elem_data, trans, wb, hb, sb, w, h, mesh.ptr() ) ));

    // init info structure at the end of the image
    init_raster_GPU_kernel<<<1,1>>>( display->get_img_gpu_ptr(), w, h );

    // fill image
    dim3 grid_size_raster( wb, hb );
    CSC(( raster_gpu_kernel<<<grid_size_raster,NB_THREADS_FOR_RASTER>>>(
            display->get_img_gpu_ptr(), trans, wb, hb, sb, w, h,
            elem_count + sb * NB_BLOCKS_FOR_ELEM_COUNT,
            elem_data, mesh.ptr(), display->p_min[ 2 ], display->p_max[ 2 ], display->first_item()
    ) ));
}

void DisplayItem_BasicMesh::render_to( VectorDisplay * ) {
    TODO;
}

END_METIL_NAMESPACE;
