#include "Level1/ArrayHeader.h"
#include "Mat.h"

BEG_METIL_NAMESPACE;

Level1::MO *Mat::init_dyn_mat( ST r, ST c ) {
    typedef Level1::ArrayHeader</*size*/2,/*rese*/2,/*CptUse*/1,/*ExtPtr*/0> AH;
    ST rese_mem = sizeof( AH ) + r * c * sizeof( MO );

    AH *header = (AH *)MALLOC( rese_mem );
    new( header ) AH;
    header->rese_mem = rese_mem;
    header->size[ 0 ] = c;
    header->size[ 1 ] = r;
    header->rese[ 0 ] = c;
    header->rese[ 1 ] = ( rese_mem - sizeof( AH ) ) / ( sizeof( MO ) * c );

    type = &Level1::metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse;
    data = header;

    return reinterpret_cast<Level1::MO *>( header + 1 );
}

Mat::Mat() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Mat::Mat( ST r, ST c, Level1::Type *base_type ) {
    if ( base_type ) {
        TODO;
    } else {
        Level1::MO *d = init_dyn_mat( r, c );
        for( int i = 0; i < r * c; ++i )
            new( d + i ) Val;
    }
}

END_METIL_NAMESPACE;
