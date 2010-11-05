#ifndef TYPECONSTRUCTOR_VOIDSTRING_H
#define TYPECONSTRUCTOR_VOIDSTRING_H

#include "TypeConstructor_String.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**  */
class TypeConstructor_VoidString : public TypeConstructor_String {
public:
    virtual bool is_void() const { return true; }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_VOIDSTRING_H
