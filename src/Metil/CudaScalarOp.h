#ifndef CUDASCALAROP_H
#define CUDASCALAROP_H

#include "CudaMetil.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

#define NB_THREADS_FOR_SCALAR_OP 64

template<class Dst,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, ST size, Op op ) {
    int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x;
    if ( ind < size )
        op( dst[ ind ] );
}

template<class Dst,class Src,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, const Src *src, ST size, Op op ) {
    int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x;
    if ( ind < size )
        op( dst[ ind ], src[ ind ] );
}

template<class Dst,class Src,class Srd,class Op> __global__
void cuda_scalar_op_kernel( Dst *dst, const Src *src, const Srd *srd, ST size, Op op ) {
    int ind = blockIdx.x * NB_THREADS_FOR_SCALAR_OP + threadIdx.x;
    if ( ind < size )
        op( dst[ ind ], src[ ind ], srd[ ind ] );
}


/// self version
template<class Dst,class Op>
void cuda_scalar_op( Dst *dst, ST size, const Op &op ) {
    cuda_scalar_op_kernel<<<iDivUp( size, NB_THREADS_FOR_SCALAR_OP ),NB_THREADS_FOR_SCALAR_OP>>>( dst, size, op );
}

/// with 1 arg
template<class Dst,class Src,class Op>
void cuda_scalar_op( Dst *dst, const Src *src, ST size, const Op &op ) {
    cuda_scalar_op_kernel<<<iDivUp( size, NB_THREADS_FOR_SCALAR_OP ),NB_THREADS_FOR_SCALAR_OP>>>( dst, src, size, op );
}

/// with 1 arg
template<class Dst,class Src,class Srd,class Op>
void cuda_scalar_op( Dst *dst, const Src *src, const Srd *srd, ST size, const Op &op ) {
    cuda_scalar_op_kernel<<<iDivUp( size, NB_THREADS_FOR_SCALAR_OP ),NB_THREADS_FOR_SCALAR_OP>>>( dst, src, srd, size, op );
}

template<class T>
struct SetVal {
    SetVal( T val ) : val( val ) {}
    __inline__ void operator()( T &dst ) const { dst = val; }
    T val;
};

END_METIL_NAMESPACE;

#endif // CUDASCALAROP_H
