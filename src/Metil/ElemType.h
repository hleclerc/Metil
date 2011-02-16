#ifndef ELEMTYPE_H
#define ELEMTYPE_H

#include "BasicVec.h"
#include "Val.h"

BEG_METIL_NAMESPACE;

/**
  Behavior of a parametric element
*/
class ElemType {
public:
    typedef float T;
    virtual int elem_id() const = 0;
    virtual int nvi() const = 0;
    virtual void make_rect( const BasicVec<float> &X0, const BasicVec<float> &X1, const BasicVec<int> &XD, BasicVec<BasicVec<float> > &pos_nodes, BasicVec<BasicVec<int> > &connec ) const = 0;
};

extern const ElemType * const elem_type_Triangle;

END_METIL_NAMESPACE;

#endif // ELEMTYPE_H
