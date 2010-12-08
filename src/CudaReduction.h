#ifndef CUDAREDUCTION_H
#define CUDAREDUCTION_H

#include "CudaMetil.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

#define NB_BLOCKS_FOR_REDUCTION 64
#define NB_THREADS_FOR_REDUCTION 64

// make NB_BLOCKS_FOR_REDUCTION R
template<class R,class T> __global__
void cuda_reduction_kernel_0( R *res, const T *data, ST size ) {
    __shared__ R loc[ NB_THREADS_FOR_REDUCTION ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * blockDim.x + threadIdx.x; index < size; index += NB_THREADS_FOR_REDUCTION )
        loc[ threadIdx.x ].reduction( data[ index ] );

    // reduction of loc
    for( int m = NB_THREADS_FOR_REDUCTION / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m )
            loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }

    // save
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ blockIdx.x ] = loc[ 0 ];
}

// reduction of NB_BLOCKS_FOR_REDUCTION R
template<class R> __global__
void cuda_reduction_kernel_1( R *res ) {
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

template<class R,class T>
void cuda_reduction( R &res, const T *data, ST size ) {
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * NB_BLOCKS_FOR_REDUCTION );

    cuda_reduction_kernel_0<<<NB_BLOCKS_FOR_REDUCTION,NB_THREADS_FOR_REDUCTION>>>( tmp, data, size );
    cuda_reduction_kernel_1<<<                      1,NB_BLOCKS_FOR_REDUCTION >>>( tmp );

    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    cudaFree( tmp );
}

END_METIL_NAMESPACE;

#endif // CUDAREDUCTION_H
