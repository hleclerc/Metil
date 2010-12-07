#ifndef BASICVECGPU_H
#define BASICVECGPU_H

#include "CudaMetil.h"
#include "BasicVec.h"

BEG_METIL_NAMESPACE;

/**
  simple vec
*/
template<class T>
struct BasicVecGpu {
    BasicVecGpu() : rese( 0 ) {}

    BasicVecGpu( Size, ST size, const T *data_ptr ) : rese( size ), size( size ) {
        cudaMalloc( &data, sizeof( T ) * rese );
        cudaMemcpy( data, data_ptr, sizeof( T ) * rese, cudaMemcpyHostToDevice );
    }

    ~BasicVecGpu() {
        if ( rese )
            cudaFree( data );
    }

    T *reserve_without_copy( ST want ) {
        if ( want != rese ) {
            if ( rese )
                cudaFree( data );
            rese = want;
            cudaMalloc( &data, sizeof( T ) * want );
        }
        return data;
    }

    const T *ptr() const { return data; }
    T *ptr() { return data; }

    void copy_to( BasicVec<T> &res ) {
        res.resize( rese );
        cudaMemcpy( res.ptr(), data, sizeof( T ) * rese, cudaMemcpyDeviceToHost );
    }

    T operator[]( ST index ) const {
        T res;
        cudaMemcpy( &res, data + index, sizeof( T ), cudaMemcpyDeviceToHost );
        return res;
    }

    T *data;
    ST rese;
    ST size;
};

END_METIL_NAMESPACE;

#endif // BASICVECGPU_H
