#include "TypeConstructor_Cst.h"
#include "../Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

// bootstrap
SI32 metil_def_convert_to_SI32__when__a__is__Cst_0__pert__1000( MO a ) { return 0; }
SI64 metil_def_convert_to_SI64__when__a__is__Cst_0__pert__1000( MO a ) { return 0; }
bool metil_def_convert_to_Bool__when__a__is__Cst_0__pert__1000( MO a ) { return 0; }

SI32 metil_def_convert_to_SI32__when__a__is__Cst_1__pert__1000( MO a ) { return 1; }
SI64 metil_def_convert_to_SI64__when__a__is__Cst_1__pert__1000( MO a ) { return 1; }
bool metil_def_convert_to_Bool__when__a__is__Cst_1__pert__1000( MO a ) { return 1; }


// writers
//static TypeConstructor_Cst *sc( Type *type ) {
//    return static_cast<TypeConstructor_Cst *>( type->constructor );
//}

#define CONV_TO( N ) \
    void TypeConstructor_Cst::write_convert_to_##N( MethodWriter &mw ) const { \
        mw.ret() << disp_str( true ) << ";"; \
    }

CONV_TO( Bool );
CONV_TO( SI32 );
CONV_TO( SI64 );
CONV_TO( FP32 );
CONV_TO( FP64 );
CONV_TO( FP80 );

void TypeConstructor_Cst::write_write_str( MethodWriter &cw ) const {
    cw.n << "os << " << disp_str() << ";";
}

int TypeConstructor_Cst::equ_code( MethodWriter &mw, const Mos &args, const String &val ) const {
    return 2 * bool( val == name );
}

String TypeConstructor_Cst::disp_str( bool num_conv ) const {
    String res;
    BasicVec<String> l = tokenize( name, '_' );
    if ( l[ 0 ] == "m" ) {
        l.remove( 0 );
        res << "-";
    }
    res << l[ 0 ];
    if ( l.size() >= 2 )
        res << "/" << l[ 1 ];
    return res;
}

static bool transcendental( const String &name ) {
    return  name == "pi" or
            name == "e" or
            name == "i" or
            name == "inf" or
            name == "exp" or
            name == "nan";
}

bool TypeConstructor_Cst::conversion_to( SI64 &val ) const {
    SI64 m = 1;
    BasicVec<String> l = tokenize( name, '_' );
    if ( l[ 0 ] == "m" ) {
        l.remove( 0 );
        m = -1;
    }
    if ( transcendental( l[ 0 ] ) )
        return false;
    if ( l.size() >= 2 )
        return false;
    val = Val( l[ 0 ] );
    return true;
}

int TypeConstructor_Cst::static_size_in_bits() const {
    return 0;
}

void TypeConstructor_Cst::init( Type *type ) {
    TypeConstructor::init( type );
    name = type->name + 4;
}

END_METIL_LEVEL1_NAMESPACE;
