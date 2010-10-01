#ifndef METHODCOND_H
#define METHODCOND_H

#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const = 0;
};

struct MethodCond_True {
    virtual bool valid( Type *, Type *, Type * ) const { return true; }
};

template<class T>
struct MethodCond_Cons_0_IsChildOf : public MethodCond {
    virtual bool valid( Type *type_0, Type *, Type * ) const { return dynamic_cast<T *>( type_0->constructor ); }
};

template<class T>
struct MethodCond_Cons_1_IsChildOf : public MethodCond {
    virtual bool valid( Type *, Type *type_1, Type * ) const { return dynamic_cast<T *>( type_1->constructor ); }
};

template<class T>
struct MethodCond_Cons_2_IsChildOf : public MethodCond {
    virtual bool valid( Type *, Type *, Type *type_2 ) const { return dynamic_cast<T *>( type_2->constructor ); }
};

template<class C_0,class C_1>
struct MethodCond_And : public MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const {
        return cond_0.valid( type_0, type_1, type_2 ) and cond_1.valid( type_0, type_1, type_2 );
    }
    C_0 cond_0;
    C_1 cond_1;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODCOND_H
