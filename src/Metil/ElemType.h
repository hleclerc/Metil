#ifndef ELEMTYPE_H
#define ELEMTYPE_H

#include "Vec.h"

BEG_METIL_NAMESPACE;

/**
  Behavior of a parametric element
*/
class ElemType {
public:
    virtual int elem_id() const = 0;
    virtual int nvi() const = 0;
    virtual void make_rect( const Vec &X0, const Vec &X1, const Vec &XD, Vec *pos_nodes, Vec *connec ) const = 0;
};

extern const ElemType * const elem_type_Triangle;

END_METIL_NAMESPACE;

#endif // ELEMTYPE_H
