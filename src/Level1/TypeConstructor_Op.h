#ifndef TYPECONSTRUCTOR_OP_H
#define TYPECONSTRUCTOR_OP_H

#include "TypeConstructor_SymbolicExpression.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor_Op : public TypeConstructor_SymbolicExpression {
public:
    typedef enum {
        V_child, // Value
        P_child, // "positive" symbolic expression
        N_child  // "negative" symbolic expression
    } ChildType;

    DECL_WRITER( write_str );

    virtual int Owcp_size() const;
    virtual void init( Type *type );

    BasicVec<ChildType> child_types;
    String name;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_OP_H
