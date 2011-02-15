#ifndef TYPECONSTRUCTOR_SYMBOLICARRAY_H
#define TYPECONSTRUCTOR_SYMBOLICARRAY_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  - nb children
  - ( ( size type ) type ) * nb children
  -
*/
class TypeConstructor_SymbolicArray : public TypeConstructor {
public:
    DECL_WRITER( convert_to_Bool );
    DECL_WRITER( write_str );

    virtual int Owcp_size() const;
    // virtual String Owcp_data() const;

    virtual void init( Type *type );

    Val op;
    BasicVec<Type *> children;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_SYMBOLICARRAY_H
