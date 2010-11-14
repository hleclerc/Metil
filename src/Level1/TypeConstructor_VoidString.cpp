#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;

// {} + ... / ... + {}
void metil_def_self_append__when__a__isa__VoidString__pert__100( MO &a, MO b ) { a = CM_1( copy, b ); }
void metil_def_self_append__when__b__isa__VoidString__pert__101( MO &a, MO b ) {}

bool metil_def_convert_to_Bool__when__a__isa__VoidString__pert__1( MO a ) { return false; }

MO metil_def_size__when__a__isa__VoidString( MO a ) { return NEW_Number( 0 ); } // hum

const void *metil_def_ptr_z__when__a__isa__VoidString( MO &a ) { return ""; }

void *metil_def_new_ptr_z__when__a__isa__VoidString( MO a ) { return strdup( "" ); }

void metil_def_copy_data__when__a__isa__VoidString( MO a, void *ptr, ST size ) {}

int TypeConstructor_VoidString::static_size_in_bits() const { return 0; }

END_METIL_LEVEL1_NAMESPACE;
