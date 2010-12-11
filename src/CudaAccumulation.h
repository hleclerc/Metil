#ifndef CUDAACCUMULATION_H
#define CUDAACCUMULATION_H

#include "PrevNextPow2.h"
#include "CudaMetil.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

// make NB_BLOCKS_FOR_REDUCTION R
template<class T,int size_per_block> __global__
void cuda_accumulation_kernel_0( T *data, ST size, Number<size_per_block> ) {
    int index = blockIdx.x * size_per_block + threadIdx.x;

    __shared__ T loc[ size_per_block ];
    loc[ threadIdx.x ] = offset < size ? data[ index ] : 0;

    // reduction of loc
    for( int d = 2; d < size_per_block; d *= 2 ) {
        syncthreads();
        for( int ; )
        loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }

    // save
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ blockIdx.x ] = loc[ 0 ];
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

template<class T>
void cuda_accumulation( const T *data, ST size ) {
    const int opt_size_per_block = ( SIZE_SHARED_MEM_CUDA - 512  ) / sizeof( T );
    const int size_per_block = PrevPow2<opt_size_per_block>::res;
    int nb_blocks = iDivUp( size, size_per_block );
    cuda_accumulation_kernel_0<<<nb_blocks,size_per_block>>>( data, size, Number<size_per_block>() );
    // cuda_accumulation_kernel_1<<<     1,         nb_blocks>>>( data, size );
}

END_METIL_NAMESPACE;

#endif // CUDAACCUMULATION_H
