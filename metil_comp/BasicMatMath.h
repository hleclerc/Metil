#ifndef MATMATH_H
#define MATMATH_H

#include "VecMath.h"
#include "BasicMat.h"

namespace Metil {

template<class T,int s>
void cholesky( BasicMat<T,Sym<s> > &m ) {
    T *ptr = m.ptr();
    for(int r=0;r<m.nb_rows();++r) {
        int o_r = r * ( r + 1 ) / 2;
        for(int c=0;c<r;++c) {
            int o_c = c * ( c + 1 ) / 2;
            T tmp = ptr[ o_r + c ];
            for(int i=0;i<c;++i)
                tmp -= ptr[ o_c + i ] * ptr[ o_r + i ];
            ptr[ o_r + c ] = tmp * ptr[ o_c + c ];
        }
        T tmp = ptr[ o_r + r ];
        for(int i=0;i<r;++i)
            tmp -= ptr[ o_r + i ] * ptr[ o_r + i ];
        ptr[ o_r + r ] = rsqrt( tmp );
    }
}

template<class T,int s,int t,int u>
void cholesky_solve( const BasicMat<T,Sym<s> > &A, const BasicVec<double,t> &B, BasicVec<double,u> &result ) {
    int n = A.nb_rows();
    const T *ptr = A.ptr();
    result.resize( n );
    //
    for(int r=0;r<n;++r) {
        int o_r = r * ( r + 1 ) / 2;
        T tmp = B[ r ];
        for(int c=0;c<r;++c)
            tmp -= result[ c ] * ptr[ o_r + c ];
        result[ r ] = tmp * ptr[ o_r + r ];
    }
    //
    for(int r=n-1;r>=0;--r) {
        int o_r = r * ( r + 1 ) / 2;
        T tmp = result[ r ] * ptr[ o_r + r ];
        result[ r ] = tmp;
        for(int c=r-1;c>=0;--c)
            result[ c ] -= ptr[ o_r + c ] * tmp;
    }
}

template<class T,int s,int u,int v>
Vec<T,s> operator*( const BasicMat<T,Gen<s,u> > &m, const BasicVec<T,v> &vec ) {
    if ( not m.nb_cols() )
        return BasicVec<T,s>( SetSize(), m.nb_rows(), 0 );
    //
    BasicVec<T,s> res( SetSize(), m.nb_rows() );
    for(int r=0;r<m.nb_rows();++r) {
        T tmp = m( r, 0 ) * vec[ 0 ];
        for(int c=1;c<m.nb_cols();++c)
            tmp += m( r, c ) * vec[ c ];
        res[ r ] = tmp;
    }
}

template<class T,int s,int v>
Vec<T,s> operator*( const BasicMat<T,Sym<s> > &m, const BasicVec<T,v> &vec ) {
    if ( not m.nb_cols() )
        return BasicVec<T,s>( SetSize(), m.nb_rows(), T( 0 ) );
    // TODO -> optimize
    BasicVec<T,s> res( SetSize(), m.nb_rows() );
    for(int r=0;r<m.nb_rows();++r) {
        T tmp = m( r, 0 ) * vec[ 0 ];
        for(int c=1;c<m.nb_cols();++c)
            tmp += m( r, c ) * vec[ c ];
        res[ r ] = tmp;
    }
    return res;
}

}

#endif // MATMATH_H
