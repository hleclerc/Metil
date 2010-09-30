#ifndef METHODCOND_H
#define METHODCOND_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const = 0;
};

template<class T>
struct MethodCond_Cons_0_IsChildOf {
    virtual bool valid( Type *type_0, Type *, Type * ) const { return dynamic_cast<T>( type_0->constructor ); }
};

template<class T>
struct MethodCond_Cons_1_IsChildOf {
    virtual bool valid( Type *, Type *type_1, Type * ) const { return dynamic_cast<T>( type_1->constructor ); }
};

template<class T>
struct MethodCond_Cons_2_IsChildOf {
    virtual bool valid( Type *, Type *, Type *type_2 ) const { return dynamic_cast<T>( type_2->constructor ); }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODCOND_H
