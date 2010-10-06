#include "TypeConstructor_Int.h"
#include "DisplayInt.h"

BEG_METIL_LEVEL1_NAMESPACE;

// bootstrap methods for Int64
void metil_def_del__when__a__is__Int_s_64( MO &a ) { DEL( reinterpret_cast<SI64 *>( a.data ) ); }
void metil_def_del__when__a__is__Int_s_32( MO &a ) { DEL( reinterpret_cast<SI32 *>( a.data ) ); }

MO metil_def_copy__when__a__is__Int_s_32( MO a ) { return NEW_Number( *reinterpret_cast<SI32 *>( a.data ) ); }
MO metil_def_copy__when__a__is__Int_s_64( MO a ) { return NEW_Number( *reinterpret_cast<SI64 *>( a.data ) ); }

void metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000( MO &a, MO b ) {
    DisplayInt<63,1,0,63>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}
void metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000( MO &a, MO b ) {
    DisplayInt<31,1,0,31>::display( static_cast<String &>( a ), (const PI8 *)b.data );
}

bool metil_def_convert_to_Bool__when__a__is__Int_s_64( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }
SI32 metil_def_convert_to_SI32__when__a__is__Int_s_64( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }
SI64 metil_def_convert_to_SI64__when__a__is__Int_s_64( MO a ) { return *reinterpret_cast<const SI64 *>( a.data ); }

bool metil_def_convert_to_Bool__when__a__is__Int_s_32( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }
SI32 metil_def_convert_to_SI32__when__a__is__Int_s_32( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }
SI64 metil_def_convert_to_SI64__when__a__is__Int_s_32( MO a ) { return *reinterpret_cast<const SI32 *>( a.data ); }

#define BOP( N, O ) \
    MO metil_def_##N##__when__a__is__Int_s_64__and__b__is__Int_s_64( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI64 *>( a.data ) O *reinterpret_cast<const SI64 *>( b.data ) ); } \
    MO metil_def_##N##__when__a__is__Int_s_32__and__b__is__Int_s_32( MO a, MO b ) { return NEW_Number( *reinterpret_cast<const SI32 *>( a.data ) O *reinterpret_cast<const SI32 *>( b.data ) ); }

BOP( add, + );
BOP( sub, - );
BOP( mul, * );

BOP( boolean_or , || );
BOP( boolean_and, && );

#undef BOP

// TypeConstructor_Int
void TypeConstructor_Int::init( Type *type ) {
}

END_METIL_LEVEL1_NAMESPACE;
