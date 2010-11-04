#include "TypeConstructor.h"
#include "ArrayHeader.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO *init_dyn_array( MO &res, const ST *size, Number<0>, Type *base_type ) {
    res.type = &metil_type_ref_Array_4NULL_0;
    return 0;
}

// if dim > 0
template<int dim>
MO *init_dyn_array( MO &res, const ST *size, Number<dim> n_dim, Type *base_type ) {
    typedef Level1::ArrayHeader</*size*/dim,/*rese*/dim,/*CptUse*/1,/*ExtPtr*/0> AH;

    // get real sizes (-> alignement)
    ST rese[ dim ], line_size;
    if ( base_type ) {
        base_type->init_if_necessary();
        ST stat_size = base_type->constructor->static_size_in_bytes();
        ASSERT( stat_size >= 0, "TODO : Array with types of varying sizes" );
        line_size = ceil( stat_size * size[ 0 ], base_type->constructor->needed_alignement_in_bytes() );
        rese[ 0 ] = line_size / stat_size;
        for( int d = 1; d < dim; ++d )
            rese[ d ] = size[ d ];
    } else {
        line_size = size[ 0 ] * sizeof( MO );
        for( int d = 0; d < dim; ++d )
            rese[ d ] = size[ d ];
    }

    // rese_mem
    ST rese_blk = line_size;
    for( int d = 1; d < dim - 1; ++d )
        rese_blk *= rese[ d ];
    ST rese_mem = sizeof( AH ) + rese[ dim - 1 ] * rese_blk;

    // fill header
    AH *header = (AH *)MALLOC( rese_mem );
    new( header ) AH;
    header->rese_mem = rese_mem;
    for( int d = 0; d < dim    ; ++d ) header->size[ d ] = size[ d ];
    for( int d = 0; d < dim - 1; ++d ) header->rese[ d ] = rese[ d ];
    // if reserved memory if >, maybe we can consider more reserved blocks
    header->rese[ dim - 1 ] = ( rese_mem - sizeof( AH ) ) / rese_blk;

    // data
    res.data = header;

    // type
    if ( base_type ) {
        res.type = base_type->dyn_array_type( n_dim );
    } else {
        switch ( dim ) {
        case 1: res.type = &metil_type_bas_Array_4NULL_1_m_m_CptUse; break;
        case 2: res.type = &metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse; break;
        case 3: res.type = &metil_type_bas_Array_4NULL_3_m_m_m_m_m_m_CptUse; break;
        case 4: res.type = &metil_type_bas_Array_4NULL_4_m_m_m_m_m_m_m_m_CptUse; break;
        default: TODO;
        }
    }

    return reinterpret_cast<Level1::MO *>( header + 1 );
}

static void __fake__( MO res ) {
    init_dyn_array( res, 0, Number<0>(), 0 );
    init_dyn_array( res, 0, Number<1>(), 0 );
    init_dyn_array( res, 0, Number<2>(), 0 );
    init_dyn_array( res, 0, Number<3>(), 0 );
    init_dyn_array( res, 0, Number<4>(), 0 );
    __fake__( res );
}

END_METIL_LEVEL1_NAMESPACE;
