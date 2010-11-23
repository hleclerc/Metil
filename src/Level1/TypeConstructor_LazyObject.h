#ifndef TYPECONSTRUCTOR_LAZYOBJECT_H
#define TYPECONSTRUCTOR_LAZYOBJECT_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  Lazy object.


*/
class TypeConstructor_LazyObject : public TypeConstructor {
public:
    virtual void default_mw( MethodWriter &mw ) const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_LAZYOBJECT_H
