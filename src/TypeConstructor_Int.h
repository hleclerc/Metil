#ifndef TYPECONSTRUCTOR_INT_H
#define TYPECONSTRUCTOR_INT_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Int : public TypeConstructor {
public:
    virtual void init( Type *type );
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_INT_H
