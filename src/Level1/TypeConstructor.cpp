#include "TypeConstructor.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_self_append__pert__0( MO &a, MO b ) { Ad c = a; a = CM_2( append, a, b ); }

void metil_def_reassign__pert__0( MO &a, MO b ) { Ad c = a; a = CM_1( copy, b ); }

void metil_def_add_parent__pert__0( MO &a, struct OwcpChild *b ) {}
void metil_def_rem_parent__pert__0( MO &a, struct OwcpChild *b ) {}

// static gen...( MethodWriter & ) { constructor->write_... }
#define DECL_MET( T, N ) void metil_gen_##N##__when__a__has__has_writer_for_##N##__pert__1( MethodWriter &cw, Mos *a ) { cw.type[ 0 ]->constructor->write_##N( cw, a ); }
#include "DeclMethodsUnary.h"
#undef DECL_MET


TypeConstructor::TypeConstructor() { have_been_initialized = false; }
void TypeConstructor::init( Type *type ) { bas_type = type->bas_type; ref_type = type->ref_type; cst_type = type->cst_type; }
void TypeConstructor::default_mw( MethodWriter &mw ) const {}
bool TypeConstructor::is_a_POD() const { return 0; }
int TypeConstructor::Owcp_size() const { return -1; }
int TypeConstructor::static_size_in_bytes() const { return ( static_size_in_bits() + 7 ) / 8; }
int TypeConstructor::static_size_in_bits() const { return -1; }
int TypeConstructor::tensor_order() const { return 0; }
int TypeConstructor::needed_alignement_in_bits() const { return 8; }

void TypeConstructor::write_convert_to_ST( MethodWriter &mw, const Mos *a, const String &ret_ins ) const {
    mw.n << "if ( sizeof( ST ) == 8 ) {";
    write_convert_to_SI64( mw, a, ret_ins );
    mw.n << "} else {";
    write_convert_to_SI32( mw, a, ret_ins );
    mw.n << "}";
}

// virtual has_writer_for_...
#define DECL_MET( T, N ) bool TypeConstructor::has_writer_for_##N() const { return 0; }
#include "DeclMethodsUnary.h"
#undef DECL_MET

// virtual write_...
#define DECL_MET( T, N ) void TypeConstructor::write_##N( MethodWriter &, const Mos *, const String & ) const { ERROR( "What do we do here (%s, %s) ?", bas_type->name, #N ); }
#include "DeclMethodsUnary.h"
#undef DECL_MET

void TypeConstructor::write_select_op( MethodWriter &mw, const Mos *a, TypeConstructor *index_type, const String &op ) const {
    ERROR( "write_select_op is not defined for %s", bas_type->name );
}

String TypeConstructor::cpp_type() const {
    return String();
}

END_METIL_LEVEL1_NAMESPACE;
