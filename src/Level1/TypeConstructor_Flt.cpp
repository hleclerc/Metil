#include "TypeConstructor_Flt.h"
#include "MethodFinder.h"
#include "DisplayFlt.h"
#include "Tokenize.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_self_append__when__a__isa__String__and__b__is__Flt_0_23_23_8_31_1_127__pert__1000( MO &a, MO b ) {
    String &os = static_cast<String &>( a );
    DisplayFlt<0,23,23,8,31,1,-127>::display( os, (const PI8 *)b.data );
}
void metil_def_self_append__when__a__isa__String__and__b__is__Flt_0_52_52_11_63_1_1023__pert__1000( MO &a, MO b ) {
    String &os = static_cast<String &>( a );
    DisplayFlt<0,52,52,11,63,1,-1023>::display( os, (const PI8 *)b.data );
}

void metil_gen_reassign_inplace__when__a__isa__Flt( MethodWriter &mw ) {
    TypeConstructor_Flt *c = static_cast<TypeConstructor_Flt *>( mw.get_type( 0 )->constructor );
    if ( String cpp = c->cpp_type() ) {
        String ret; ret << "*reinterpret_cast<" << cpp << " *>( " << mw.arg[ 0 ].data << " ) = ";
        if      ( cpp == "FP32" ) mw.call_gene( "convert_to_FP32", mw.get_type( 1 ), mw.arg[ 1 ], ret );
        else if ( cpp == "FP64" ) mw.call_gene( "convert_to_FP64", mw.get_type( 1 ), mw.arg[ 1 ], ret );
        else if ( cpp == "FP80" ) mw.call_gene( "convert_to_FP80", mw.get_type( 1 ), mw.arg[ 1 ], ret );
        else ERROR("unknown cpp type");
    } else
        TODO;
}

void metil_gen_init_arg__when__a__isa__Flt( MethodWriter &mw ) {
    metil_gen_reassign_inplace__when__a__isa__Flt( mw );
}

void TypeConstructor_Flt::write_convert_to_Bool( MethodWriter &mw ) const { write_convert_to_( mw ); }
void TypeConstructor_Flt::write_convert_to_SI32( MethodWriter &mw ) const { write_convert_to_( mw ); }
void TypeConstructor_Flt::write_convert_to_SI64( MethodWriter &mw ) const { write_convert_to_( mw ); }
void TypeConstructor_Flt::write_convert_to_FP32( MethodWriter &mw ) const { write_convert_to_( mw ); }
void TypeConstructor_Flt::write_convert_to_FP64( MethodWriter &mw ) const { write_convert_to_( mw ); }
void TypeConstructor_Flt::write_convert_to_FP80( MethodWriter &mw ) const { write_convert_to_( mw ); }

void TypeConstructor_Flt::write_convert_to_( MethodWriter &mw ) const {
    if ( String cpp = cpp_type() ) {
        mw.add_include("String.h");
        mw.ret() << "*reinterpret_cast<const " << cpp << " *>( " << mw.arg[ 0 ].data << " );\n";
    } else
        TODO;
}

void TypeConstructor_Flt::write_write_str( MethodWriter &mw ) const {
    mw.add_include( "Level1/DisplayFlt.h" );
    if ( mant.len == 64 )
        mw.n << "ERROR(\"TODO: correction bug disp FP80\");";
    mw.n << "DisplayFlt<"
         << mant.off << "," << mant.len << ","
         << expo.off << "," << expo.len << ","
         << sign.off << "," << sign.len << ","
         << - bia_expo
         << ">::display( os, (const PI8 *)" << mw.arg[ 0 ].data << " );";
}


int TypeConstructor_Flt::static_size_in_bits() const {
    return max( max( expo.len + expo.off, mant.len + mant.off ), sign.len + sign.off );
}

int TypeConstructor_Flt::needed_alignement_in_bits_if_in_vec( MachineId::Type mid ) const {
    return MachineId::simd_alignement( mid );
}

bool TypeConstructor_Flt::is_a_POD() const {
    return true;
}

String TypeConstructor_Flt::cpp_type() const {
    if ( static_size_in_bits() == 32 ) return "FP32";
    if ( static_size_in_bits() == 64 ) return "FP64";
    if ( static_size_in_bits() == 80 ) return "FP80";
    return String();
}

void TypeConstructor_Flt::init( Type *type ) {
    BasicVec<String> l = tokenize( type->name + 4, "_" );

    mant.off = Val( l[ 0 ] );
    mant.len = Val( l[ 1 ] );
    expo.off = Val( l[ 2 ] );
    expo.len = Val( l[ 3 ] );
    sign.off = Val( l[ 4 ] );
    sign.len = Val( l[ 5 ] );
    bia_expo = Val( l[ 6 ] );
}


END_METIL_LEVEL1_NAMESPACE;
