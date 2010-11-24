#ifndef TYPECONSTRUCTOR_LAZYOBJECT_H
#define TYPECONSTRUCTOR_LAZYOBJECT_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  Lazy object.


*/
class TypeConstructor_LazyObject : public TypeConstructor {
public:
    void write_header( MethodWriter &mw, const String &name_header, const String &data ) const;
    virtual void default_mw( MethodWriter &mw ) const;
    virtual String Owcp_data() const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_LAZYOBJECT_H
