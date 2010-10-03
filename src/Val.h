#ifndef VAL_H
#define VAL_H

//#include "EnableIf.h"
//#include "IsAScalar.h"
//#include "IsAnInteger.h"
//
//BEG_METIL_NAMESPACE;
//
//class Val : public Level1::MO {
//public:
//    #ifdef METIL_BOOSTRAP
//    Val() : MO( Level1::NEW_Number( 0 ) ) {}
//    Val( SI32 v ) : MO( Level1::NEW_Number( v ) ) {}
//    Val( SI64 v ) : MO( Level1::NEW_Number( v ) ) {}
//    #else
//    #endif
//    Val( const Level1::MO &mo ) : Level1::MO( mo ) {}
//
//    #define DECL_POD_CONSTRUCTOR( T ) \
//        Val( T v       ) { data = NEW( T, v ); type = &Level1::type_##T; } \
//        Val( Ref, T &v ) { data = (void *)&v;  type = &Level1::type_##T##_Ref; }
//
//    #ifndef METIL_BOOSTRAP
//    DECL_POD_CONSTRUCTOR( SI8  );
//    DECL_POD_CONSTRUCTOR( SI16 );
//    DECL_POD_CONSTRUCTOR( SI32 );
//    DECL_POD_CONSTRUCTOR( SI64 );
//
//    DECL_POD_CONSTRUCTOR( PI8  );
//    DECL_POD_CONSTRUCTOR( PI16 );
//    DECL_POD_CONSTRUCTOR( PI32 );
//    DECL_POD_CONSTRUCTOR( PI64 );
//
//    DECL_POD_CONSTRUCTOR( NI8  );
//    DECL_POD_CONSTRUCTOR( NI16 );
//    DECL_POD_CONSTRUCTOR( NI32 );
//    DECL_POD_CONSTRUCTOR( NI64 );
//    #endif
//
//    DECL_POD_CONSTRUCTOR( FP32 );
//    DECL_POD_CONSTRUCTOR( FP64 );
//    DECL_POD_CONSTRUCTOR( FP80 );
//
//    #undef DECL_POD_CONSTRUCTOR
//
//    ~Val() { type->del( *this ); }
//
//    Val &operator=( const Val &v ) { type->reassign( *this, v ); return *this; }
//
//    Val operator-() const { return type->neg( *this ); }
//
//    Val operator+( const Val &b ) const { return type->add( *this, b ); }
//    Val operator-( const Val &b ) const { return type->sub( *this, b ); }
//    Val operator*( const Val &b ) const { return type->mul( *this, b ); }
//    Val operator/( const Val &b ) const { return type->div( *this, b ); }
//    Val operator%( const Val &b ) const { return type->mod( *this, b ); }
//
//    Val operator&( const Val &b ) const { return type->bitwise_and( *this, b ); }
//    Val operator|( const Val &b ) const { return type->bitwise_or ( *this, b ); }
//    Val operator^( const Val &b ) const { return type->bitwise_xor( *this, b ); }
//
//    Val operator&&( const Val &b ) const { return type->boolean_and( *this, b ); }
//    Val operator||( const Val &b ) const { return type->boolean_or ( *this, b ); }
//
//    Val &operator+=( const Val &b ) { type->self_add( *this, b ); return *this; }
//    Val &operator-=( const Val &b ) { type->self_sub( *this, b ); return *this; }
//    Val &operator*=( const Val &b ) { type->self_mul( *this, b ); return *this; }
//    Val &operator/=( const Val &b ) { type->self_div( *this, b ); return *this; }
//    Val &operator%=( const Val &b ) { type->self_mod( *this, b ); return *this; }
//
//    template<class T> Val &operator+=( T b ) { return *this += Val( b ); }
//    template<class T> Val &operator-=( T b ) { return *this -= Val( b ); }
//    template<class T> Val &operator*=( T b ) { return *this *= Val( b ); }
//    template<class T> Val &operator/=( T b ) { return *this /= Val( b ); }
//    template<class T> Val &operator%=( T b ) { return *this %= Val( b ); }
//
//    Val operator< ( const Val &b ) const { return type->inf  ( *this, b ); }
//    Val operator<=( const Val &b ) const { return type->infeq( *this, b ); }
//    Val operator> ( const Val &b ) const { return type->sup  ( *this, b ); }
//    Val operator>=( const Val &b ) const { return type->supeq( *this, b ); }
//    Val operator==( const Val &b ) const { return type->equal( *this, b ); }
//
//    operator bool() const { return type->convert_to_Bool( *this ); }
//    operator SI32() const { return type->convert_to_SI32( *this ); }
//    operator SI64() const { return type->convert_to_SI64( *this ); }
//    operator FP32() const { return type->convert_to_FP32( *this ); }
//    operator FP64() const { return type->convert_to_FP64( *this ); }
//    operator FP80() const { return type->convert_to_FP80( *this ); }
//};
//
//// function( Val, Val )
//inline Val pow  ( const Val &a, const Val &b ) { return a.type->pow  ( a, b ); }
//inline Val mod  ( const Val &a, const Val &b ) { return a.type->mod  ( a, b ); }
//inline Val atan2( const Val &a, const Val &b ) { return a.type->atan2( a, b ); }
//inline Val quo  ( const Val &a, const Val &b ) { return a.type->quo  ( a, b ); }
//
//inline bool always_equal( const Val &a, const Val &b ) { return a.type->always_equal( a, b ); }
//
//// function( Scalar, Val )
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator+ ( T a, const Val &b ) { return Val( a ) + b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator- ( T a, const Val &b ) { return Val( a ) - b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator* ( T a, const Val &b ) { return Val( a ) * b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator/ ( T a, const Val &b ) { return Val( a ) / b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator% ( T a, const Val &b ) { return Val( a ) % b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator==( T a, const Val &b ) { return Val( a ) == b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator< ( T a, const Val &b ) { return Val( a ) <  b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator<=( T a, const Val &b ) { return Val( a ) <= b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator> ( T a, const Val &b ) { return Val( a ) >  b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator>=( T a, const Val &b ) { return Val( a ) >= b; }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T pow       ( T a, const Val &b ) { return pow  ( Val( a ), b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T mod       ( T a, const Val &b ) { return mod  ( Val( a ), b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T atan2     ( T a, const Val &b ) { return atan2( Val( a ), b ); }
//
//// function( Val, Scalar )
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator+ ( const Val &a, T b ) { return a + Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator- ( const Val &a, T b ) { return a - Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator* ( const Val &a, T b ) { return a * Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator/ ( const Val &a, T b ) { return a / Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator% ( const Val &a, T b ) { return a % Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator==( const Val &a, T b ) { return a == Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator< ( const Val &a, T b ) { return a <  Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator<=( const Val &a, T b ) { return a <= Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator> ( const Val &a, T b ) { return a >  Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T operator>=( const Val &a, T b ) { return a >= Val( b ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T pow       ( const Val &a, T b ) { return pow  ( a, Val( b ) ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T mod       ( const Val &a, T b ) { return mod  ( a, Val( b ) ); }
//template<class T> typename EnableIf<IsAScalar<T>::res,Val>::T atan2     ( const Val &a, T b ) { return atan2( a, Val( b ) ); }
//
//// function( Val )
//#define DECL_MET( T, N ) inline Val N( const Val &v ) { return v.type->N( v ); }
//#include "DeclMethodsUnaryArithmetic.h"
//#undef DECL_MET
//
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T inv ( T b ) { return inv ( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T sin ( T b ) { return sin ( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T cos ( T b ) { return cos ( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T tan ( T b ) { return tan ( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T asin( T b ) { return asin( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T acos( T b ) { return acos( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T atan( T b ) { return atan( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T sqrt( T b ) { return sqrt( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T log ( T b ) { return log ( Val( b ) ); }
//template<class T> typename EnableIf<IsAnInteger<T>::res,Val>::T exp ( T b ) { return exp ( Val( b ) ); }
//
//
//#ifndef METIL_BOOSTRAP
//extern Val zero;              // 0
//extern Val one;               // 1
//extern Val two;               // 2
//extern Val minus_one;         // -1
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
//#endif
//
//END_METIL_NAMESPACE

#endif // VAL_H
