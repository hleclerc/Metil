#include "BasicMethods.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

void do_nothing_VO( MO & ) {}

void default_reassign( MO &a, MO b ) { Ad c = a; a = CM_1( copy, b ); }
void default_self_add( MO &a, MO b ) { Ad c = a; a = CM_2( add, a, b ); }
void default_self_sub( MO &a, MO b ) { Ad c = a; a = CM_2( sub, a, b ); }
void default_self_mul( MO &a, MO b ) { Ad c = a; a = CM_2( mul, a, b ); }
void default_self_div( MO &a, MO b ) { Ad c = a; a = CM_2( div, a, b ); }
void default_self_quo( MO &a, MO b ) { Ad c = a; a = CM_2( quo, a, b ); }
void default_self_mod( MO &a, MO b ) { Ad c = a; a = CM_2( mod, a, b ); }

END_METIL_LEVEL1_NAMESPACE
