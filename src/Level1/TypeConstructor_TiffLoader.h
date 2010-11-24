#ifndef TYPECONSTRUCTOR_TIFFLOADER_H
#define TYPECONSTRUCTOR_TIFFLOADER_H

#include "TypeConstructor_LazyObject.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  Make an array from a String (filename)
*/
class TypeConstructor_TiffLoader : public TypeConstructor_LazyObject {
public:
    virtual void write_exec_node( MethodWriter &mw );
    virtual int Owcp_size() const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_TIFFLOADER_H
