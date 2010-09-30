#ifndef MATH_H
#define MATH_H

#include "IsAnInteger.h"
#include "IsSigned.h"
#include "EnableIf.h"

BEG_METIL_NAMESPACE


template<class T> bool is_positive( T a  ) { return a > 0; }
template<class T> bool is_negative( T a  ) { return a < 0; }

template<class T> bool is_equal_to_0( T a ) { return a == 0; }
template<class T> bool is_equal_to_1( T a ) { return a == 1; }

template<class T> bool eqz   ( T a ) { return is_equal_to_0( a ); }
template<class T> bool supeqz( T a ) { return a >= 0; }
template<class T> bool supz  ( T a ) { return a >  0; }
template<class T> bool infeqz( T a ) { return a <= 0; }
template<class T> bool infz  ( T a ) { return a <  0; }

template<class T0,class T1> bool boolean_xor( T0 a, T1 b ) { return bool( a ) ^ bool( b ); }


inline FP32 modf( FP32 a ) { return __builtin_modff( a, &a ); }
inline FP64 modf( FP64 a ) { return __builtin_modf ( a, &a ); }
inline FP80 modf( FP80 a ) { return __builtin_modfl( a, &a ); }

inline FP32 intf( FP32 a ) { __builtin_modff( a, &a ); return a; }
inline FP64 intf( FP64 a ) { __builtin_modf ( a, &a ); return a; }
inline FP80 intf( FP80 a ) { __builtin_modfl( a, &a ); return a; }

inline FP32 quo( FP32 a, FP32 b ) { return intf( a / b ); }
inline FP64 quo( FP64 a, FP64 b ) { return intf( a / b ); }
inline FP80 quo( FP80 a, FP80 b ) { return intf( a / b ); }

inline FP32 frexp( FP32 a, int *exp ) { return __builtin_frexpf( a, exp ); }
inline FP64 frexp( FP64 a, int *exp ) { return __builtin_frexp ( a, exp ); }
inline FP80 frexp( FP80 a, int *exp ) { return __builtin_frexpl( a, exp ); }

template<class T> bool is_odd( T a ) { return a % 2; }
inline bool is_odd( FP32 a ) { FP32 tmp = ( a + 1 ) / 2; return not modf( tmp ); }
inline bool is_odd( FP64 a ) { FP64 tmp = ( a + 1 ) / 2; return not modf( tmp ); }
inline bool is_odd( FP80 a ) { FP80 tmp = ( a + 1 ) / 2; return not modf( tmp ); }


template<class T> bool is_even( T a ) { return a % 2; }
inline bool is_even( FP32 a ) { FP32 tmp = a / 2; return not modf( tmp ); }
inline bool is_even( FP64 a ) { FP64 tmp = a / 2; return not modf( tmp ); }
inline bool is_even( FP80 a ) { FP80 tmp = a / 2; return not modf( tmp ); }

template<class T0,class T1> __inline__ T0 ceil( T0 a, T1 m ) {
    if ( not m )
        return a;
    return ( a + m - 1 ) / m * m;
}

template<class T0,class T1>
T0 iDivUp( T0 a, T1 b ) {
    return ( a + b - 1 ) / b;
}

template<class T> T abs( T a ) { return a >= 0 ? a : -a; }
inline FP32 abs( FP32  a ) { return __builtin_fabsf( a ); }
inline FP64 abs( FP64  a ) { return __builtin_fabs ( a ); }
inline FP80 abs( FP80  a ) { return __builtin_fabsl( a ); }

inline FP32 inv( FP32  a ) { return 1.0f / a; }
inline FP64 inv( FP64  a ) { return 1.0  / a; }
inline FP80 inv( FP80  a ) { return FP80( 1 ) / a; }

template<class T> inline SI32 sgn( T a ) { return is_positive( a ) - is_negative( a ); }

inline FP32 sqrt( FP32 a ) { return __builtin_sqrtf( a ); }
inline FP64 sqrt( FP64 a ) { return __builtin_sqrt ( a ); }
inline FP80 sqrt( FP80 a ) { return __builtin_sqrtl( a ); }

inline FP32 rsqrt( FP32 a ) { return inv( __builtin_sqrtf( a ) ); }
inline FP64 rsqrt( FP64 a ) { return inv( __builtin_sqrt ( a ) ); }
inline FP80 rsqrt( FP80 a ) { return inv( __builtin_sqrtl( a ) ); }

