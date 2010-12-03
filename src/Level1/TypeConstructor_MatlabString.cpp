#include "TypeConstructor_MatlabString.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_self_append__when__a__isa__MatlabString__and__b__isa__ConstCharPtr__pert__2( MethodWriter &mw ) {
    mw.n << "mexPrintf( \"%s\", " << mw.arg[ 1 ].data << " );";
}

void metil_gen_self_append__when__a__isa__MatlabString__and__b__isa__OwcpString__pert__1( MethodWriter &mw ) {
    mw.n << "const char *data = (const char *)CM_1( ptr_z, " << mw.arg[ 1 ] << " );";
    mw.n << "mexPrintf( \"%s\", data );";
}

void metil_def_flush__when__a__isa__MatlabString( MO &a ) {}

void TypeConstructor_MatlabString::default_mw( MethodWriter &mw ) const {
    TypeConstructor_String::default_mw( mw );
    mw.add_include( "Matlab.h" );
}

END_METIL_LEVEL1_NAMESPACE;
