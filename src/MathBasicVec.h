#ifndef MathBasicVec_h
#define MathBasicVec_h

#include "BasicVec.h"
#include "Math.h"

BEG_METIL_NAMESPACE

template<class T,int s>
__inline__ void operator-=( BasicVec<T,s> &a, const BasicVec<T,s> &b ) {
    for( int i = 0; i < a.size(); ++i )
        a[ i ] -= b[ i ];
}

template<class T,int s>
__inline__ T dot( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) {
    T res = 0;
    for( int i = 0; i < a.size(); ++i )
        res += a[ i ] * b[ i ];
    return res;
}

template<class T,int s>
__inline__ T norm_2_p2( const BasicVec<T,s> &a ) {
    T res = 0;
    for( int i = 0; i < a.size(); ++i )
        res += a[ i ] * a[ i ];
    return res;
}

template<class T,int s>
__inline__ T length( const BasicVec<T,s> &a ) {
    return sqrt( dot( a, a ) );
}

template<class T,int s>
__inline__ BasicVec<T,s> normalized( const BasicVec<T,s> &a ) {
    T n = length( a );
    return a / n;
}

template<class T>
__inline__ BasicVec<T,3> cross( const BasicVec<T,3> &a, const BasicVec<T,3> &b ) {
    return BasicVec<T,3>( a[ 1 ] * b[ 2 ] - a[ 2 ] * b[ 1 ], a[ 2 ] * b[ 0 ] - a[ 0 ] * b[ 2 ], a[ 0 ] * b[ 1 ] - a[ 1 ] * b[ 0 ] );
}

template<class T>
__inline__ T cross( const BasicVec<T,2> &a, const BasicVec<T,2> &b ) {
    return a[ 0 ] * b[ 1 ] - a[ 1 ] * b[ 0 ];
}

template<class T>
__inline__ T cross( const BasicVec<T,1> &a, const BasicVec<T,1> &b ) {
    return b[ 0 ] - a[ 0 ];
}

template<class T>
__inline__ BasicVec<T,3> rot( const BasicVec<T,3> &V, const BasicVec<T,3> &R ) {
    T a = length( R ) + 1e-40;
    T x = R[ 0 ] / a;
    T y = R[ 1 ] / a;
    T z = R[ 2 ] / a;
    T c = Metil::cos( a );
    T s = Metil::sin( a );
    return BasicVec<T,3>(
        ( x*x+(1-x*x)*c ) * V[ 0 ] + ( x*y*(1-c)-z*s ) * V[ 1 ] + ( x*z*(1-c)+y*s ) * V[ 2 ],
        ( y*x*(1-c)+z*s ) * V[ 0 ] + ( y*y+(1-y*y)*c ) * V[ 1 ] + ( y*z*(1-c)-x*s ) * V[ 2 ],
        ( z*x*(1-c)-y*s ) * V[ 0 ] + ( z*y*(1-c)+x*s ) * V[ 1 ] + ( z*z+(1-z*z)*c ) * V[ 2 ]
    );
}


template<class T,int s> __inline__ BasicVec<T,s> operator+( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] + b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator-( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] - b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator*( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] * b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator/( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] / b[ i ]; return res; }

template<class T,int s> __inline__ BasicVec<T,s> operator+( const T &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), b.size() ); for( int i = 0; i < b.size(); ++i ) res[ i ] = a + b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator-( const T &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), b.size() ); for( int i = 0; i < b.size(); ++i ) res[ i ] = a - b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator*( const T &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), b.size() ); for( int i = 0; i < b.size(); ++i ) res[ i ] = a * b[ i ]; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator/( const T &a, const BasicVec<T,s> &b ) { BasicVec<T,s> res( Size(), b.size() ); for( int i = 0; i < b.size(); ++i ) res[ i ] = a / b[ i ]; return res; }

template<class T,int s> __inline__ BasicVec<T,s> operator+( const BasicVec<T,s> &a, const T &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] + b; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator-( const BasicVec<T,s> &a, const T &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] - b; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator*( const BasicVec<T,s> &a, const T &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] * b; return res; }
template<class T,int s> __inline__ BasicVec<T,s> operator/( const BasicVec<T,s> &a, const T &b ) { BasicVec<T,s> res( Size(), a.size() ); for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] / b; return res; }

template<class T,int s> __inline__ void operator+=( BasicVec<T,s> &a, const T &b ) { for( int i = 0; i < a.size(); ++i ) a[ i ] += b; }
template<class T,int s> __inline__ void operator-=( BasicVec<T,s> &a, const T &b ) { for( int i = 0; i < a.size(); ++i ) a[ i ] -= b; }
template<class T,int s> __inline__ void operator*=( BasicVec<T,s> &a, const T &b ) { for( int i = 0; i < a.size(); ++i ) a[ i ] *= b; }
template<class T,int s> __inline__ void operator/=( BasicVec<T,s> &a, const T &b ) { for( int i = 0; i < a.size(); ++i ) a[ i ] /= b; }

template<class T,int dim>
__inline__ BasicVec<T,dim> ceil( const BasicVec<T,dim> &a ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = ceil( a[ i ] ); return res; }


template<class T,int dim>
__inline__ BasicVec<T,dim> iDivUp( const BasicVec<T,dim> &a, const BasicVec<T,dim> &b ) {
    BasicVec<T,dim> res;
    for( int i = 0; i < a.size(); ++i )
        res[ i ] = iDivUp( a[ i ], b[ i ] );
    return res;
}

template<class T,int dim>
__inline__ BasicVec<T,dim> abs( const BasicVec<T,dim> &a ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = abs( a[ i ] ); return res; }

template<class T,int dim>
__inline__ BasicVec<T,dim> min( const BasicVec<T,dim> &a, const BasicVec<T,dim> &b ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = min( a[ i ], b[ i ] ); return res; }

template<class T,int dim>
__inline__ BasicVec<T,dim> max( const BasicVec<T,dim> &a, const BasicVec<T,dim> &b ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = max( a[ i ], b[ i ] ); return res; }

template<class T,int dim>
__inline__ T min( const BasicVec<T,dim> &a ) { T res = a[ 0 ]; for( int i = 1; i < a.size(); ++i ) res = min( res, a[ i ] ); return res; }

template<class T,int dim>
__inline__ T max( const BasicVec<T,dim> &a ) { T res = a[ 0 ]; for( int i = 1; i < a.size(); ++i ) res = max( res, a[ i ] ); return res; }

template<class T,int dim>
__inline__ T product( const BasicVec<T,dim> &a ) { T res = 1; for( int i = 0; i < a.size(); ++i ) res *= a[ i ]; return res; }

/// [ a b c d ] -> [ 1 a a*b a*b*c ]
template<class T,int dim>
__inline__ BasicVec<T,dim> cum( const BasicVec<T,dim> &S ) {
    BasicVec<T,dim> res( Size(), S.size() );
    for( int d = 0, c = 1; d < S.size(); c *= S[ d++ ] )
        res[ d ] = c;
    return res;
}

END_METIL_NAMESPACE

#endif // MathBasicVec_h
