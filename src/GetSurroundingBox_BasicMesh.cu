#include "GetSurroundingBox_BasicMesh.h"
#include "CudaMetil.h"
#include "String.h"

#define NB_THREADS_MIN_MAX 64
#define NB_BLOCKS_MIN_MAX  64

BEG_METIL_NAMESPACE;

__global__
void get_min_max_transformation_kernel_0( float *res, const BasicMesh_Compacted *m, const DisplayTrans *trans_ptr, int w, int h ) {
    typedef DisplayTrans::T  T;
    typedef DisplayTrans::T3 T3;

    float *min_list[ 3 ], *max_list[ 3 ];
    for( int d = 0; d < 3; ++d ) {
        min_list[ d ] = res + ( 2 * d + 0 ) * NB_BLOCKS_MIN_MAX;
        max_list[ d ] = res + ( 2 * d + 1 ) * NB_BLOCKS_MIN_MAX;
    }

    int nb_nodes = m->pos_nodes[ 0 ].size();
    const float *n_x = m->pos_nodes[ 0 ].ptr();
    const float *n_y = m->pos_nodes[ 1 ].ptr();
    const float *n_z = m->pos_nodes[ 2 ].ptr();

    __shared__ float local_min[ 3 * NB_THREADS_MIN_MAX ];
    __shared__ float local_max[ 3 * NB_THREADS_MIN_MAX ];

    for( int d = 0; d < 3; ++d ) {
        local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = + HUGE;
        local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = - HUGE;
    }

    if ( trans_ptr ) {
        DisplayTrans::Buf trans = trans_ptr->make_buf( w, h );
        for( int index = blockIdx.x * NB_THREADS_MIN_MAX + threadIdx.x; index < nb_nodes; index += NB_THREADS_MIN_MAX ) {
            T3 P = trans.proj( n_x[ index ], n_y[ index ], n_z[ index ] );
            for( int d = 0; d < 3; ++d ) {
                local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = min( local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ], P[ d ] );
                local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = max( local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ], P[ d ] );
            }
        }
    } else {
        for( int index = blockIdx.x * NB_THREADS_MIN_MAX + threadIdx.x;index < nb_nodes; index += NB_THREADS_MIN_MAX ) {
            T3 P( n_x[ index ], n_y[ index ], n_z[ index ] );
            for( int d = 0; d < 3; ++d ) {
                local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = min( local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ], P[ d ] );
                local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = max( local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ], P[ d ] );
            }
        }
    }

    // reduction
    for( int m = NB_THREADS_MIN_MAX / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m ) {
            for( int d = 0; d < 3; ++d ) {
                local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = min( local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x ], local_min[ d * NB_THREADS_MIN_MAX + threadIdx.x + m ] );
                local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ] = max( local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x ], local_max[ d * NB_THREADS_MIN_MAX + threadIdx.x + m ] );
            }
        }
    }

    // -> mi and ma
    syncthreads();
    for( int d = 0; d < 3; ++d ) {
        min_list[ d ][ blockIdx.x ] = local_min[ d * NB_THREADS_MIN_MAX ];
        max_list[ d ][ blockIdx.x ] = local_max[ d * NB_THREADS_MIN_MAX ];
    }
}

__global__
void get_min_max_transformation_kernel_1( float *res ) {
    float *min_list[ 3 ], *max_list[ 3 ];
    for( int d = 0; d < 3; ++d ) {
        min_list[ d ] = res + ( 2 * d + 0 ) * NB_BLOCKS_MIN_MAX;
        max_list[ d ] = res + ( 2 * d + 1 ) * NB_BLOCKS_MIN_MAX;
    }

    for( int m = NB_BLOCKS_MIN_MAX / 2; m; m /= 2 ) {
        syncthreads();
        for( int i = threadIdx.x; i < m; i += NB_BLOCKS_MIN_MAX ) {
            for( int c = 0; c < 3; ++c ) {
                min_list[ c ][ i ] = min( min_list[ c ][ i ], min_list[ c ][ i + m ] );
                max_list[ c ][ i ] = max( max_list[ c ][ i ], max_list[ c ][ i + m ] );
            }
        }
    }
}

void get_surrounding_box( float *mi, float *ma, BasicMesh_Compacted *m, DisplayTrans *trans, int w, int h ) {
    float *res;
    CSC(( cudaMalloc( &res, 3 * 2 * NB_BLOCKS_MIN_MAX * sizeof( float ) ) ));

    CSC(( get_min_max_transformation_kernel_0<<<NB_BLOCKS_MIN_MAX,NB_THREADS_MIN_MAX>>>( res, m, trans, w, h ) ));
    CSC(( get_min_max_transformation_kernel_1<<<                1, NB_BLOCKS_MIN_MAX>>>( res ) ));

    for( int d = 0; d < 3; ++d ) {
        CSC(( cudaMemcpy( mi + d, res + ( 2 * d + 0 ) * NB_BLOCKS_MIN_MAX, sizeof( float ), cudaMemcpyDeviceToHost ) ));
        CSC(( cudaMemcpy( ma + d, res + ( 2 * d + 1 ) * NB_BLOCKS_MIN_MAX, sizeof( float ), cudaMemcpyDeviceToHost ) ));
    }
}


END_METIL_NAMESPACE;
