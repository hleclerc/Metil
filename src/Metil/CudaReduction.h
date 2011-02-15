#ifndef CUDAREDUCTION_H
#define CUDAREDUCTION_H

#include "Limits.h"
#include "CudaMetil.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

#define NB_BLOCKS__FOR_REDUCTION 64
#define NB_THREADS_FOR_REDUCTION 64

//
template<class T,int nb_threads>
__device__ void cuda_reduction_kernel_loc( T *loc, N<nb_threads> ) {
    for( int m = nb_threads / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m )
            loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }
}

// make NB_BLOCKS__FOR_REDUCTION R. 1 arg
template<class R,class T0> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, ST size ) {
    __shared__ R loc[ NB_THREADS_FOR_REDUCTION ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * NB_THREADS_FOR_REDUCTION + threadIdx.x; index < size; index += NB_BLOCKS__FOR_REDUCTION * NB_THREADS_FOR_REDUCTION )
        loc[ threadIdx.x ].reduction( data_0[ index ] );

    // reduction of loc
    cuda_reduction_kernel_loc( loc, N<NB_THREADS_FOR_REDUCTION>() );

    // save
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ blockIdx.x ] = loc[ 0 ];
}

// make NB_BLOCKS__FOR_REDUCTION R. 2 arg
template<class R,class T0,class T1> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, const T1 *data_1, ST size ) {
    __shared__ R loc[ NB_THREADS_FOR_REDUCTION ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * NB_THREADS_FOR_REDUCTION + threadIdx.x; index < size; index += NB_BLOCKS__FOR_REDUCTION * NB_THREADS_FOR_REDUCTION )
        loc[ threadIdx.x ].reduction( data_0[ index ], data_1[ index ] );

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

// make NB_BLOCKS__FOR_REDUCTION R. 3 arg
template<class R,class T0,class T1,class T2> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, const T1 *data_1, const T2 *data_2, ST size ) {
    __shared__ R loc[ NB_THREADS_FOR_REDUCTION ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * NB_THREADS_FOR_REDUCTION + threadIdx.x; index < size; index += NB_BLOCKS__FOR_REDUCTION * NB_THREADS_FOR_REDUCTION )
        loc[ threadIdx.x ].reduction( data_0[ index ], data_1[ index ], data_2[ index ] );

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

// reduction of NB_BLOCKS__FOR_REDUCTION R
template<class R> __global__
void cuda_reduction_kernel_1( R *res ) {
    // copy in loc
    __shared__ R loc[ NB_BLOCKS__FOR_REDUCTION ];
    loc[ threadIdx.x ] = res[ threadIdx.x ];

    // reduction of loc
    for( int m = NB_BLOCKS__FOR_REDUCTION / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m )
            loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }

    // save in res
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ 0 ] = loc[ 0 ];
}

/// 1 arg
template<class R,class T0>
void cuda_reduction( R &res, const T0 *data_0, ST size ) {
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * NB_BLOCKS__FOR_REDUCTION );
    cuda_reduction_kernel_0<<<NB_BLOCKS__FOR_REDUCTION,NB_THREADS_FOR_REDUCTION>>>( tmp, data_0, size );
    cuda_reduction_kernel_1<<<                       1,NB_BLOCKS__FOR_REDUCTION>>>( tmp );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    cudaFree( tmp );
}

/// 2 arg
template<class R,class T0,class T1>
void cuda_reduction( R &res, const T0 *data_0, const T1 *data_1, ST size ) {
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * NB_BLOCKS__FOR_REDUCTION );
    cuda_reduction_kernel_0<<<NB_BLOCKS__FOR_REDUCTION,NB_THREADS_FOR_REDUCTION>>>( tmp, data_0, data_1, size );
    cuda_reduction_kernel_1<<<                       1,NB_BLOCKS__FOR_REDUCTION>>>( tmp );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    cudaFree( tmp );
}

/// 3 arg
template<class R,class T0,class T1,class T2>
void cuda_reduction( R &res, const T0 *data_0, const T1 *data_1, const T2 *data_2, ST size ) {
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * NB_BLOCKS__FOR_REDUCTION );
    cuda_reduction_kernel_0<<<NB_BLOCKS__FOR_REDUCTION,NB_THREADS_FOR_REDUCTION>>>( tmp, data_0, data_1, data_2, size );
    cuda_reduction_kernel_1<<<                       1,NB_BLOCKS__FOR_REDUCTION>>>( tmp );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    cudaFree( tmp );
}

template<class T>
struct CudaReductionMinMax {
    __inline__ CudaReductionMinMax() {
        mi = Limits<T>::max();
        ma = Limits<T>::min();
    }
    __inline__ void reduction( T val ) {
        mi = min( mi, val );
        ma = max( ma, val );
    }
    __inline__ void reduction( const CudaReductionMinMax &val ) {
        mi = min( mi, val.mi );
        ma = max( ma, val.ma );
    }
    T mi, ma;
};

template<class T>
struct CudaReductionSumSquare {
    __inline__ CudaReductionSumSquare() { res = 0; }
    __inline__ void reduction( T v0 ) { res += v0 * v0; }
    __inline__ void reduction( T v0, T v1 ) { res += v0 * v0 + v1 * v1; }
    __inline__ void reduction( T v0, T v1, T v2 ) { res += v0 * v0 + v1 * v1 + v2 * v2; }
    __inline__ void reduction( const CudaReductionSumSquare &val ) { res += val.res; }
    T res;
};

END_METIL_NAMESPACE;

#endif // CUDAREDUCTION_H
