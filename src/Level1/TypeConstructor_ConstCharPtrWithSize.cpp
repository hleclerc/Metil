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

MO metil_def_size__when__a__isa__ConstCharPtrWithSize( MO a ) {
    return NEW_Number( reinterpret_cast<TD *>( a.data )->size );
}

const void *metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize( MO a ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    return strndup( o->data, o->size );
}

void metil_def_copy_data__when__a__isa__ConstCharPtrWithSize( MO a, void *ptr, ST size ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    memcpy( ptr, o->data, size );
}

const void *metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize( MO &a ) {
    const TD *o = reinterpret_cast<const TD *>( a.data );
    NewString res( o->data, o->data + o->size );
    static_cast<String &>( a ) = res;
    return res.ptr();
}

END_METIL_LEVEL1_NAMESPACE;
