#include "TypeConstructor_Array.h"
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

void metil_gen_self_append__when__a__isa__String__and__b__has__has_writer_for_write_str__pert__1( MethodWriter &cw, Mos *a ) {
    cw.n << "String &os = static_cast<String &>(" << a[ 0 ] << ");";
    cw.type[ 1 ]->constructor->write_write_str( cw, a + 1 );
}

void metil_gen_del__when__a__has__is_a_POD__pert__1( MethodWriter &mw, Mos *a ) {
    mw.n << "FREE( " << a->data << ", Number<"
         << mw.type[ 0 ]->constructor->static_size_in_bytes() << ">() );";
}

TypeConstructor::TypeConstructor() {
    have_been_initialized = false;
    _vec_type_set = 0;
    _mat_type_set = 0;
}

TypeConstructor::~TypeConstructor() {
    if ( _vec_type_set ) DEL( _vec_type_set );
    if ( _mat_type_set ) DEL( _mat_type_set );
}

void TypeConstructor::init( Type *type ) {
    bas_type = type->bas_type;
    ref_type = type->ref_type;
    cst_type = type->cst_type;
}

void TypeConstructor::default_mw( MethodWriter &mw ) const {}
bool TypeConstructor::is_a_POD() const { return 0; }
int TypeConstructor::Owcp_size() const { return -1; }
int TypeConstructor::static_size_in_bytes() const { return ( static_size_in_bits() + 7 ) / 8; }
int TypeConstructor::static_size_in_bits() const { return -1; }
int TypeConstructor::tensor_order() const { return 0; }
int TypeConstructor::needed_alignement_in_bytes() const { return ( needed_alignement_in_bits() + 7 ) / 8; }
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

void TypeConstructor::write_write_str( MethodWriter &, const Mos *, const String & ) const { ERROR( "What do we do here (%s) ?", bas_type->name ); }

void TypeConstructor::write_select_op( MethodWriter &mw, const Mos *a, TypeConstructor *index_type, const String &op ) const {
    ERROR( "write_select_op is not defined for %s", bas_type->name );
}

String TypeConstructor::cpp_type() const {
    return String();
}

TypeSetAncestor *TypeConstructor::vec_type( const String &name ) {
    if ( not _vec_type_set ) {
        String tn; tn << "Array_" << name.size() << name << "_1_m_m_CptUse";
        _vec_type_set = NEW( TypeSet<TypeConstructor_Array>, tn );
    }
    return _vec_type_set;
}

TypeSetAncestor *TypeConstructor::mat_type( const String &name ) {
    if ( not _mat_type_set ) {
        String tn; tn << "Array_" << name.size() << name << "_2_m_m_m_m_CptUse";
        _mat_type_set = NEW( TypeSet<TypeConstructor_Array>, tn );
    }
    return _mat_type_set;
}

END_METIL_LEVEL1_NAMESPACE;
