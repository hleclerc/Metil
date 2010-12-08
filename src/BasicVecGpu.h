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
    BasicVecGpu() : _rese( 0 ), _size( 0 ) {}

    BasicVecGpu( Size, ST size, const T *data_ptr ) : _rese( size ), _size( size ) {
        if ( size ) {
            cudaMalloc( &_data, sizeof( T ) * _rese );
            cudaMemcpy( _data, data_ptr, sizeof( T ) * _rese, cudaMemcpyHostToDevice );
        }
    }

    ~BasicVecGpu() {
        if ( _rese )
            cudaFree( _data );
    }

    T *reserve_without_copy( ST want ) {
        if ( want != _rese ) {
            if ( _rese )
                cudaFree( _data );
            _rese = want;
            cudaMalloc( &_data, sizeof( T ) * want );
        }
        return _data;
    }

    T *resize_without_copy( ST want ) {
        _size = want;
        return reserve_without_copy( want );
    }

    const T *ptr() const { return _data; }
    T *ptr() { return _data; }

    ST size() const { return _size; }
    ST rese() const { return _rese; }

    void copy_to( BasicVec<T> &res ) {
        res.resize( _rese );
        cudaMemcpy( res.ptr(), _data, sizeof( T ) * _rese, cudaMemcpyDeviceToHost );
    }

    T operator[]( ST index ) const {
        T res;
        cudaMemcpy( &res, _data + index, sizeof( T ), cudaMemcpyDeviceToHost );
        return res;
    }

private:
    T *_data;
    ST _rese;
    ST _size;
};

END_METIL_NAMESPACE;

#endif // BASICVECGPU_H
