#ifndef CUDAACCUMULATION_H
#define CUDAACCUMULATION_H

#include "CudaMetil.h"
#include "Math.h"

#define NB_THREADS_FOR_ACCUMULATION 64
#define NB_DIV_____FOR_ACCUMULATION 8

BEG_METIL_NAMESPACE;

// make NB_BLOCKS_FOR_REDUCTION R
template<class T> __global__
void cuda_accumulation_kernel_0( const T *data, ST size, T *room ) {
    int index_room = blockDim.x * blockIdx.x + threadIdx.x;
    int index_data = NB_DIV_____FOR_ACCUMULATION * index_room;

    T res = 0;
    for( int i = index_data; i < min( index_data + NB_DIV_____FOR_ACCUMULATION, size ); ++i )
        res += data[ i ];
    room[ index_room ] = res;
}

// reduction of NB_BLOCKS_FOR_REDUCTION R
template<class R> __global__
void cuda_accumulation_kernel_1( R *res ) {
    // copy in loc
    __shared__ R loc[ NB_BLOCKS_FOR_REDUCTION ];
    loc[ threadIdx.x ] = res[ threadIdx.x ];

    // reduction of loc
    for( int m = NB_BLOCKS_FOR_REDUCTION / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m )
            loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }

    // save in res
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ 0 ] = loc[ 0 ];
}

inline ST room_size_for_cuda_accumulation( ST size ) {
    ST res = 0, mul = size;
    while ( mul ) {
        mul = iDivUp( size, NB_DIV_____FOR_ACCUMULATION );
        res += mul;
    }
    return res;
}

/// a_{-1} = size; a_n = iDivUp( a_n - 1 ). room must contain sum a_n. Can be computed using room_size_for_cuda_accumulation
template<class T>
void cuda_accumulation( const T *data, ST size, T *room ) {
    ST tot_nb_threads = iDivUp( size, NB_DIV_____FOR_ACCUMULATION );
    int nb_blocks = iDivUp( tot_nb_threads, NB_THREADS_FOR_ACCUMULATION );
    cuda_accumulation_kernel_0<<<nb_blocks,NB_THREADS_FOR_ACCUMULATION>>>( data, size, room );
    // cuda_accumulation_kernel_1<<<     1,         nb_blocks>>>( data, size );
}

/// convenience function
template<class T>
void cuda_accumulation( const T *data, ST size ) {
    T *room;
    cudaMalloc( &room, sizeof( T ) * room_size_for_cuda_accumulation( size ) );
    cuda_accumulation( data, size, room );
    cudeFree( room );
}

END_METIL_NAMESPACE;

#endif // CUDAACCUMULATION_H
