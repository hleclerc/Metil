#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "TypeConstructor_ConstCharPtr.h"
#include "NewAndRefNumber.h"
#include "StringHelp.h"
#include "../Val.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_copy__when__a__isa__ConstCharPtr( MO a ) { return a; }

MO metil_def_size__when__a__isa__ConstCharPtr( MO a ) { return NEW_Number( strlen( (const char *)a.data ) ); }

const void *metil_def_ptr_z__when__a__isa__ConstCharPtr( MO &a ) { return a.data; }

const void *metil_def_new_ptr_z__when__a__isa__ConstCharPtr( MO a ) { return strdup( (const char *)a.data ); }

void metil_def_copy_data__when__a__isa__ConstCharPtr( MO a, void *ptr, ST size ) { memcpy( ptr, a.data, size ); }

bool metil_def_convert_to_Bool__when__a__isa__ConstCharPtr__pert__1( MO a ) { return true; }

MO metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1( MO a, MO b ) { return NEW_Number( equal( (const char *)a.data, (const char *)b.data ) ); }

MO metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1( MO a, MO b ) {
    return NEW_Number( find( (const char *)a.data, (const char *)b.data ) );
}

MO metil_def_rfind__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1( MO a, MO b ) {
    return NEW_Number( rfind( (const char *)a.data, (const char *)b.data ) );
}

MO metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1( MO a, MO b ) {
    return MO( (char *)a.data + CM_1( convert_to_SI64, b ), a.type );
}

MO metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1( MO a, MO b ) {
    return MO(
        NEW( TypeConstructor_ConstCharPtrWithSize::Data, (const char *)a.data, static_cast<const Val &>( b ) ),
        &metil_type_bas_ConstCharPtrWithSize
    );
}

MO metil_def_select_C__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1( MO a, MO b ) {
    unsigned char v = reinterpret_cast<const unsigned char *>( a.data )[ CM_1( convert_to_SI32, b ) ];
    return MO( String::char_ptr + 2 * v, &Level1::metil_type_cst_ConstCharPtr );
}

END_METIL_LEVEL1_NAMESPACE;
