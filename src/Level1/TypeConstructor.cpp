#include "TypeConstructor_Array.h"
#include "TypeConstructor_LazyObject.h"
#include "MethodFinder.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

// default behavior
void metil_def_self_append__pert__0( MO &a, MO b ) { Ad c = a; a = CM_2( append, a, b ); }
void metil_def_reassign__pert__0( MO &a, MO b ) { Ad c = a; a = CM_1( copy, b ); }
void metil_def_add_parent__pert__0( MO &a, struct OwcpChild *b ) {}
void metil_def_rem_parent__pert__0( MO &a, struct OwcpChild *b ) {}
bool metil_def_cur_op_id__pert__0( MO a ) { return false; }
ST   metil_def_nb_children__pert__0( MO a ) { return 0; }
MO   metil_def_get_op_mp__pert__0( MO a ) { return MO( 0, 0 ); }
void metil_def_set_op_mp__pert__0( MO &a, void *data, void *type ) {}

const  MachineId *metil_def_machine_id__pert__0( MO a ) { return MachineId::cur(); }
struct OwcpChild *metil_def_get_parent__pert__0( MO a ) { return 0; }

// void objects
MO metil_def_copy__when__a__has__is_void__pert__1( MO a ) { return a.type; }
void metil_gen_copy__when__a__has__is_void( MethodWriter &mw ) { mw.ret() << mw.arg[ 0 ].type << ";"; }

// static gen...( MethodWriter & ) { constructor->write_... }
#define DECL_MET( T, N ) void metil_gen_##N##__when__a__has__has_writer_for_##N##__pert__1( MethodWriter &mw ) { mw.get_type( 0 )->constructor->write_##N( mw ); }
#include "DeclMethodsUnary.h"
#undef DECL_MET

// string << ...
void metil_gen_self_append__when__a__isa__String__and__b__has__has_writer_for_write_str__pert__1( MethodWriter &mw ) {
    mw.add_include( "String.h" );
    if ( mw.get_os_defined() == false ) {
        mw.set_os_defined( true );
        mw.n << "String &os = static_cast<String &>( " << mw.arg[ 0 ] << " );";
    }
    MethodWriter mw_d( mw );
    mw_d.type[ 0 ] = mw.type[ 1 ];
    mw_d.arg [ 0 ] = mw.arg [ 1 ];
    mw.get_type( 1 )->constructor->write_write_str( mw_d );
}

// POD
void metil_gen_del__when__a__has__is_a_POD__pert__1( MethodWriter &mw ) {
    int size = mw.get_type( 0 )->constructor->static_size_in_bytes();
    if ( size > 0 )
        mw.n << "FREE( " << mw.arg[ 0 ].data << ", Number<" << size << ">() );";
}

void metil_gen_copy__when__a__has__is_a_POD__pert__1( MethodWriter &mw ) {
    int size = mw.get_type( 0 )->constructor->static_size_in_bytes();
    if ( size > 0 ) {
        mw.add_include( "Level1/StringHelp.h" );
        String s; s << "Number<" << size << ">()";
        mw.n << "void *res = MALLOC( " << s << " );";
        mw.n << "memcpy( res, " << mw.arg[ 0 ].data << ", " << s << " );";
        mw.ret() << "MO( res, &metil_type_bas_" << mw.get_type( 0 )->name << " );";
    } else {
        mw.ret() << "MO( &metil_type_cst_" << mw.get_type( 0 )->name << " );";
    }
}





TypeConstructor::TypeConstructor() {
    have_been_initialized = false;
}

TypeConstructor::~TypeConstructor() {
}

void TypeConstructor::init( Type *type ) {
    bas_type = type->bas_type;
    ref_type = type->ref_type;
    cst_type = type->cst_type;
}

bool TypeConstructor::Owcp_type() const { return Owcp_size() >= 0; }
bool TypeConstructor::Owcp_size_0() const { return Owcp_size() == 0; }
bool TypeConstructor::Owcp_size_1() const { return Owcp_size() == 1; }
bool TypeConstructor::Owcp_size_2() const { return Owcp_size() == 2; }
bool TypeConstructor::Owcp_size_3() const { return Owcp_size() == 3; }

bool TypeConstructor::is_a_POD() const { return 0; }
bool TypeConstructor::tensor_order_0() const { return tensor_order() == 0; }
bool TypeConstructor::tensor_order_1() const { return tensor_order() == 1; }
bool TypeConstructor::is_void() const { return static_size_in_bits() == 0; }
bool TypeConstructor::staticsize() const { return static_size_in_bits() >= 0; }

void TypeConstructor::default_mw( MethodWriter &mw ) const {}
String TypeConstructor::Owcp_data() const { return "AdditionalDataVoid"; }
int TypeConstructor::Owcp_size() const { return -1; }
int TypeConstructor::static_size_in_bits() const { return -1; }
int TypeConstructor::needed_alignement_in_bits() const { return 8; }
int TypeConstructor::needed_alignement_in_bits_if_in_vec( MachineId::Type mid ) const { return 1; }
int TypeConstructor::tensor_order() const { return 0; }

int TypeConstructor::static_size_in_bytes() const { int sb = static_size_in_bits(); return sb < 0 ? -1 : ( sb + 7 ) / 8; }
int TypeConstructor::needed_alignement_in_bytes() const { return ( needed_alignement_in_bits() + 7 ) / 8; }
int TypeConstructor::needed_alignement_in_bytes_if_in_vec( MachineId::Type mid ) const { return ( needed_alignement_in_bits_if_in_vec( mid ) + 7 ) / 8; }

int TypeConstructor::equ_code( MethodWriter &, const Mos &, const String & ) const { return 0; }

void TypeConstructor::write_convert_to_ST( MethodWriter &mw ) const {
    mw.n << "if ( sizeof( ST ) == 8 ) {";
    write_convert_to_SI64( mw );
    mw.n << "} else {";
    write_convert_to_SI32( mw );
    mw.n << "}";
}

// virtual has_writer_for_...
#define DECL_MET( T, N ) bool TypeConstructor::has_writer_for_##N() const { return 0; }
#include "DeclMethodsUnary.h"
#undef DECL_MET

// virtual write_...
#define DECL_MET( T, N ) void TypeConstructor::write_##N( MethodWriter & ) const { ERROR( "What do we do here (%s, %s) ?", bas_type->name, #N ); }
#include "DeclMethodsUnary.h"
#undef DECL_MET

void TypeConstructor::write_write_str( MethodWriter & ) const { ERROR( "What do we do here (%s) ?", bas_type->name ); }

void TypeConstructor::write_select_op( MethodWriter &mw, TypeConstructor *index_type, const String &op ) const {
    ERROR( "write_select_op is not defined for %s", bas_type->name );
}

String TypeConstructor::cpp_type() const {
    return String();
}

END_METIL_LEVEL1_NAMESPACE;
