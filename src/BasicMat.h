#ifndef BASICMAT_H
#define BASICMAT_H

#include "BasicVec.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

template<class T_,int dim,bool sym=false>
struct BasicMat;

template<class T_,int dim>
struct BasicMat<T_,dim,true> {
    typedef T_ T;
    static const int size = dim * ( dim + 1 ) / 2;

    __inline__ BasicMat() {}
    __inline__ BasicMat( T val ) : data( val ) {}

    __inline__ const T &sel_sec( int r, int c ) const { return data[ r * ( r + 1 ) / 2 + c ]; } ///< assuming c < r
    __inline__ T &sel_sec( int r, int c ) { return data[ r * ( r + 1 ) / 2 + c ]; } ///< assuming c < r

    __inline__ const T &operator()( int r, int c ) const { if ( r < c ) return sel_sec( c, r ); return sel_sec( r, c ); }
    __inline__ T &operator()( int r, int c ) { if ( r < c ) return sel_sec( c, r ); return sel_sec( r, c ); }

    __inline__ void operator+=( const BasicMat &m ) {
        data += m.data;
    }

    __inline__ void chol( int d = dim ) {
        for( int r = 0; r < d; ++r ) {
            for( int c = 0; c < r; ++c ) {
                T val = sel_sec( r, c );
                for( int i = 0; i < c; ++i )
                    val -= sel_sec( r, i ) * sel_sec( c, i );
                sel_sec( r, c ) = val * sel_sec( c, c );
            }
            T val = sel_sec( r, r );
            for( int i = 0; i < r; ++i )
                val -= pow( sel_sec( r, i ), 2 );
            sel_sec( r, r ) = 1 / sqrt( val );
        }

    }

    __inline__ BasicVec<T,dim> solve_using_cholesky( BasicVec<T,dim> sol, int d = dim ) {
        BasicVec<T,dim> res;
        for( int r = 0; r < d; ++r ) {
            T v = sol[ r ];
            for( int c = 0; c < r; ++c )
                v -= sel_sec( r, c ) * res[ c ];
            res[ r ] = v * sel_sec( r, r );
        }

        for( int r = d- 1; r >= 0; --r ) {
            T v = res[ r ];
            for( int c = r + 1; c < d; ++c )
                v -= sel_sec( c, r ) * res[ c ];
            res[ r ] = v * sel_sec( r, r );
        }

        return res;
    }

    __inline__ void add_l_Id( T l ) {
        for( int c = 0; c < dim; ++c )
            sel_sec( c, c ) += l;
    }

    __inline__ BasicVec<T,dim> operator*( const BasicVec<T,dim> &vec ) const {
        BasicVec<T,dim> res( 0 );
        for( int r = 0; r < dim; ++r )
            for( int c = 0; c < dim; ++c )
                res[ r ] += operator()( r, c ) * vec[ c ];
        return res;
    }

    template<class TS>
    void write_str( TS &os ) const {
        for( int r = 0; r < dim; ++r ) {
            for( int c = 0; c < dim; ++c )
                os << ( c ? " " : "" ) << operator()( r, c );
            os << "\n";
        }
    }

    BasicVec<T,size> data;
};

END_METIL_NAMESPACE;

#endif // BASICMAT_H
