#ifndef CUDAREDUCTION_H
#define CUDAREDUCTION_H

#include "PrevNextPow2.h"
#include "CudaMetil.h"
//#include "String.h"
#include "Limits.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

// #define NB_BLOCKS__FOR_REDUCTION 64
// #define NB_THREADS_FOR_REDUCTION 64

//
template<class T,int nb_th>
__device__ void cuda_reduction_kernel_loc( T *loc, N<nb_th> ) {
    for( int m = nb_th / 2; m; m /= 2 ) {
        syncthreads();
        if ( threadIdx.x < m )
            loc[ threadIdx.x ].reduction( loc[ threadIdx.x + m ] );
    }
}

// make NB_BLOCKS__FOR_REDUCTION R. 1 arg
template<class R,class T0,int nb_bl,int nb_th> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, ST size, N<nb_bl>, N<nb_th> ) {
    __shared__ R loc[ nb_th ];

    // update loc
    syncthreads();
    for( int index = blockIdx.x * nb_th + threadIdx.x; index < size; index += nb_bl * nb_th )
        loc[ threadIdx.x ].reduction( data_0[ index ] );

    // reduction of loc
    cuda_reduction_kernel_loc( loc, N<nb_th>() );

    // save
    syncthreads();
    if ( threadIdx.x == 0 )
        res[ blockIdx.x ] = loc[ 0 ];
}

// make NB_BLOCKS__FOR_REDUCTION R. 2 arg
template<class R,class T0,class T1,int nb_bl,int nb_th> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, const T1 *data_1, ST size, N<nb_bl>, N<nb_th> ) {
    __shared__ R loc[ nb_th ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * nb_th + threadIdx.x; index < size; index += nb_bl * nb_th )
        loc[ threadIdx.x ].reduction( data_0[ index ], data_1[ index ] );

    // reduction of loc
    for( int m = nb_th / 2; m; m /= 2 ) {
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
template<class R,class T0,class T1,class T2,int nb_bl,int nb_th> __global__
void cuda_reduction_kernel_0( R *res, const T0 *data_0, const T1 *data_1, const T2 *data_2, ST size, N<nb_bl>, N<nb_th> ) {
    __shared__ R loc[ nb_th ];

    // uupdate loc
    syncthreads();
    for( int index = blockIdx.x * nb_th + threadIdx.x; index < size; index += nb_bl * nb_th )
        loc[ threadIdx.x ].reduction( data_0[ index ], data_1[ index ], data_2[ index ] );

    // reduction of loc
    for( int m = nb_th / 2; m; m /= 2 ) {
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
template<class R,int nb_th> __global__
void cuda_reduction_kernel_1( R *res, N<nb_th> ) {
    // copy in loc
    __shared__ R loc[ nb_th ];
    loc[ threadIdx.x ] = res[ threadIdx.x ];

    // reduction of loc
    for( int m = nb_th / 2; m; m /= 2 ) {
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
    const int nb_th = MIN( 128, PrevPow2< ( 0x4000 - 1 ) / sizeof( R ) >::res );
    const int nb_bl = 64;
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * nb_bl );
    cuda_reduction_kernel_0<<<nb_bl,nb_th>>>( tmp, data_0, size, N<nb_bl>(), N<nb_th>() );
    cuda_reduction_kernel_1<<<    1,nb_bl>>>( tmp, N<nb_bl>() );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    CSC(( cudaFree( tmp ) ));
}

/// 2 arg
template<class R,class T0,class T1>
void cuda_reduction( R &res, const T0 *data_0, const T1 *data_1, ST size ) {
    const int nb_th = MIN( 128, PrevPow2< ( 0x4000 - 1 ) / sizeof( R ) >::res );
    const int nb_bl = 64;
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * nb_bl );
    cuda_reduction_kernel_0<<<nb_bl,nb_th>>>( tmp, data_0, data_1, size, N<nb_bl>(), N<nb_th>() );
    cuda_reduction_kernel_1<<<    1,nb_bl>>>( tmp, N<nb_bl>() );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    CSC(( cudaFree( tmp ) ));
}

/// 3 arg
template<class R,class T0,class T1,class T2>
void cuda_reduction( R &res, const T0 *data_0, const T1 *data_1, const T2 *data_2, ST size ) {
    const int nb_th = MIN( 128, PrevPow2< ( 0x4000 - 1 ) / sizeof( R ) >::res );
    const int nb_bl = 64;
    R *tmp; cudaMalloc( &tmp, sizeof( R ) * nb_bl );
    cuda_reduction_kernel_0<<<nb_bl,nb_th>>>( tmp, data_0, data_1, data_2, size, N<nb_bl>(), N<nb_th>() );
    cuda_reduction_kernel_1<<<    1,nb_bl>>>( tmp, N<nb_bl>() );
    cudaMemcpy( &res, tmp, sizeof( R ), cudaMemcpyDeviceToHost );
    CSC(( cudaFree( tmp ) ));
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
    template<class ST>
    void write_str( ST &os ) const {
        os << "mi=" << mi << " ma=" << ma;
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

/**
  Example to sum a vector of TF:
@code
CudaReductionSum<TF> sum;
cuda_reduction( sum, data, size );
PRINT( sum.res );
@endcode

*/
template<class T>
struct CudaReductionSum {
    __inline__ CudaReductionSum() { res = 0; }
    __inline__ void reduction( T v0 ) { res += v0; }
    __inline__ void reduction( const CudaReductionSum &val ) { res += val.res; }
    T res;
};

END_METIL_NAMESPACE;

#endif // CUDAREDUCTION_H
