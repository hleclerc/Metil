#ifndef TYPECONSTRUCTOR_CST_H
#define TYPECONSTRUCTOR_CST_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Cst : public TypeConstructor {
public:
    DECL_WRITER( convert_to_Bool );
    DECL_WRITER( convert_to_SI32 );
    DECL_WRITER( convert_to_SI64 );
    DECL_WRITER( convert_to_FP32 );
    DECL_WRITER( convert_to_FP64 );
    DECL_WRITER( convert_to_FP80 );

    String disp_str() const;

    virtual int static_size_in_bits() const;
    virtual void init( Type *type );

    String name;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_CST_H
