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

    BasicVecGpu( Size, ST size, const T *data_ptr = 0 ) : _rese( size ), _size( size ) {
        if ( size ) {
            cudaMalloc( &_data, sizeof( T ) * _rese );
            if ( data_ptr )
                cudaMemcpy( _data, data_ptr, sizeof( T ) * _rese, cudaMemcpyHostToDevice );
        }
    }

    BasicVecGpu( const BasicVec<T> data_vec ) {
        init( data_vec );
    }

    BasicVecGpu &operator=( const BasicVecGpu &data_vec ) {
        if ( _rese )
            cudaFree( _data );
        _rese = data_vec.size();
        _size = data_vec.size();
        if ( _size ) {
            cudaMalloc( &_data, sizeof( T ) * _rese );
            cudaMemcpy( _data, data_vec.ptr(), sizeof( T ) * _rese, cudaMemcpyDeviceToDevice );
        }
        return *this;
    }

    void init( const BasicVec<T> data_vec ) {
        _rese = data_vec.size();
        _size = data_vec.size();
        if ( _size ) {
            cudaMalloc( &_data, sizeof( T ) * _rese );
            cudaMemcpy( _data, data_vec.ptr(), sizeof( T ) * _rese, cudaMemcpyHostToDevice );
        }
    }

    ~BasicVecGpu() {
        if ( _rese )
            cudaFree( _data );
    }

    operator BasicVec<T>() const {
        BasicVec<T> res( Size(), _rese );
        cudaMemcpy( res.ptr(), _data, sizeof( T ) * _rese, cudaMemcpyDeviceToHost );
        return res;
    }

    operator T*() const{
        return _data;
    }

    T *reserve_without_copy( ST want ) {
        if ( want != _rese ) {
            if ( _rese )
                cudaFree( _data );
            _rese = want;
            if ( want )
                CSC(( cudaMalloc( &_data, sizeof( T ) * want ) ));
        }
        return _data;
    }

    T *reserve_without_copy_at_least( ST want ) {
        if ( want > _rese ) {
            if ( _rese )
                cudaFree( _data );
            _rese = want;
            CSC(( cudaMalloc( &_data, sizeof( T ) * want ) ));
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

    void copy_to( BasicVec<T> &res ) const {
        res.resize( _size );
        copy_to( res.ptr() );
    }

    void copy_to( T *res ) const {
        cudaMemcpy( res, _data, sizeof( T ) * _size, cudaMemcpyDeviceToHost );
    }

    template<class Os>
    void write_str( Os &os ) const {
        os << operator BasicVec<T>();
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
