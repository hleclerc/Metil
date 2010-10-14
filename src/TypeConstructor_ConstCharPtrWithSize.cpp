#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "String.h"
#include "StringHelp.h"

BEG_METIL_LEVEL1_NAMESPACE;

typedef TypeConstructor_ConstCharPtrWithSize::Data TD;

void metil_def_del__when__a__isa__ConstCharPtrWithSize( MO &a ) {
    DEL( reinterpret_cast<TD *>( a.data ) );
}

MO metil_def_copy__when__a__isa__ConstCharPtrWithSize( MO a ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    return MO( NEW( TD, o->data, o->size ), a.type );
}

const void *metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize( MO a ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    return strndup( o->data, o->size );
}

void metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize( MO &a ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    static_cast<String &>( a ) = NewString( o->data, o->data + o->size );
}

END_METIL_LEVEL1_NAMESPACE;
