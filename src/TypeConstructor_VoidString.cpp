#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;

// {} + ... / ... + {}
void metil_def_self_append__when__a__isa__VoidString__pert__1( MO &a, MO b ) { a = CM_1( copy, b ); }
void metil_def_self_append__when__b__isa__VoidString__pert__2( MO &a, MO b ) {}

END_METIL_LEVEL1_NAMESPACE;
