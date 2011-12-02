#ifndef CUDASCALAROP_H
#define CUDASCALAROP_H

#include "CudaMetil.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

#define NB_THREADS_FOR_SCALAR_OP 64
#define NB_BLOCKS_FOR_SCALAR_OP 128

template<class Dst,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, ST size, Op op ) {
    for( int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x; ind < size; ind += NB_BLOCKS_FOR_SCALAR_OP * NB_THREADS_FOR_SCALAR_OP )
        op( dst[ ind ] );
}

template<class Dst,class Src,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, const Src *src, ST size, Op op ) {
    for( int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x; ind < size; ind += NB_BLOCKS_FOR_SCALAR_OP * NB_THREADS_FOR_SCALAR_OP )
        op( dst[ ind ], src[ ind ] );
}

template<class Dst,class Src,class Srd,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, const Src *src, const Srd *srd, ST size, Op op ) {
    for( int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x; ind < size; ind += NB_BLOCKS_FOR_SCALAR_OP * NB_THREADS_FOR_SCALAR_OP )
        op( dst[ ind ], src[ ind ], srd[ ind ] );
}


/// self version
template<class Dst,class Op>
void cuda_scalar_op( Dst *dst, ST size, const Op &op ) {
    CSC(( cuda_scalar_op_kernel<<<NB_BLOCKS_FOR_SCALAR_OP,NB_THREADS_FOR_SCALAR_OP>>>( dst, size, op ) ));
}

/// with 1 arg
template<class Dst,class Src,class Op>
void cuda_scalar_op( Dst *dst, const Src *src, ST size, const Op &op ) {
    CSC(( cuda_scalar_op_kernel<<<NB_BLOCKS_FOR_SCALAR_OP,NB_THREADS_FOR_SCALAR_OP>>>( dst, src, size, op ) ));
}

/// with 1 arg
template<class Dst,class Src,class Srd,class Op>
void cuda_scalar_op( Dst *dst, const Src *src, const Srd *srd, ST size, const Op &op ) {
    // iDivUp( size, ST( NB_THREADS_FOR_SCALAR_OP ) )
    CSC(( cuda_scalar_op_kernel<<<NB_BLOCKS_FOR_SCALAR_OP,NB_THREADS_FOR_SCALAR_OP>>>( dst, src, srd, size, op ) ));
}

/**
  Ex:
   cuda_scalar_op( dst, size, SetVal<int>( 10 ) );

  will set $size values of $dst to 10

  cuda_scalar_op can take other vectors as argument. Ex

    template<class T>
    struct SelfAdd {
        __inline__ void operator()( T &dst, T vec ) const { dst += 15 * vec; }
    };

    cuda_scalar_op( dst, vec, size, SelfAdd() );

  will make the operation dst[ i ] += 15 * vec[ i ]; for each i in 0..size
*/
template<class T>
struct SetVal {
    SetVal( T val ) : val( val ) {}
    __inline__ void operator()( T &dst ) const { dst = val; }
    T val;
};

END_METIL_NAMESPACE;

#endif // CUDASCALAROP_H
