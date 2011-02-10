#include "MetilString.h"

#ifndef VAL_H
#define VAL_H

#include "EnableIf.h"
#include "IsAScalar.h"
#include "IsAnInteger.h"
#include "Level1/NewAndRefNumber.h"

BEG_METIL_NAMESPACE;

/**
  Scalar type
*/
class Val : public Level1::MO {
public:
    Val() { type = &Level1::metil_type_cst_Cst_0; }
    Val( const Level1::MO &mo ) : Level1::MO( mo ) {}

    template<class T>
    Val( const T &val ) : Level1::MO( Level1::NEW_Number( val ) ) {}

    template<class T>
    Val( Ref, T &val ) : Level1::MO( Level1::REF_Number( val ) ) {}

    Val( const String &str );
    Val( const char   *str );

    ~Val() { type->del( *this ); }

    Val &operator=( const Val &v ) { CM_2( reassign, *this, v ); return *this; }

    Val operator-() const { return CM_1( neg, *this ); }

    Val operator+( const Val &b ) const { return CM_2( add, *this, b ); }
    Val operator-( const Val &b ) const { return CM_2( sub, *this, b ); }
    Val operator*( const Val &b ) const { return CM_2( mul, *this, b ); }
    Val operator/( const Val &b ) const { return CM_2( div, *this, b ); }
    Val operator%( const Val &b ) const { return CM_2( mod, *this, b ); }

    Val operator&( const Val &b ) const { return CM_2( bitwise_and, *this, b ); }
    Val operator|( const Val &b ) const { return CM_2( bitwise_or , *this, b ); }
    Val operator^( const Val &b ) const { return CM_2( bitwise_xor, *this, b ); }

    // Val operator&&( const Val &b ) const { return CM_2( boolean_and, *this, b ); }
    // Val operator||( const Val &b ) const { return CM_2( boolean_or , *this, b ); }

    Val &operator+=( const Val &b ) { CM_2( self_add, *this, b ); return *this; }
    Val &operator-=( const Val &b ) { CM_2( self_sub, *this, b ); return *this; }
    Val &operator*=( const Val &b ) { CM_2( self_mul, *this, b ); return *this; }
    Val &operator/=( const Val &b ) { CM_2( self_div, *this, b ); return *this; }
    Val &operator%=( const Val &b ) { CM_2( self_mod, *this, b ); return *this; }

    template<class T> Val &operator+=( T b ) { return *this += Val( b ); }
    template<class T> Val &operator-=( T b ) { return *this -= Val( b ); }
    template<class T> Val &operator*=( T b ) { return *this *= Val( b ); }
    template<class T> Val &operator/=( T b ) { return *this /= Val( b ); }
    template<class T> Val &operator%=( T b ) { return *this %= Val( b ); }

    Val operator< ( const Val &b ) const { return CM_2( inf  , *this, b ); }
    Val operator<=( const Val &b ) const { return CM_2( infeq, *this, b ); }
    Val operator> ( const Val &b ) const { return CM_2( sup  , *this, b ); }
    Val operator>=( const Val &b ) const { return CM_2( supeq, *this, b ); }
    Val operator==( const Val &b ) const { return CM_2( equal, *this, b ); }
    Val operator!=( const Val &b ) const { return CM_2( noteq, *this, b ); }

    operator bool() const { return type->convert_to_Bool( *this ); }
    operator SI32() const { return type->convert_to_SI32( *this ); }
    operator SI64() const { return type->convert_to_SI64( *this ); }
    operator FP32() const { return type->convert_to_FP32( *this ); }
    operator FP64() const { return type->convert_to_FP64( *this ); }
    operator FP80() const { return type->convert_to_FP80( *this ); }

    static Val read_from_type_name( const char *&name );
};

// function( Val, Val )
inline Val pow  ( const Val &a, const Val &b ) { return CM_2( pow  , a, b ); }
inline Val mod  ( const Val &a, const Val &b ) { return CM_2( mod  , a, b ); }
inline Val atan2( const Val &a, const Val &b ) { return CM_2( atan2, a, b ); }
inline Val quo  ( const Val &a, const Val &b ) { return CM_2( quo  , a, b ); }

inline bool always_equal( const Val &a, const Val &b ) { return CM_2( always_equal, a, b ); }

