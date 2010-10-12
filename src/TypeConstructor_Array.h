#ifndef TYPECONSTRUCTOR_ARRAY_H
#define TYPECONSTRUCTOR_ARRAY_H

#include "TypeConstructor.h"
#include "BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Array : public TypeConstructor {
public:
    virtual void init( Type *type );

    BasicVec<ST> size;
    BasicVec<ST> rese;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_ARRAY_H
