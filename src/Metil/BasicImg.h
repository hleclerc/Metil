#ifndef BASICIMG_H
#define BASICIMG_H

#include "MathBasicVec.h"

BEG_METIL_NAMESPACE

template<class T,int dim>
struct BasicImg {
    typedef BasicVec<int,dim> TV;

    BasicImg() {}
    BasicImg( TV size ) : size( size ), data( Size(), product( size ) ) {}

    void resize( TV s ) {
        size = s;
        data.resize( product( s ) );
    }

    const T &operator()( int x, int y ) const { return data[ y * size[ 0 ] + x ]; }
    T &operator()( int x, int y ) { return data[ y * size[ 0 ] + x ]; }
    
    const T *ptr() const { return data.ptr(); }
    T *ptr() { return data.ptr(); }

    template<class F>
    T interp( F x, F y ) const {
        int xi = x, yi = y;
        F xf = x - xi, yf = y - yi;
        return ( 1 - xf ) * ( 1 - yf ) * operator()( xi + 0, yi + 0 ) + 
               ( 0 + xf ) * ( 1 - yf ) * operator()( xi + 1, yi + 0 ) + 
               ( 1 - xf ) * ( 0 + yf ) * operator()( xi + 0, yi + 1 ) + 
               ( 0 + xf ) * ( 0 + yf ) * operator()( xi + 1, yi + 1 );
    }

    template<class Hdf,class TS>
    void write_to( Hdf &hdf, const TS &name ) {
        BasicVec<T> tmp = data;
        hdf.write( name, tmp.ptr(), size );
    }

    template<class Hdf,class TS>
    void read_from( const Hdf &hdf, const TS &name ) {
        // size
        BasicVec<int,dim> s;
        hdf.read_size( name, s );
        resize( s );
        // data
        hdf.read_data( name, data.ptr(), s, s );
    }

    TV size;
    BasicVec<T> data;
};

END_METIL_NAMESPACE

#endif // BASICIMG_H
