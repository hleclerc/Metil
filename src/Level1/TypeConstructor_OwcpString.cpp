#include "TypeConstructor_OwcpString.h"
#include "NewAndRefNumber.h"
#include "OwcpStringData.h"
#include "StringHelp.h"
#include "NewString.h"
#include "Val.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_del__when__a__isa__OwcpString( MO &a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    if ( --o->cpt_use < 0 )
        FREE( o, o->rese() );
}

MO metil_def_copy__when__a__isa__OwcpString( MO a ) {
    ++reinterpret_cast<OwcpStringData *>( a.data )->cpt_use;
    return a;
}

MO metil_def_size__when__a__isa__OwcpString( MO a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    return NEW_Number( o->size() );
}

const char *metil_def_ptr_z__when__a__isa__OwcpString( MO &a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    return o->ptr();
}

char *metil_def_new_ptr_z__when__a__isa__OwcpString( MO a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    return strndup( o->ptr(), o->size() );
}

void metil_def_copy_data__when__a__isa__OwcpString( MO a, void *ptr, ST size ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    memcpy( ptr, o->ptr(), size );
}

MO metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1( MO a, MO b ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    return NEW_Number( find( o->ptr(), (const char *)b.data, o->size() ) );
}

MO metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1( MO a, MO b ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    ST s = static_cast<const Val &>( b );
    NewString ns( o->ptr(), o->ptr() + s );
    return MO( ns.data, &metil_type_bas_OwcpString );
}

MO metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1( MO a, MO b ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    ST s = static_cast<const Val &>( b );
    NewString ns( o->ptr() + s, o->ptr() + o->size() );
    return MO( ns.data, &metil_type_bas_OwcpString );
}

MO metil_def_select_C__when__a__isa__OwcpString__and__b__isa__Int__pert__1( MO a, MO b ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    unsigned char v = o->val( CM_1( convert_to_SI32, b ) );
    return MO( String::char_ptr + 2 * v, &Level1::metil_type_cst_ConstCharPtr );
}

END_METIL_LEVEL1_NAMESPACE;
