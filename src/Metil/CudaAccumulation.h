#ifndef CUDAACCUMULATION_H
#define CUDAACCUMULATION_H

#include "PrevNextPow2.h"
#include "CudaMetil.h"
#include "String.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

/// n -> nb T in loc to accumulate
template<class T,int n> __device__
void _cuda_accumulation_kernel_loc_rec( T *loc, Number<n> ) {
    int t2 = 2 * threadIdx.x, a = t2 + 0, b = t2 + 1, s = n + threadIdx.x;

    syncthreads();
    if ( t2 < n ) {
        loc[ b ] += loc[ a ];
        loc[ s ]  = loc[ b ];
    }

    _cuda_accumulation_kernel_loc_rec( loc + n, Number<n/2>() );

    syncthreads();
    if ( t2 < n and threadIdx.x ) {
        loc[ a ] += loc[ s - 1 ];
        loc[ b ] += loc[ s - 1 ];
    }
}

template<class T> __device__
void _cuda_accumulation_kernel_loc_rec( T *loc, Number<1> ) {
}

template<class T,int n> __global__
void _cuda_accumulation_kernel_loc( T *data, int size, T *room, Number<n> ) {
    int o = n * blockIdx.x + threadIdx.x;

    __shared__ T loc[ 2 * n ];
    loc[ threadIdx.x ] = threadIdx.x < size ? data[ o ] : 0;

    syncthreads();
    _cuda_accumulation_kernel_loc_rec( loc, Number<n>() );

    syncthreads();
    if ( threadIdx.x < size )
        data[ o ] = loc[ threadIdx.x ];
    if ( room and threadIdx.x == n - 1 )
        room[ blockIdx.x ] = loc[ n - 1 ];
}

template<class T,int n> __global__
void _cuda_accumulation_kernel_add( T *data, int size, T *room, Number<n> ) {
    int o = n * ( blockIdx.x + 1 ) + threadIdx.x;
    if ( o < size ) {
        T a = room[ blockIdx.x ];
        data[ o ] += a;
    }
}

template<class T>
struct CudaAccumulationParm {
    static const int t = ( SIZE_SHARED_MEM_CUDA - 32 ) / sizeof( T );
    static const int u = PrevPow2<t>::res;
    static const int n = u < 512 ? u : 512;

    static ST room_size( ST size ) {
        if ( size <= 1 )
            return 0;
        ST l = iDivUp( size, ST( n ) );
        return l + room_size( l );
    }

    static void acc_rec( T *data, ST size, T *room ) {
        int nb_bl = iDivUp( size, ST( n ) );
        if ( nb_bl )
            CSC(( _cuda_accumulation_kernel_loc<<<nb_bl,n>>>( data, size, room, Number<n>() ) ));
        if ( nb_bl > 1 ) {
            acc_rec( room, nb_bl, room + nb_bl );
            CSC(( _cuda_accumulation_kernel_add<<<nb_bl-1,n>>>( data, size, room, Number<n>() ) ));
        }
    }

    static void acc( T *data, ST size, T *room, bool need_alloc ) {
        if ( need_alloc )
            cudaMalloc( &room, sizeof( T ) * room_size( size ) );
        acc_rec( data, size, room );
        if ( need_alloc )
            cudaFree( room );
    }
};

/// room must be free room for $size items
template<class T>
void cuda_accumulation( T *data, ST size, T *room = 0 ) {
    CudaAccumulationParm<T>::acc( data, size, room, not room );
}

END_METIL_NAMESPACE;

#endif // CUDAACCUMULATION_H
