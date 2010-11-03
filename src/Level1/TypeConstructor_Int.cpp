#include "TypeConstructor_Int.h"
#include "DisplayInt.h"
#include "MethodWriter.h"
#include "../Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

// bootstrap methods for Int64
void metil_def_del__when__a__is__Int_s_64__pert__100( MO &a ) { DEL( reinterpret_cast<SI64 *>( a.data ) ); }
void metil_def_del__when__a__is__Int_s_32__pert__100( MO &a ) { DEL( reinterpret_cast<SI32 *>( a.data ) ); }

MO metil_def_copy__when__a__is__Int_s_32( MO a ) { return NEW_Number( *reinterpret_cast<SI32 *>( a.data ) ); }
MO metil_def_copy__when__a__is__Int_s_64( MO a ) { return NEW_Number( *reinterpret_cast<SI64 *>( a.data ) ); }

void metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000( MO &a, MO b ) {
    DisplayInt<63,1,0,63>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}
void metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000( MO &a, MO b ) {
    DisplayInt<31,1,0,31>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}

void metil_def_self_append__when__a__isa__String__and__b__is__Int_p_64__pert__1000( MO &a, MO b ) {
    DisplayInt<64,0,0,0>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}

void metil_def_self_append__when__a__isa__String__and__b__is__Int_p_32__pert__1000( MO &a, MO b ) {
    DisplayInt<32,0,0,0>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}

bool metil_def_convert_to_Bool__when__a__is__Int_s_64__pert__1000( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }
SI32 metil_def_convert_to_SI32__when__a__is__Int_s_64__pert__1000( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }
SI64 metil_def_convert_to_SI64__when__a__is__Int_s_64__pert__1000( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }

bool metil_def_convert_to_Bool__when__a__is__Int_s_32__pert__1000( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }
SI32 metil_def_convert_to_SI32__when__a__is__Int_s_32__pert__1000( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }
SI64 metil_def_convert_to_SI64__when__a__is__Int_s_32__pert__1000( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }

#define BOP( N, O ) \
    MO metil_def_##N##__when__a__is__Int_s_32__and__b__is__Int_s_32( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI32 *>( a.data ) O *reinterpret_cast<const SI32 *>( b.data ) ); } \
    MO metil_def_##N##__when__a__is__Int_s_32__and__b__is__Int_s_64( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI32 *>( a.data ) O *reinterpret_cast<const SI64 *>( b.data ) ); } \
    MO metil_def_##N##__when__a__is__Int_s_64__and__b__is__Int_s_32( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI64 *>( a.data ) O *reinterpret_cast<const SI32 *>( b.data ) ); } \
    MO metil_def_##N##__when__a__is__Int_s_64__and__b__is__Int_s_64( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI64 *>( a.data ) O *reinterpret_cast<const SI64 *>( b.data ) ); }

BOP( add, + );
BOP( sub, - );
BOP( mul, * );

BOP( sup  , >  );
BOP( supeq, >= );
BOP( inf  , <  );
BOP( infeq, <= );

BOP( boolean_or , || );
BOP( boolean_and, && );

#undef BOP

//
void metil_gen_div__when__a__is__Int_s_64__and__b__is__Int_s_64( MethodWriter &cw, Mos *mos ) {
    TODO;
}

#define WCONV( T ) \
    void TypeConstructor_Int::write_convert_to_##T( MethodWriter &mw, const Mos *a, const String &ret_ins ) const { \
       mw.n << ret_ins << "*reinterpret_cast<const " << cpp_type() << " *>(" << a[ 0 ].data << ");"; \
    }
WCONV( Bool );
WCONV( SI32 );
WCONV( SI64 );
WCONV( FP32 );
WCONV( FP64 );
WCONV( FP80 );
WCONV( ST   );

String TypeConstructor_Int::cpp_type() const {
    if ( sign == 0 ) {
        if ( mant ==  8 ) return "SI8";
        if ( mant == 16 ) return "SI16";
        if ( mant == 32 ) return "SI32";
        if ( mant == 64 ) return "SI64";
    } else if ( sign == 1 ) {
        if ( mant ==  8 ) return "PI8";
        if ( mant == 16 ) return "PI16";
        if ( mant == 32 ) return "PI32";
        if ( mant == 64 ) return "PI64";
    } else if ( sign == -1 ) {
        if ( mant ==  8 ) return "NI8";
        if ( mant == 16 ) return "NI16";
        if ( mant == 32 ) return "NI32";
        if ( mant == 64 ) return "NI64";
    }
    return String();
}

bool TypeConstructor_Int::is_a_POD() const { return 1; }

//
void TypeConstructor_Int::init( Type *type ) {
    TypeConstructor::init( type );

    BasicVec<String> l = tokenize( type->name, "_" );
    ASSERT( l.size() >= 3, "...%s", type->name );

    // sign
    if      ( l[ 1 ] == 'n' ) sign = -1;
    else if ( l[ 1 ] == 's' ) sign =  0;
    else if ( l[ 1 ] == 'p' ) sign = +1;
    else ERROR( "unknown sign description" );

    // mant
    mant = Val( l[ 2 ] );
}

END_METIL_LEVEL1_NAMESPACE;
