#ifndef TYPECONSTRUCTOR_MATLABSTRING_H
#define TYPECONSTRUCTOR_MATLABSTRING_H

#include "TypeConstructor_String.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_MatlabString : public TypeConstructor_String {
public:
    virtual void default_mw( MethodWriter &mw ) const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_MATLABSTRING_H