// function( Scalar, Val )
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator+ ( T a, const Val &b ) { return Val( a ) + b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator- ( T a, const Val &b ) { return Val( a ) - b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator* ( T a, const Val &b ) { return Val( a ) * b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator/ ( T a, const Val &b ) { return Val( a ) / b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator% ( T a, const Val &b ) { return Val( a ) % b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator& ( T a, const Val &b ) { return Val( a ) & b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator| ( T a, const Val &b ) { return Val( a ) | b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator^ ( T a, const Val &b ) { return Val( a ) ^ b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator&&( T a, const Val &b ) { return Val( a ) && b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator||( T a, const Val &b ) { return Val( a ) || b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator==( T a, const Val &b ) { return Val( a ) == b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator< ( T a, const Val &b ) { return Val( a ) <  b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator<=( T a, const Val &b ) { return Val( a ) <= b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator> ( T a, const Val &b ) { return Val( a ) >  b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator>=( T a, const Val &b ) { return Val( a ) >= b; }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T pow       ( T a, const Val &b ) { return pow  ( Val( a ), b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T mod       ( T a, const Val &b ) { return mod  ( Val( a ), b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T atan2     ( T a, const Val &b ) { return atan2( Val( a ), b ); }

template<class T> typename EnableIf<IsAScalar<T>::res,T>::T &operator+=( T &a, const Val &b ) { a = a + b; return a; }
template<class T> typename EnableIf<IsAScalar<T>::res,T>::T &operator-=( T &a, const Val &b ) { a = a - b; return a; }
template<class T> typename EnableIf<IsAScalar<T>::res,T>::T &operator*=( T &a, const Val &b ) { a = a * b; return a; }
template<class T> typename EnableIf<IsAScalar<T>::res,T>::T &operator/=( T &a, const Val &b ) { a = a / b; return a; }
template<class T> typename EnableIf<IsAScalar<T>::res,T>::T &operator%=( T &a, const Val &b ) { a = a % b; return a; }

// function( Val, Scalar )
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator+ ( const Val &a, T b ) { return a + Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator- ( const Val &a, T b ) { return a - Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator* ( const Val &a, T b ) { return a * Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator/ ( const Val &a, T b ) { return a / Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator% ( const Val &a, T b ) { return a % Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator& ( const Val &a, T b ) { return a & Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator| ( const Val &a, T b ) { return a | Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator^ ( const Val &a, T b ) { return a ^ Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator&&( const Val &a, T b ) { return a && Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator||( const Val &a, T b ) { return a || Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator==( const Val &a, T b ) { return a == Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator< ( const Val &a, T b ) { return a <  Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator<=( const Val &a, T b ) { return a <= Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator> ( const Val &a, T b ) { return a >  Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator>=( const Val &a, T b ) { return a >= Val( b ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T pow       ( const Val &a, T b ) { return pow  ( a, Val( b ) ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T mod       ( const Val &a, T b ) { return mod  ( a, Val( b ) ); }
template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T atan2     ( const Val &a, T b ) { return atan2( a, Val( b ) ); }

// function( Val )
#define DECL_MET( T, N ) inline Val N( const Val &v ) { return v.type->N( v ); }
#include "Level1/DeclMethodsUnaryArithmetic.h"
#undef DECL_MET

template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T inv ( T b ) { return inv ( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T sin ( T b ) { return sin ( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T cos ( T b ) { return cos ( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T tan ( T b ) { return tan ( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T asin( T b ) { return asin( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T acos( T b ) { return acos( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T atan( T b ) { return atan( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T sqrt( T b ) { return sqrt( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T log ( T b ) { return log ( Val( b ) ); }
template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T exp ( T b ) { return exp ( Val( b ) ); }


extern Val zero;              // 0
extern Val one;               // 1
extern Val two;               // 2
extern Val three;             // 3
extern Val four;              // 4
extern Val five;              // 5
extern Val minus_one;         // -1
//extern Val pi;                // 3.14159...
//extern Val i;                 // sqrt(-1)
//extern Val one_half;          // 1/2
//extern Val minus_one_half;    // -1/2
//extern Val one_quarter;       // 1/4
//extern Val minus_one_quarter; // -1/4
//extern Val inf;               // infinity
//extern Val exp_1;             // exp( 1 )
//extern Val nan;               // exp( 1 )
//
//extern Val zero_as_PI32;      // 0
//extern Val one_as_PI32;       // 1
//extern Val minus_one_as_NI32; // -1
//

extern Val _0; // first arg
extern Val _1; // first arg
extern Val _2; // first arg


END_METIL_NAMESPACE;

#endif // VAL_H
