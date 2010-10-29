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

int TypeConstructor::Owcp_size() const { return -1; }
void TypeConstructor::default_mw( MethodWriter &mw ) const {}
void TypeConstructor::init( Type *type ) {}
int TypeConstructor::static_size_in_bytes() const { return ( static_size_in_bits() + 7 ) / 8; }
int TypeConstructor::static_size_in_bits() const { return -1; }
int TypeConstructor::tensor_order() const { return 0; }
int TypeConstructor::needed_alignement_in_bits() const { return 8; }

END_METIL_LEVEL1_NAMESPACE;
