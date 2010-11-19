#ifndef TYPECONSTRUCTOR_LAZYOBJECT_H
#define TYPECONSTRUCTOR_LAZYOBJECT_H

#include "TypeConstructor.h"
#include "MachineId.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  Lazy object.

  name contains
    - provenance type (Loc, Cpu, Gpu, ...) -> a 3 letters word, followed by a _
    - type

*/
class TypeConstructor_LazyObject : public TypeConstructor {
public:
    virtual void default_mw( MethodWriter &mw ) const;
    virtual void init( Type *type );

    MachineId::Type provenance;
    Type *base_type;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_LAZYOBJECT_H
