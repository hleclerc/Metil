#include "TypeConstructor_VoidString.h"
#include "Dout.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_add__VoidString__VoidString( MO a, MO b ) {
    DOUT( __LINE__ );
    return MO();
}

void TypeConstructor_VoidString::init( Type *type ) {
}

END_METIL_LEVEL1_NAMESPACE;
