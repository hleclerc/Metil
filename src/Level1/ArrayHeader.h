#ifndef ARRAYDATA_H
#define ARRAYDATA_H

#include "ClassOrVoid.h"
#include "MO.h"

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

struct ArrayHeader_Ptr {
    void *ext_ptr;
};

/// header of array. Followed by data of ext_ptr = false
template<int len_size,int len_rese,bool want_cpt_use,bool want_ext_ptr>
struct ArrayHeader :
        public ClassOrVoid<ArrayHeader_CptUse,want_cpt_use>,
        public ClassOrVoid<ArrayHeader_SizeAndRese<len_size,len_rese>,( len_size or len_rese )>,
        public ClassOrVoid<ArrayHeader_Ptr,want_ext_ptr> {};


END_METIL_LEVEL1_NAMESPACE;

#endif // ARRAYDATA_H
