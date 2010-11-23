#ifndef TYPECONSTRUCTOR_DISTANTOBJECT_H
#define TYPECONSTRUCTOR_DISTANTOBJECT_H

#include "TypeConstructor.h"
#include "MachineId.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  Object which may be on a distant machine

  DistantObject_[Cpu|Gpu|...]
*/
class TypeConstructor_DistantObject : public TypeConstructor {
public:
    virtual void default_mw( MethodWriter &mw ) const;
    virtual void init( Type *type );

    MachineId::Type provenance;
    Type *base_type;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_DISTANTOBJECT_H
