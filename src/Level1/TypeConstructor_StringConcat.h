#ifndef TYPECONSTRUCTOR_STRINGCONCAT_H
#define TYPECONSTRUCTOR_STRINGCONCAT_H

#include "TypeConstructor_String.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
Concatenation of two string.


*/
class TypeConstructor_StringConcat : public TypeConstructor_String {
public:
    virtual int Owcp_size() const { return 2; }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_STRINGCONCAT_H
