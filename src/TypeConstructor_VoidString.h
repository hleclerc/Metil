#ifndef TYPECONSTRUCTOR_VOIDSTRING_H
#define TYPECONSTRUCTOR_VOIDSTRING_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**  */
class TypeConstructor_VoidString : public TypeConstructor {
public:
    virtual void init( Type *type );
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_VOIDSTRING_H
