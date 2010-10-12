#ifndef LST_H
#define LST_H

#include "Val.h"

BEG_METIL_NAMESPACE;


template<class T>
struct Lst {
    Lst() { type = &metil_type_ref_Array_m_1_0; }

    ~Lst() { type->del( *this ); }

    Val size() const { return type->size( *this ); }
};

END_METIL_NAMESPACE;

#endif // LST_H
