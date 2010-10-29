#include "Level1/ArrayHeader.h"
#include "Vec.h"

BEG_METIL_NAMESPACE;

Level1::MO *Vec::init_dyn_vec( ST size ) {
    typedef Level1::ArrayHeader</*size*/1,/*rese*/1,/*CptUse*/1,/*ExtPtr*/0> AH;
    ST rese_mem = sizeof( AH ) + size * sizeof( MO );

    AH *header = (AH *)MALLOC( rese_mem );
    new( header ) AH;
    header->rese_mem = rese_mem;
    header->size[ 0 ] = size;
    header->rese[ 0 ] = ( rese_mem - sizeof( AH ) ) / sizeof( MO );

    type = &Level1::metil_type_ref_Array_4NULL_1_m_m_CptUse;
    data = header;

    return reinterpret_cast<Level1::MO *>( header + 1 );
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

END_METIL_NAMESPACE;
