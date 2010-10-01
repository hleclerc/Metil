#include "TypeConstructor_VoidString.h"
#include "Dout.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString( MO a, MO b ) {
    DOUT( __LINE__ );
    return MO();
}

void TypeConstructor_VoidString::init( Type *type ) {
}

END_METIL_LEVEL1_NAMESPACE;
