#ifndef TYPECONSTRUCTOR_SYMBOL_H
#define TYPECONSTRUCTOR_SYMBOL_H

#include "TypeConstructor_SymbolicExpression.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Symbol : public TypeConstructor_SymbolicExpression {
public:
    DECL_WRITER( write_str );

    virtual int Owcp_size() const { return 0; }
    virtual void default_mw( MethodWriter &mw ) const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_SYMBOL_H
