#ifndef TYPECONSTRUCTOR_GPUTEX_H
#define TYPECONSTRUCTOR_GPUTEX_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/*
  GpuTex_[dim]_[type]
*/
class TypeConstructor_GpuTex : public TypeConstructor {
public:
    virtual int Owcp_size() const;
    virtual String Owcp_data() const;
    virtual void default_mw( MethodWriter &mw ) const;
    virtual void init( Type *type );

    int dim;
    Type *item_type_bas;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_GPUTEX_H