inline FP32 log( FP32 a ) { return __builtin_logf( a ); }
inline FP64 log( FP64 a ) { return __builtin_log ( a ); }
inline FP80 log( FP80 a ) { return __builtin_logl( a ); }

inline FP32 exp( FP32 a ) { return __builtin_expf( a ); }
inline FP64 exp( FP64 a ) { return __builtin_exp ( a ); }
inline FP80 exp( FP80 a ) { return __builtin_expl( a ); }

inline FP32 neg( FP32  a ) { return - a; }
inline FP64 neg( FP64  a ) { return - a; }
inline FP80 neg( FP80  a ) { return - a; }

inline FP32 sin( FP32 a ) { return __builtin_sinf( a ); }
inline FP64 sin( FP64 a ) { return __builtin_sin ( a ); }
inline FP80 sin( FP80 a ) { return __builtin_sinl( a ); }

inline FP32 cos( FP32 a ) { return __builtin_cosf( a ); }
inline FP64 cos( FP64 a ) { return __builtin_cos ( a ); }
inline FP80 cos( FP80 a ) { return __builtin_cosl( a ); }


inline FP32 tan( FP32 a ) { return __builtin_tanf( a ); }
inline FP64 tan( FP64 a ) { return __builtin_tan ( a ); }
inline FP80 tan( FP80 a ) { return __builtin_tanl( a ); }


inline FP32 asin( FP32 a ) { return __builtin_asinf( a ); }
inline FP64 asin( FP64 a ) { return __builtin_asin ( a ); }
inline FP80 asin( FP80 a ) { return __builtin_asinl( a ); }


inline FP32 acos( FP32 a ) { return __builtin_acosf( a ); }
inline FP64 acos( FP64 a ) { return __builtin_acos ( a ); }
inline FP80 acos( FP80 a ) { return __builtin_acosl( a ); }

// atan
inline FP32 atan( FP32 a ) { return __builtin_atanf( a ); }
inline FP64 atan( FP64 a ) { return __builtin_atan ( a ); }
inline FP80 atan( FP80 a ) { return __builtin_atanl( a ); }

