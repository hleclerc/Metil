#ifndef TYPECONSTRUCTOR_LAZYOPERATION_H
#define TYPECONSTRUCTOR_LAZYOPERATION_H

#include "TypeConstructor_LazyObject.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_LazyOperation : public TypeConstructor_LazyObject {
public:
    virtual int Owcp_size() const;
    virtual String Owcp_data() const;
    virtual void default_mw( MethodWriter &mw );
    virtual void init( Type *type );

    String name_operation;
    String type_operation;
    int nb_args;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_LAZYOPERATION_H
