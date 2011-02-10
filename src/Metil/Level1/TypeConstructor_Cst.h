#ifndef TYPECONSTRUCTOR_CST_H
#define TYPECONSTRUCTOR_CST_H

#include "TypeConstructor_SymbolicExpression.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Cst : public TypeConstructor_SymbolicExpression {
public:
    DECL_WRITER( convert_to_Bool );
    DECL_WRITER( convert_to_SI32 );
    DECL_WRITER( convert_to_SI64 );
    DECL_WRITER( convert_to_FP32 );
    DECL_WRITER( convert_to_FP64 );
    DECL_WRITER( convert_to_FP80 );
    DECL_WRITER( write_str );

    String disp_str( bool num_conv = false ) const;

    virtual int equ_code( MethodWriter &mw, const Mos &args, const String &val ) const;
    virtual bool conversion_to( SI64 &val ) const;

    virtual int static_size_in_bits() const;
    virtual void init( Type *type );

    String name;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_CST_H
