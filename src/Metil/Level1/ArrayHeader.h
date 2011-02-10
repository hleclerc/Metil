#ifndef ARRAYDATA_H
#define ARRAYDATA_H

#include "../ClassOrVoid.h"
#include "../MachineId.h"
#include "../Number.h"
#include "../Math.h"
#include "../MO.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct ArrayHeader_CptUse {
    ArrayHeader_CptUse() : cpt_use( 0 ), parent( 0 ) {}
    ST cpt_use;
    Level1::MO *parent;
};

template<int len_size,int len_rese>
struct ArrayHeader_SizeAndRese  {
    ST rese_mem;
    ST size[ len_size ];
    ST rese[ len_rese ];
};

struct ArrayHeader_MachineId {
    const MachineId *machine_id;
};

struct ArrayHeader_Ptr {
    void *ext_ptr;
};

template<int len_size,int len_rese,bool want_cpt_use,bool want_ext_ptr,bool want_machine_id,int alignment_in_bytes>
struct ArrayHeaderBase :
        public ClassOrVoid<ArrayHeader_CptUse,want_cpt_use>,
        public ClassOrVoid<ArrayHeader_SizeAndRese<len_size,len_rese>,( len_size or len_rese )>,
        public ClassOrVoid<ArrayHeader_MachineId,want_machine_id>,
        public ClassOrVoid<ArrayHeader_Ptr,want_ext_ptr> {};

/**
 @brief header of array objects (desribing size, ...).

 Followed by data of ext_ptr = false. It is assumed that alignment_in_bytes si a power of 2

 If ext_ptr == true, alignment_in_bytes is not used.
*/
template<int len_size,int len_rese,bool want_cpt_use,bool want_ext_ptr,bool want_machine_id,int alignment_in_bytes>
struct ArrayHeader : public ArrayHeaderBase<len_size,len_rese,want_cpt_use,want_ext_ptr,want_machine_id,alignment_in_bytes> {
    static const int base_size = sizeof( ArrayHeaderBase<len_size,len_rese,want_cpt_use,want_ext_ptr,want_machine_id,alignment_in_bytes> );
    static const int base_ceil = CEIL_P2( base_size, alignment_in_bytes );
    char extra_bytes[ base_ceil - base_size ];
};

//MO *init_dyn_array_dyn_dim( MO &res, const ST *size, int dim, Type *base_type = 0, const MachineId *mid = MachineId::cur() );

//MO *init_dyn_array( MO &res, const ST *size, Number<0>, Type *base_type = 0, const MachineId *mid = MachineId::cur() );
//MO *init_dyn_array( MO &res, const ST *size, Number<1>, Type *base_type = 0, const MachineId *mid = MachineId::cur() );
//MO *init_dyn_array( MO &res, const ST *size, Number<2>, Type *base_type = 0, const MachineId *mid = MachineId::cur() );
//MO *init_dyn_array( MO &res, const ST *size, Number<3>, Type *base_type = 0, const MachineId *mid = MachineId::cur() );
//MO *init_dyn_array( MO &res, const ST *size, Number<4>, Type *base_type = 0, const MachineId *mid = MachineId::cur() );

//template<int n>
//MO *init_dyn_array( MO &res, const ST *size, Number<n>, Type *base_type = 0, const MachineId *mid = MachineId::cur() ) {
//    return init_dyn_array_dyn_dim( res, size, n, base_type, mid );
//}

END_METIL_LEVEL1_NAMESPACE;

#endif // ARRAYDATA_H
