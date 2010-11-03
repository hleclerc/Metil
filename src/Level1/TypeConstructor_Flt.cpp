#include "TypeConstructor_Flt.h"
#include "MethodFinder.h"
#include "DisplayFlt.h"
#include "Tokenize.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_reassign_inplace__when__a__isa__Flt( MethodWriter &mw, Mos *a ) {
    TypeConstructor_Flt *c = static_cast<TypeConstructor_Flt *>( mw.type[ 0 ]->constructor );
    if ( String cpp = c->cpp_type() ) {
        String ret; ret << "reinterpret_cast<" << cpp << ">( " << a[ 0 ].data << " ) =";
        call_gene<MethodName_convert_to_FP32>( mw, mw.type[ 1 ], 0, 0, a + 1, ret );
    } else
        TODO;
}

void TypeConstructor_Flt::write_write_str( MethodWriter &mw, const Mos *a, const String & ) const {
    mw.add_include( "Level1/DisplayFlt.h" );
    if ( mant.len == 64 )
        mw.n << "ERROR(\"TODO: correction bug disp FP80\");";
    mw.n << "DisplayFlt<"
         << mant.off << "," << mant.len << ","
         << expo.off << "," << expo.len << ","
         << sign.off << "," << sign.len << ","
         << - bia_expo
         << ">::display( os, (const PI8 *)" << a->data << " );";
}


int TypeConstructor_Flt::static_size_in_bits() const {
    return max( max( expo.len + expo.off, mant.len + mant.off ), sign.len + sign.off );
}

bool TypeConstructor_Flt::is_a_POD() const {
    return true;
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
