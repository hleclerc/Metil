#include "TypeConstructor.h"
#include "ArrayHeader.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

//// dynamic version
//MO *init_dyn_array_dyn_dim( MO &res, const ST *size, int dim, Type *base_type, const MachineId *mid ) {
//    TODO;
//    return 0;
//}

//template<class AH>
//void set_machine_id( Number<0>, AH *header, const MachineId *mid ) {}

//template<class AH>
//void set_machine_id( Number<1>, AH *header, const MachineId *mid ) { header->machine_id = mid; }

//// if dim == 1
//template<int want_ExtPtr,int want_MachineId>
//inline MO *init_dyn_array_kernel( MO &res, const ST *size, Number<1> n_dim, Type *base_type, const MachineId *mid, Number<want_ExtPtr> wep, Number<want_MachineId> wmi ) {
//}

//// if dim > 1
//template<int dim,int want_machine_id>
//inline MO *init_dyn_array_kernel( MO &res, const ST *size, Number<dim> n_dim, Type *base_type, const MachineId *mid, Number<want_machine_id> wmi ) {
//    TODO;
//    return 0;
////    ASSERT( dim > 1, "wrong function call" );
////    // get real sizes (-> alignement)
////    ST rese[ dim ], ls, al;
////    if ( base_type ) {
////        base_type->init_if_necessary();
////        al = base_type->constructor->needed_alignement_in_bytes_if_in_vec( mid );
////        ST ss = base_type->constructor->static_size_in_bytes();
////        ASSERT( ss >= 0, "TODO : Array with types of varying sizes" );
////        ls = ceil( ss * size[ 0 ], al );
////        rese[ 0 ] = ls / ss;
////        for( int d = 1; d < dim; ++d )
////            rese[ d ] = size[ d ];

////        res.type = base_type->dyn_array_type( n_dim, want_machine_id, mid->is_a_gpu() );
////    } else {
////        al = 1;
////        ls = size[ 0 ] * sizeof( MO );
////        for( int d = 0; d < dim; ++d )
////            rese[ d ] = size[ d ];

////        ASSERT( dim <= 4, "TODO" );
////        if ( want_machine_id ) {
////            if ( mid->is_a_gpu() ) {
////                switch ( dim ) {
////                case 2: res.type = &metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse_Gpu; break;
////                case 3: res.type = &metil_type_bas_Array_4NULL_3_m_m_m_m_m_m_CptUse_Gpu; break;
////                case 4: res.type = &metil_type_bas_Array_4NULL_4_m_m_m_m_m_m_m_m_CptUse_Gpu; break;
////                }
////            } else {
////                switch ( dim ) {
////                case 2: res.type = &metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse_MachineId; break;
////                case 3: res.type = &metil_type_bas_Array_4NULL_3_m_m_m_m_m_m_CptUse_MachineId; break;
////                case 4: res.type = &metil_type_bas_Array_4NULL_4_m_m_m_m_m_m_m_m_CptUse_MachineId; break;
////                }
////            }
////        } else {
////            switch ( dim ) {
////            case 2: res.type = &metil_type_bas_Array_4NULL_2_m_m_m_m_CptUse; break;
////            case 3: res.type = &metil_type_bas_Array_4NULL_3_m_m_m_m_m_m_CptUse; break;
////            case 4: res.type = &metil_type_bas_Array_4NULL_4_m_m_m_m_m_m_m_m_CptUse; break;
////            }
////        }
////    }

////    // rese_mem
////    typedef Level1::ArrayHeader</*size*/dim,/*rese*/dim,/*CptUse*/1,/*ExtPtr*/0,want_machine_id,/*wrong alignment_in_bytes*/1> AH;
////    ST rese_blk = ls;
////    for( int d = 1; d < dim - 1; ++d )
////        rese_blk *= rese[ d ];
////    ST rese_dat = rese_blk * rese[ dim - 1 ];
////    ST real_hea = ceil_p2( sizeof( AH ), al );
////    ST rese_mem = real_hea + rese_dat;

////    // fill header
////    AH *header = (AH *)MALLOC( rese_mem );
////    new( header ) AH;
////    header->rese_mem = rese_mem;
////    for( int d = 0; d < dim    ; ++d ) header->size[ d ] = size[ d ];
////    for( int d = 0; d < dim - 1; ++d ) header->rese[ d ] = rese[ d ];
////    // if reserved memory if >, maybe we can consider more reserved blocks
////    header->rese[ dim - 1 ] = ( rese_mem - sizeof( AH ) ) / rese_blk;
////    set_machine_id( wmi, header, mid );

////    // data
////    res.data = header;

////    return reinterpret_cast<Level1::MO *>( reinterpret_cast<char *>( header ) + real_hea );
//}


////
//template<int dim>
//inline MO *init_dyn_array_kernel( MO &res, const ST *size, Number<dim> n_dim, Type *base_type, const MachineId *mid ) {
//    if ( mid != MachineId::cur() )
//        return init_dyn_array_kernel( res, size, n_dim, base_type, mid, Number<1>(), Number<1>() );
//    return init_dyn_array_kernel( res, size, n_dim, base_type, mid, Number<0>(), Number<0>() );
//}

//MO *init_dyn_array( MO &res, const ST *, Number<0>, Type *, const MachineId * ) { res.type = &metil_type_ref_Array_4NULL_0; return 0; }
//MO *init_dyn_array( MO &res, const ST *size, Number<1> n, Type *base_type, const MachineId *mid ) { return init_dyn_array_kernel( res, size, n, base_type, mid ); }
//MO *init_dyn_array( MO &res, const ST *size, Number<2> n, Type *base_type, const MachineId *mid ) { return init_dyn_array_kernel( res, size, n, base_type, mid ); }
//MO *init_dyn_array( MO &res, const ST *size, Number<3> n, Type *base_type, const MachineId *mid ) { return init_dyn_array_kernel( res, size, n, base_type, mid ); }
//MO *init_dyn_array( MO &res, const ST *size, Number<4> n, Type *base_type, const MachineId *mid ) { return init_dyn_array_kernel( res, size, n, base_type, mid ); }


END_METIL_LEVEL1_NAMESPACE;
