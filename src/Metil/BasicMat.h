#ifndef BASICMAT_H
#define BASICMAT_H

#include "BasicVec.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

template<class T_,int dim,bool sym=false,bool diag=false>
struct BasicMat;

// sym
template<class T_,int dim>
struct BasicMat<T_,dim,true,false> {
    typedef T_ T;
    static const int size = dim * ( dim + 1 ) / 2;

    __inline__ BasicMat() {}
    __inline__ BasicMat( T val ) : data( val ) {}

    int nb_rows() const { return dim; }
    int nb_cols() const { return dim; }

    __inline__ const T &sec_sel( int r, int c ) const { return data[ r * ( r + 1 ) / 2 + c ]; } ///< assuming c <= r
    __inline__ T &sec_sel( int r, int c ) { return data[ r * ( r + 1 ) / 2 + c ]; } ///< assuming c <= r

    __inline__ const T &operator()( int r, int c ) const { return r < c ? sec_sel( c, r ) : sec_sel( r, c ); }
    __inline__ T &operator()( int r, int c ) { return r < c ? sec_sel( c, r ) : sec_sel( r, c ); }

    __inline__ void operator+=( const BasicMat &m ) {
        data += m.data;
    }

    __inline__ void operator=( const T &v ) {
        data = v;
    }

    __inline__ void set( T val ) { data.set( val ); }

    
    __inline__ void complete_diag( T c = 0 ) {
        for( int i = 0; i < dim; ++i )
            operator()( i, i ) += operator()( i, i ) == 0;
        T m = 0;
        for( int i = 0; i < dim; ++i )
            m = max( m, abs( operator()( i, i ) ) );
        for( int i = 0; i < dim; ++i )
            operator()( i, i ) += c * m;
    }
    
    
    __inline__ void chol( int d = dim ) {
        for( int r = 0; r < d; ++r ) {
            for( int c = 0; c < r; ++c ) {
                T val = sec_sel( r, c );
                for( int i = 0; i < c; ++i )
                    val -= sec_sel( r, i ) * sec_sel( c, i );
                sec_sel( r, c ) = val * sec_sel( c, c );
            }
            T val = sec_sel( r, r );
            for( int i = 0; i < r; ++i )
                val -= pow( sec_sel( r, i ), 2 );
            sec_sel( r, r ) = 1 / sqrt( val );
        }

    }

    __inline__ BasicVec<T,dim> solve_using_cholesky( BasicVec<T,dim> sol, int d = dim ) const {
        BasicVec<T,dim> res;
        for( int r = 0; r < d; ++r ) {
            T v = sol[ r ];
            for( int c = 0; c < r; ++c )
                v -= sec_sel( r, c ) * res[ c ];
            res[ r ] = v * sec_sel( r, r );
        }

        for( int r = d- 1; r >= 0; --r ) {
            T v = res[ r ];
            for( int c = r + 1; c < d; ++c )
                v -= sec_sel( c, r ) * res[ c ];
            res[ r ] = v * sec_sel( r, r );
        }

        return res;
    }

    __inline__ void add_l_Id( T l ) {
        for( int c = 0; c < dim; ++c )
            sec_sel( c, c ) += l;
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

/// non symetric
template<class T_,int dim>
struct BasicMat<T_,dim,false,false> {
    typedef T_ T;
    static const int size = dim * dim;

    __inline__ BasicMat() {}
    __inline__ BasicMat( T val ) : data( val ) {}

    int nb_rows() const { return dim; }
    int nb_cols() const { return dim; }

    __inline__ const T &sec_sel( int r, int c ) const { return data[ r * dim + c ]; } ///< assuming c <= r
    __inline__ T &sec_sel( int r, int c ) { return data[ r * dim + c ]; } ///< assuming c <= r

    __inline__ const T &operator()( int r, int c ) const { return sec_sel( r, c ); }
    __inline__ T &operator()( int r, int c ) { return sec_sel( r, c ); }

    __inline__ void operator+=( const BasicMat &m ) {
        data += m.data;
    }

    __inline__ void operator=( const T &v ) {
        data = v;
    }

    __inline__ void set( T val ) { data.set( val ); }

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

    template<class Hdf,class TS>
    void write_to( Hdf &hdf, const TS &name ) {
        BasicVec<int,2> s( dim, dim );
        hdf.write( name, data.ptr(), s );
    }

    BasicVec<T,size> data;
};


// diag
template<class T_,int dim>
struct BasicMat<T_,dim,true,true> {
    typedef T_ T;
    static const int size = dim;

    __inline__ BasicMat() {}
    __inline__ BasicMat( T val ) : data( val ) {}

    int nb_rows() const { return dim; }
    int nb_cols() const { return dim; }

    __inline__ const T &sec_sel( int r, int c ) const { return data[ r ]; }
    __inline__ T &sec_sel( int r, int c ) { return data[ r ]; }

    __inline__ T operator()( int r, int c ) const { return r == c ? data[ r ] : 0; }
    __inline__ T &operator()( int r, int c ) { return data[ r ]; } ///< hum !!!

    __inline__ void operator+=( const BasicMat &m ) { data += m.data; }

    __inline__ void operator=( const T &v ) { data = v; }

    __inline__ void set( T val ) { data.set( val ); }

    __inline__ void chol( int d = dim ) {
        for( int r = 0; r < d; ++r )
            sec_sel( r, r ) = 1 / sqrt( sec_sel( r, r ) );
    }

    __inline__ BasicVec<T,dim> solve_using_cholesky( BasicVec<T,dim> sol, int d = dim ) const {
        BasicVec<T,dim> res;
        for( int r = 0; r < d; ++r )
            res[ r ] = sol[ r ] * sec_sel( r, r ) * sec_sel( r, r );
        return res;
    }

    __inline__ void add_l_Id( T l ) {
        for( int c = 0; c < dim; ++c )
            sec_sel( c, c ) += l;
    }

    __inline__ BasicVec<T,dim> operator*( const BasicVec<T,dim> &vec ) const {
        BasicVec<T,dim> res( 0 );
        for( int r = 0; r < dim; ++r )
            res[ r ] += sec_sel( r, r ) * vec[ r ];
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
