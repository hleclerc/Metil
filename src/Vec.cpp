#include "Level1/ArrayHeader.h"
#include "Vec.h"

BEG_METIL_NAMESPACE;

Vec::Vec() {
}

Vec::Vec( const Val &v_0 ) {
    Level1::MO *vec = init_dyn_vec( 1 );
    vec[ 0 ] = CM_1( copy, v_0 );
}

Vec::Vec( const Val &v_0, const Val &v_1 ) {
    Level1::MO *vec = init_dyn_vec( 2 );
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2 ) {
    Level1::MO *vec = init_dyn_vec( 3 );
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3 ) {
    Level1::MO *vec = init_dyn_vec( 4 );
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
    vec[ 3 ] = CM_1( copy, v_3 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3, const Val &v_4 ) {
    Level1::MO *vec = init_dyn_vec( 5 );
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
    vec[ 3 ] = CM_1( copy, v_3 );
    vec[ 4 ] = CM_1( copy, v_4 );
}

Level1::MO *Vec::init_dyn_vec( Level1::Type *type, ST size ) {
    return Level1::init_dyn_array( *this, &size, Number<1>(), type );
}

Level1::MO *Vec::init_dyn_vec( ST size ) {
    return Level1::init_dyn_array( *this, &size, Number<1>() );
}

END_METIL_NAMESPACE;
