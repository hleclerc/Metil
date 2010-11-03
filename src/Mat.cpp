#include "Level1/TypeConstructor.h"
#include "Level1/ArrayHeader.h"
#include "Math.h"
#include "Mat.h"

BEG_METIL_NAMESPACE;

Level1::MO *Mat::init_dyn_mat( ST r, ST c, Level1::Type *base_type ) {
    typedef Level1::ArrayHeader</*size*/2,/*rese*/2,/*CptUse*/1,/*ExtPtr*/0> AH;
    ST rese_mem = sizeof( AH );
    ST rc = c, ls;
    if ( base_type ) {
        base_type->init_if_necessary();
        Level1::TypeConstructor *tc = base_type->constructor;
        ST al = tc->needed_alignement_in_bytes() / tc->static_size_in_bytes();
        rc = al ? ceil( c, al ) : c;
        ASSERT( tc->static_size_in_bytes() >= 0, "Array with types of varying sizes" );
        ls = rc * tc->static_size_in_bytes();
        rese_mem += r * ls;
    } else {
        ls = c * sizeof( MO );
        rese_mem += r * ls;
    }

    AH *header = (AH *)MALLOC( rese_mem );
    new( header ) AH;
    header->rese_mem = rese_mem;
    header->size[ 0 ] = c;
    header->size[ 1 ] = r;
    header->rese[ 0 ] = rc;
    header->rese[ 1 ] = ( rese_mem - sizeof( AH ) ) / ls;

    type = base_type ? base_type->mat_type() : &Level1::metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse;
    data = header;

    return reinterpret_cast<Level1::MO *>( header + 1 );
}

Mat::Mat() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Mat::Mat( ST r, ST c, Level1::Type *base_type ) {
    Level1::MO *d = init_dyn_mat( r, c, base_type );
    if ( not base_type ) {
        for( int i = 0; i < r * c; ++i )
            new( d + i ) Val;
    }
}

END_METIL_NAMESPACE;
