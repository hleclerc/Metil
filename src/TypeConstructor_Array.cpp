#include "TypeConstructor_Array.h"
#include "MethodWriter.h"
#include "Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_self_append__when__a__isa__String__and__b__isa__Array__pert__1( MethodWriter &mw, Mos *mos ) {

}

void TypeConstructor_Array::init( Type *type ) {
    owcp = false;
    ext_ptr = false;

    BasicVec<String> lst = tokenize( type->name, '_' );

    int dim = Val( lst[ 1 ] );
    size.resize( dim );
    rese.resize( dim );
    for( int d = 0; d < dim; ++d ) {
        size[ d ] = Val( lst[ 2 + 2 * d ] );
        rese[ d ] = Val( lst[ 3 + 2 * d ] );
    }

    for( int d = 2 + 2 * dim; d < lst.size(); ++d ) {
        if ( lst[ d ] == "Owcp"   ) owcp    = true;
        if ( lst[ d ] == "ExtPtr" ) ext_ptr = true;
    }
}

END_METIL_LEVEL1_NAMESPACE;
