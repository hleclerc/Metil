#ifndef BASICMETHODS_H
#define BASICMETHODS_H

#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

void do_nothing_VO( MO &a );
void default_reassign( MO &a, const MO &b );
void default_self_add( MO &a, const MO &b );
void default_self_sub( MO &a, const MO &b );
void default_self_mul( MO &a, const MO &b );
void default_self_div( MO &a, const MO &b );
void default_self_quo( MO &a, const MO &b );
void default_self_mod( MO &a, const MO &b );

END_METIL_LEVEL1_NAMESPACE

#endif // BASICMETHODS_H
