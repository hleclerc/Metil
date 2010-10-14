#ifndef MathBasicVec_h
#define MathBasicVec_h
// #include </home/casimir/NVIDIA_GPU_Computing_SDK/C/common/inc/cutil_math.h>

#include "BasicVec.h"
#include "Math.h"

BEG_METIL_NAMESPACE

#define BT3 BasicVec<T,3>

template<class T>
__inline__ void operator-=( BT3 &a, const BT3 &b ) {
    a[ 0 ] -= b[ 0 ];
    a[ 1 ] -= b[ 1 ];
    a[ 2 ] -= b[ 2 ];
}

template<class T>
__inline__ T dot( const BT3 &a, const BT3 &b ) {
    return a[ 0 ] * b[ 0 ] + a[ 1 ] * b[ 1 ] + a[ 2 ] * b[ 2 ];
}

template<class T>
__inline__ T length( const BT3 &a ) {
    return sqrt( dot( a, a ) );
}

template<class T>
__inline__ BT3 normalized( const BT3 &a ) {
    T n = length( a );
    return BT3( a[ 0 ] / n, a[ 1 ] / n, a[ 2 ] / n );
}

template<class T>
__inline__ BT3 cross( const BT3 &a, const BT3 &b ) {
    return BT3( a[ 1 ] * b[ 2 ] - a[ 2 ] * b[ 1 ], a[ 2 ] * b[ 0 ] - a[ 0 ] * b[ 2 ], a[ 0 ] * b[ 1 ] - a[ 1 ] * b[ 0 ] ); 
}

template<class T> __inline__ BT3 operator+( const BT3 &a, const BT3 &b ) { return BT3( a[ 0 ] + b[ 0 ], a[ 1 ] + b[ 1 ], a[ 2 ] + b[ 2 ] ); }
template<class T> __inline__ BT3 operator-( const BT3 &a, const BT3 &b ) { return BT3( a[ 0 ] - b[ 0 ], a[ 1 ] - b[ 1 ], a[ 2 ] - b[ 2 ] ); }
template<class T> __inline__ BT3 operator*( const BT3 &a, const BT3 &b ) { return BT3( a[ 0 ] * b[ 0 ], a[ 1 ] * b[ 1 ], a[ 2 ] * b[ 2 ] ); }
template<class T> __inline__ BT3 operator/( const BT3 &a, const BT3 &b ) { return BT3( a[ 0 ] / b[ 0 ], a[ 1 ] / b[ 1 ], a[ 2 ] / b[ 2 ] ); }

template<class T> __inline__ BT3 operator+( const T &a, const BT3 &b ) { return BT3( a + b[ 0 ], a + b[ 1 ], a + b[ 2 ] ); }
template<class T> __inline__ BT3 operator-( const T &a, const BT3 &b ) { return BT3( a - b[ 0 ], a - b[ 1 ], a - b[ 2 ] ); }
template<class T> __inline__ BT3 operator*( const T &a, const BT3 &b ) { return BT3( a * b[ 0 ], a * b[ 1 ], a * b[ 2 ] ); }
template<class T> __inline__ BT3 operator/( const T &a, const BT3 &b ) { return BT3( a / b[ 0 ], a / b[ 1 ], a / b[ 2 ] ); }

template<class T> __inline__ BT3 operator+( const BT3 &a, const T &b ) { return BT3( a[ 0 ] + b, a[ 1 ] + b, a[ 2 ] + b ); }
template<class T> __inline__ BT3 operator-( const BT3 &a, const T &b ) { return BT3( a[ 0 ] - b, a[ 1 ] - b, a[ 2 ] - b ); }
template<class T> __inline__ BT3 operator*( const BT3 &a, const T &b ) { return BT3( a[ 0 ] * b, a[ 1 ] * b, a[ 2 ] * b ); }
template<class T> __inline__ BT3 operator/( const BT3 &a, const T &b ) { return BT3( a[ 0 ] / b, a[ 1 ] / b, a[ 2 ] / b ); }

#undef BT3

END_METIL_NAMESPACE

#endif // MathBasicVec_h
