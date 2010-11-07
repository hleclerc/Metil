#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;

// {} + ... / ... + {}
void metil_def_self_append__when__a__isa__VoidString__pert__100( MO &a, MO b ) { a = CM_1( copy, b ); }
void metil_def_self_append__when__b__isa__VoidString__pert__101( MO &a, MO b ) {}

bool metil_def_convert_to_Bool__when__a__isa__VoidString__pert__1( MO a ) { return false; }

MO metil_def_size__when__a__isa__VoidString( MO a ) { return &metil_type_cst_Cst_zero; }

const void *metil_def_ptr_z__when__a__isa__VoidString( MO &a ) { return ""; }

END_METIL_LEVEL1_NAMESPACE;
