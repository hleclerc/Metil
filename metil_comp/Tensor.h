#ifndef TENSOR_H
#define TENSOR_H

#include "BasicVec.h"

namespace Metil {

/**
  static order
*/
template<class T,int order_=-1,int prereservation=1>
class Tensor {
public:
    Tensor() {}

    Tensor( SetSize, int i ) : _size( i ), _accu( i ), _data( SetSize(), i ) {}
    Tensor( SetSize, int i, int j ) : _size( i, j ), _accu( i, i * j ), _data( SetSize(), i * j ) {}
    Tensor( SetSize, int i, int j, int k ) : _size( i, j, k ), _accu( i, i * j, i * j * k ), _data( SetSize(), i * j * k ) {}
    Tensor( SetSize, int i, int j, int k, int l ) : _size( i, j, k, l ), _accu( i, i * j, i * j * k, i * j * k * l ), _data( SetSize(), i * j * k * l ) {}

    template<class TV>
    void resize( const TV &size ) {
        for(int i=0;i<order();++i)
            ASSERT( _size[ i ] == 0, "TODO : resize non void tensors" );

        //
        if ( not size.size() ) {
            _size.resize( 0 );
            _accu.resize( 0 );
            return;
        }
        _size      = size;
        //
        _accu.resize( _size.size() );
        _accu[ 0 ] = size[ 0 ];
        for(int i=1;i<order();++i)
            _accu[ i ] = _accu[ i - 1 ] * _size[ i ];
        _data.resize( _accu.back() );
    }

    void resize( int i ) { resize( BasicVec<int,1>( i ) ); }
    void resize( int i, int j ) { resize( BasicVec<int,2>( i, j ) ); }
    void resize( int i, int j, int k ) { resize( BasicVec<int,3>( i, j, k ) ); }
    void resize( int i, int j, int k, int l ) { resize( BasicVec<int,4>( i, j, k, l ) ); }

    template<class T2>
    void set( const T2 &val ) { _data.set( val ); }

    int order() const { return _size.size(); }
    BasicVec<int,order_,2> size() const { return _size; }
    int nb_terms() const { if ( _accu.size() ) return _accu.back(); return 0; }

    const T &operator[]( int i ) const { return _data[ i ]; }
    T &operator[]( int i ) { return _data[ i ]; }

    const T &operator()( int i, int j ) const { return _data[ _accu[0] * j + i ]; }
          T &operator()( int i, int j )       { return _data[ _accu[0] * j + i ]; }

    const T &operator()( int i, int j, int k ) const { return _data[ _accu[1] * k + _accu[0] * j + i ]; }
          T &operator()( int i, int j, int k )       { return _data[ _accu[1] * k + _accu[0] * j + i ]; }

    const T &operator()( int i, int j, int k, int l ) const { return _data[ _accu[2] * l + _accu[1] * k + _accu[0] * j + i ]; }
          T &operator()( int i, int j, int k, int l )       { return _data[ _accu[2] * l + _accu[1] * k + _accu[0] * j + i ]; }

    template<class TV> const T &operator()( const TV &v ) const { return _data[ offset( v ) ]; }
    template<class TV>       T &operator[]( const TV &v )       { return _data[ offset( v ) ]; }

    template<class TV> int offset( const TV &v ) {
        int res = v[ 0 ];
        for(int s=0;s<_size.size();)
            res += _accu[ s ] * v[ ++s ];
        return res;
    }

    void write_to_stream( Stream &os ) const {
        if ( order() ) {
            int off = 0;
            write_to_stream( os, 0, off );
        }
    }

private:
    void write_to_stream( Stream &os, int ord, int &off ) const {
        if ( ord == order() - 1 ) {
            os << _data[ off++ ];
            for(int i=1;i<_size[ ord ];++i)
                os << ' ' << _data[ off++ ];
        } else {
            for(int i=0;i<_size[ ord ];++i) {
                if ( off ) os << '\n';
                write_to_stream( os, ord+1, off );
            }
        }
    }
    
    BasicVec<int,order_,4> _size;
    BasicVec<int,order_,4> _accu;
    BasicVec<T,-1,prereservation> _data;
};

} // namespace Metil

#endif // TENSOR_H
