#include "TypeConstructor_Flt.h"
#include "DisplayFlt.h"
#include "Tokenize.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

void TypeConstructor_Flt::write_write_str( MethodWriter &mw, const Mos *a, const String & ) const {
    mw.add_include( "Level1/DisplayFlt.h" );
    if ( mant.len == 64 )
        mw.n << "ERROR(\"TODO: correction bog disp FP80\");";
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

int TypeConstructor_Flt::needed_alignement_in_bits() const {
    switch ( static_size_in_bits() ) {
    case 32: return 4; ///< hum
    case 64: return 2; ///< hum
    }
    return 1;
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
