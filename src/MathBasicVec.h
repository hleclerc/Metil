#ifndef MathBasicVec_h
#define MathBasicVec_h
// #include </home/casimir/NVIDIA_GPU_Computing_SDK/C/common/inc/cutil_math.h>

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

//template<class T,int s> __inline__ BasicVec<T,s> operator+( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a[ 0 ] + b[ 0 ], a[ 1 ] + b[ 1 ], a[ 2 ] + b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator-( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a[ 0 ] - b[ 0 ], a[ 1 ] - b[ 1 ], a[ 2 ] - b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator*( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a[ 0 ] * b[ 0 ], a[ 1 ] * b[ 1 ], a[ 2 ] * b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator/( const BasicVec<T,s> &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a[ 0 ] / b[ 0 ], a[ 1 ] / b[ 1 ], a[ 2 ] / b[ 2 ] ); }

//template<class T,int s> __inline__ BasicVec<T,s> operator+( const T &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a + b[ 0 ], a + b[ 1 ], a + b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator-( const T &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a - b[ 0 ], a - b[ 1 ], a - b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator*( const T &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a * b[ 0 ], a * b[ 1 ], a * b[ 2 ] ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator/( const T &a, const BasicVec<T,s> &b ) { return BasicVec<T,s>( a / b[ 0 ], a / b[ 1 ], a / b[ 2 ] ); }

//template<class T,int s> __inline__ BasicVec<T,s> operator+( const BasicVec<T,s> &a, const T &b ) { return BasicVec<T,s>( a[ 0 ] + b, a[ 1 ] + b, a[ 2 ] + b ); }
template<class T,int s> __inline__ BasicVec<T,s> operator-( const BasicVec<T,s> &a, const T &b ) { BasicVec<T,s> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = a[ i ] - b; return res; }
//template<class T,int s> __inline__ BasicVec<T,s> operator*( const BasicVec<T,s> &a, const T &b ) { return BasicVec<T,s>( a[ 0 ] * b, a[ 1 ] * b, a[ 2 ] * b ); }
//template<class T,int s> __inline__ BasicVec<T,s> operator/( const BasicVec<T,s> &a, const T &b ) { return BasicVec<T,s>( a[ 0 ] / b, a[ 1 ] / b, a[ 2 ] / b ); }


template<class T,int dim>
BasicVec<T,dim> min( const BasicVec<T,dim> &a, const BasicVec<T,dim> &b ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = min( a[ i ], b[ i ] ); return res; }

template<class T,int dim>
BasicVec<T,dim> max( const BasicVec<T,dim> &a, const BasicVec<T,dim> &b ) { using namespace std; BasicVec<T,dim> res; for( int i = 0; i < a.size(); ++i ) res[ i ] = max( a[ i ], b[ i ] ); return res; }

template<class T,int dim>
T min( const BasicVec<T,dim> &a ) { T res = a[ 0 ]; for( int i = 1; i < a.size(); ++i ) res = min( res, a[ i ] ); return res; }

template<class T,int dim>
T max( const BasicVec<T,dim> &a ) { T res = a[ 0 ]; for( int i = 1; i < a.size(); ++i ) res = max( res, a[ i ] ); return res; }

template<class T,int dim>
T product( const BasicVec<T,dim> &a ) { T res = 1; for( int i = 0; i < a.size(); ++i ) res *= a[ i ]; return res; }

/// [ a b c d ] -> [ 1 a a*b a*b*c ]
template<class T,int dim>
BasicVec<T,dim> cum( const BasicVec<T,dim> &S ) {
    BasicVec<T,dim> res;
    for( int d = 0, c = 1; d < dim; c *= S[ d++ ] )
        res[ d ] = c;
    return res;
}

END_METIL_NAMESPACE

#endif // MathBasicVec_h
