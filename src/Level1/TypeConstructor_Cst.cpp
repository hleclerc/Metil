#include "TypeConstructor_Cst.h"

BEG_METIL_LEVEL1_NAMESPACE;

static TypeConstructor_Cst *sc( Type *type ) {
    return static_cast<TypeConstructor_Cst *>( type->constructor );
}

#define CONV_TO( N ) \
    void TypeConstructor_Cst::write_convert_to_##N( MethodWriter &mw, const Mos *a, const String &ret_ins ) const { \
        mw.n << ret_ins << " " << disp_str() << ";"; \
    }

CONV_TO( Bool );
CONV_TO( SI32 );
CONV_TO( SI64 );
CONV_TO( FP32 );
CONV_TO( FP64 );
CONV_TO( FP80 );

void metil_gen_self_append__when__a__isa__String__and__b__isa__Cst__pert__1( MethodWriter &cw, Mos *args ) {
    cw.add_include( "String.h" );
    cw.n << "static_cast<String &>( a ) << " << sc( cw.type[ 1 ] )->disp_str() << ";";
}


SI32 metil_def_convert_to_SI32__when__a__is__Cst_zero__pert__1000( MO a ) { return 0; }
SI32 metil_def_convert_to_SI64__when__a__is__Cst_zero__pert__1000( MO a ) { return 0; }
SI32 metil_def_convert_to_Bool__when__a__is__Cst_zero__pert__1000( MO a ) { return 0; }


MO metil_def_copy__when__a__isa__Cst__pert__1( MO a ) {
    return a.type;
}



String TypeConstructor_Cst::disp_str() const {
    if ( name == "zero"      ) return "0";
    if ( name == "one"       ) return "1";
    if ( name == "minus_one" ) return "-1";
    ERROR( "unknown cst %s", name.c_str() );
    return "";
}

void TypeConstructor_Cst::init( Type *type ) {
    TypeConstructor::init( type );
    name = type->name + 4;
}

END_METIL_LEVEL1_NAMESPACE;
