#include "ElemType.h"

BEG_METIL_NAMESPACE;

struct ElemTypeTriangle : public ElemType {
    virtual int elem_id() const { return 0; }
};

#define IP( E ) \
    ElemType##E inst_elem_type_##E; \
    const ElemType *const elem_type_##E = &inst_elem_type_##E

IP( Triangle );

END_METIL_NAMESPACE;
