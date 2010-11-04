#include "ArrayHeader.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<int dim>
MO *init_dyn_array( MO &res, ST *sizes, Number<dim> ) {
    typedef Level1::ArrayHeader</*size*/dim,/*rese*/dim,/*CptUse*/1,/*ExtPtr*/0> AH;
    ST rese_mem = sizeof( AH ) + size * sizeof( MO );

    AH *header = (AH *)MALLOC( rese_mem );
    new( header ) AH;
    header->rese_mem = rese_mem;
    for( int d = 0; d < dim; ++d ) {
        header->size[ 0 ] = size;
        header->rese[ 0 ] = ( rese_mem - sizeof( AH ) ) / sizeof( MO );
    }

    res.type = &Level1::metil_type_bas_Array_4NULL_1_m_m_CptUse;
    res.data = header;

    return reinterpret_cast<Level1::MO *>( header + 1 );
}

END_METIL_LEVEL1_NAMESPACE;
