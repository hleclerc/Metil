#ifndef TYPECONSTRUCTOR_H
#define TYPECONSTRUCTOR_H

#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor {
public:
    TypeConstructor();
    virtual void init( Type *type ) = 0;

    bool have_been_initialized;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_H
