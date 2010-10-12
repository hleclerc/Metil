#ifndef ELEMTYPE_H
#define ELEMTYPE_H

#include "Val.h"

BEG_METIL_NAMESPACE;

/**
  Behavior of a parametric element
*/
class ElemType {
public:
    virtual int elem_id() const = 0;
};

extern const ElemType * const elem_type_Triangle;

END_METIL_NAMESPACE;

#endif // ELEMTYPE_H
