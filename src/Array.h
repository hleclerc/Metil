#ifndef ARRAY_H
#define ARRAY_H

#include "Val.h"

BEG_METIL_NAMESPACE;

/**
  multidimensionnal array

*/
template<class T>
struct Array : public Level1::MO {
    Array( ST dim ) {
        static Level1::Type *lst[] = {
            &Level1::metil_type_ref_Array_0_1_0,
            &Level1::metil_type_ref_Array_1_1_0_0_0,
            &Level1::metil_type_ref_Array_2_1_0_0_0_0_0,
            &Level1::metil_type_ref_Array_3_1_0_0_0_0_0_0_0,
            &Level1::metil_type_ref_Array_4_1_0_0_0_0_0_0_0_0_0,
            &Level1::metil_type_ref_Array_5_1_0_0_0_0_0_0_0_0_0_0_0,
        };
        ASSERT( dim < 6, "TODO" );
        type = lst[ dim ];
    }

    ~Array() { type->del( *this ); }

    Val size() const { return type->size( *this ); }
};

END_METIL_NAMESPACE;

#endif // ARRAY_H