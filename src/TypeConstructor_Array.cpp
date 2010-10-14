#include "TypeConstructor_Array.h"
#include "Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

void TypeConstructor_Array::init( Type *type ) {
    PRINT( type->name );
    BasicVec<String> lst = tokenize( type->name, '_' );

    PRINT( lst[ 1 ] );
    int dim = Val( lst[ 1 ] );
    PRINT( dim );
}

END_METIL_LEVEL1_NAMESPACE;