// atan2
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T atan2( T a, FP32 b ) { return __builtin_atan2f( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T atan2( T a, FP64 b ) { return __builtin_atan2 ( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T atan2( T a, FP80 b ) { return __builtin_atan2l( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T atan2( FP32 a, T b ) { return __builtin_atan2f( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T atan2( FP64 a, T b ) { return __builtin_atan2 ( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T atan2( FP80 a, T b ) { return __builtin_atan2l( a, b ); }
inline FP32 atan2( FP32 a, FP32 b ) { return __builtin_atan2f( a, b ); }
inline FP32 atan2( FP32 a, FP64 b ) { return __builtin_atan2f( a, b ); }
inline FP32 atan2( FP32 a, FP80 b ) { return __builtin_atan2f( a, b ); }
inline FP32 atan2( FP64 a, FP32 b ) { return __builtin_atan2f( a, b ); }
inline FP64 atan2( FP64 a, FP64 b ) { return __builtin_atan2 ( a, b ); }
inline FP80 atan2( FP64 a, FP80 b ) { return __builtin_atan2l( a, b ); }
inline FP32 atan2( FP80 a, FP32 b ) { return __builtin_atan2f( a, b ); }
inline FP64 atan2( FP80 a, FP64 b ) { return __builtin_atan2 ( a, b ); }
inline FP80 atan2( FP80 a, FP80 b ) { return __builtin_atan2l( a, b ); }

// mod
inline FP32 mod_FP32( FP32 a, FP32 b ) { return a - quo( a, b ) * b; }
inline FP64 mod_FP64( FP64 a, FP64 b ) { return a - quo( a, b ) * b; }
inline FP80 mod_FP80( FP80 a, FP80 b ) { return a - quo( a, b ) * b; }

template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T mod( T a, FP32 b ) { return mod_FP32( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T mod( T a, FP64 b ) { return mod_FP64( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T mod( T a, FP80 b ) { return mod_FP80( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T mod( FP32 a, T b ) { return mod_FP32( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T mod( FP64 a, T b ) { return mod_FP64( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T mod( FP80 a, T b ) { return mod_FP80( a, b ); }
inline FP32 mod( FP32 a, FP32 b ) { return mod_FP32( a, b ); }
inline FP32 mod( FP32 a, FP64 b ) { return mod_FP32( a, b ); }
inline FP32 mod( FP32 a, FP80 b ) { return mod_FP32( a, b ); }
inline FP32 mod( FP64 a, FP32 b ) { return mod_FP32( a, b ); }
inline FP64 mod( FP64 a, FP64 b ) { return mod_FP64( a, b ); }
inline FP80 mod( FP64 a, FP80 b ) { return mod_FP80( a, b ); }
inline FP32 mod( FP80 a, FP32 b ) { return mod_FP32( a, b ); }
inline FP64 mod( FP80 a, FP64 b ) { return mod_FP64( a, b ); }
inline FP80 mod( FP80 a, FP80 b ) { return mod_FP80( a, b ); }

// pow
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T pow( T a, FP32 b ) { return __builtin_powf( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T pow( T a, FP64 b ) { return __builtin_pow ( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T pow( T a, FP80 b ) { return __builtin_powl( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP32>::T pow( FP32 a, T b ) { return __builtin_powf( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP64>::T pow( FP64 a, T b ) { return __builtin_pow ( a, b ); }
template<class T> inline typename EnableIf<IsAnInteger<T>::res,FP80>::T pow( FP80 a, T b ) { return __builtin_powl( a, b ); }
inline FP32 pow( FP32 a, FP32 b ) { return __builtin_powf( a, b ); }
inline FP32 pow( FP32 a, FP64 b ) { return __builtin_powf( a, b ); }
inline FP32 pow( FP32 a, FP80 b ) { return __builtin_powf( a, b ); }
inline FP32 pow( FP64 a, FP32 b ) { return __builtin_powf( a, b ); }
inline FP64 pow( FP64 a, FP64 b ) { return __builtin_pow ( a, b ); }
inline FP80 pow( FP64 a, FP80 b ) { return __builtin_powl( a, b ); }
inline FP32 pow( FP80 a, FP32 b ) { return __builtin_powf( a, b ); }
inline FP64 pow( FP80 a, FP64 b ) { return __builtin_pow ( a, b ); }
inline FP80 pow( FP80 a, FP80 b ) { return __builtin_powl( a, b ); }

template<class T0,class T1> inline T0 pow_by_positive_integer( T0 m, T1 e ) {
    if ( is_equal_to_0( e ) ) return 1;
    if ( is_equal_to_1( e ) ) return m;
    if ( is_odd       ( e ) ) return m * pow( m, e - 1u );
    T0 tmp = pow( m, e / 2u );
    return tmp * tmp;
}

template<class T0,class T1> inline typename EnableIf<IsAnInteger<T1>::res and IsSigned<T1>::res==false,T0>::T pow( T0 m, T1 e ) {
    return pow_by_positive_integer( m, e );
}

template<class T1,class T2>
T1 gcd( T1 a, T2 b ) {
    if ( b == 0 )
        return 0; // hum...
    if ( b == 1 )
        return 0;

    T1 old;
    while ( b ) {
        old = b;
        b = a % b;
        a = old;
    }
    return a;
}

#define MAX( a, b ) ( (a) < (b) ? (b) : (a) )
#define MIN( a, b ) ( (a) > (b) ? (b) : (a) )

template<class T> T min( const T &a, const T &b ) { return MIN( a, b ); }
template<class T> T max( const T &a, const T &b ) { return MAX( a, b ); }

template<class T> __inline__ void swap( T &a, T &b ) { T c = a; a = b; b = c; }
template<class T> __inline__ void swap_if( T &v_0, T &v_1, bool cond ) { if ( cond ) swap( v_0, v_1 ); }

//
//template<class T0,class T1> typename T0::DelayedValue operator+( const T0 &a, const T1 &b ) { return a.conv() + b; }
//template<class T0,class T1> typename T0::DelayedValue operator-( const T0 &a, const T1 &b ) { return a.conv() - b; }
//template<class T0,class T1> typename T0::DelayedValue operator*( const T0 &a, const T1 &b ) { return a.conv() * b; }
//template<class T0,class T1> typename T0::DelayedValue operator/( const T0 &a, const T1 &b ) { return a.conv() / b; }
//template<class T0,class T1> typename T0::DelayedValue operator%( const T0 &a, const T1 &b ) { return a.conv() % b; }



END_METIL_NAMESPACE

#endif // MATH_H
