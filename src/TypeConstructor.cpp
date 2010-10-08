#include "TypeConstructor.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_self_append__pert_0( MO &a, MO b ) { Ad c = a; a = CM_2( append, a, b ); }

void metil_def_reassign__pert_0( MO &a, MO b ) { Ad c = a; a = CM_1( copy, b ); }

void metil_def_add_parent__pert_0( MO &a, struct OwcpChild *b ) {}
void metil_def_rem_parent__pert_0( MO &a, struct OwcpChild *b ) {}


TypeConstructor::TypeConstructor() {
    have_been_initialized = false;
}

void TypeConstructor::init( Type *type ) {
}

END_METIL_LEVEL1_NAMESPACE;
