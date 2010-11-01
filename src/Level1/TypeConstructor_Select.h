#ifndef TYPECONSTRUCTOR_SELECT_H
#define TYPECONSTRUCTOR_SELECT_H

#include "TypeConstructor_MORef.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
class TypeConstructor_Select : public TypeConstructor_MORef {
public:
    DECL_WRITER( copy );
    DECL_WRITER( del );

    virtual void init( Type *type );

    Type *type_a; ///< the a in a[ b ] or a( b )
    Type *type_b; ///< the b in a[ b ] or a( b )
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_SELECT_H
