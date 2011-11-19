#ifndef BASICIMGGPU_H
#define BASICIMGGPU_H

#include "MathBasicVec.h"
#include "BasicVecGpu.h"
#include "String.h"

BEG_METIL_NAMESPACE

template<class Op,class T,int nt> __global__
void apply_kernel( Op op, T *data, BasicVec<int,2> size, N<nt> ) {
    int o = blockIdx.x * nt + threadIdx.x;
    if ( o < product( size ) ) {
        int x = o % size[ 0 ];
        int y = o / size[ 0 ];
        op( data[ o ], svec( x, y ) );
    }
}

template<class T,int dim>
struct BasicImgGpu {
    typedef BasicVec<int,dim> TV;

    BasicImgGpu() {}
    BasicImgGpu( TV size ) : size( size ), data( Size(), product( size ) ) {}
    
    void set_size( TV s ) {
         size = s;
         data.resize_without_copy( product( s ) );
    }

    template<class Hdf,class TS>
    void write_to( Hdf &hdf, const TS &name ) {
        BasicVec<T> tmp = data;
        hdf.write( name, tmp.ptr(), size );
    }

    template<class Op,int nb_threads>
    void apply( const Op &op, N<nb_threads> n ) {
        CSC(( apply_kernel<<< iDivUp( product( size ), nb_threads ), nb_threads >>>( op, data.ptr(), size, n ) ));
    }

    TV size;
    BasicVecGpu<T> data;
};

END_METIL_NAMESPACE

#endif // BASICIMGGPU_H
