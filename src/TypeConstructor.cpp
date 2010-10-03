#include "TypeConstructor.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_self_append__pert_0( MO &a, MO b ) { Ad c = a; a = CM_2( append, a, b ); }

TypeConstructor::TypeConstructor() {
    have_been_initialized = false;
}

void TypeConstructor::init( Type *type ) {
}

END_METIL_LEVEL1_NAMESPACE;
