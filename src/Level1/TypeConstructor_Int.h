#ifndef TYPECONSTRUCTOR_INT_H
#define TYPECONSTRUCTOR_INT_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Int : public TypeConstructor {
public:
    DECL_WRITER( convert_to_Bool );
    DECL_WRITER( convert_to_SI32 );
    DECL_WRITER( convert_to_SI64 );
    DECL_WRITER( convert_to_FP32 );
    DECL_WRITER( convert_to_FP64 );
    DECL_WRITER( convert_to_FP80 );
    DECL_WRITER( convert_to_ST   );

    virtual bool is_a_POD() const;
    virtual String cpp_type() const;
    virtual int static_size_in_bits() const;

    virtual void init( Type *type );
    int mant;
    int sign; ///< -1 -> negative, 0 -> signed, 1 -> positive
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_INT_H
