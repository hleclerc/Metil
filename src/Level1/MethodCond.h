#ifndef METHODCOND_H
#define METHODCOND_H

#include "StringHelp.h"
#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const = 0;
};

struct MethodCond_True : public MethodCond {
    virtual bool valid( Type *, Type *, Type * ) const { return true; }
};

template<class T>
struct MethodCond_0_isa : public MethodCond {
    virtual bool valid( Type *type_0, Type *, Type * ) const { return dynamic_cast<T *>( type_0->constructor ); }
};

template<class T>
struct MethodCond_1_isa : public MethodCond {
    virtual bool valid( Type *, Type *type_1, Type * ) const { return dynamic_cast<T *>( type_1->constructor ); }
};

template<class T>
struct MethodCond_2_isa : public MethodCond {
    virtual bool valid( Type *, Type *, Type *type_2 ) const { return dynamic_cast<T *>( type_2->constructor ); }
};

template<class C_0,class C_1>
struct MethodCond_and : public MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const {
        return cond_0.valid( type_0, type_1, type_2 ) and cond_1.valid( type_0, type_1, type_2 );
    }
    C_0 cond_0;
    C_1 cond_1;
};

template<class C_0,class C_1>
struct MethodCond_or : public MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const {
        return cond_0.valid( type_0, type_1, type_2 ) or cond_1.valid( type_0, type_1, type_2 );
    }
    C_0 cond_0;
    C_1 cond_1;
};

template<class C_0>
struct MethodCond_not : public MethodCond {
    virtual bool valid( Type *type_0, Type *type_1, Type *type_2 ) const {
        return not cond_0.valid( type_0, type_1, type_2 );
    }
    C_0 cond_0;
};

struct MethodCond_0_is : public MethodCond {
    virtual bool valid( Type *type_0, Type *, Type * ) const { return equal( type_0->name, type ); }
    const char *type;
};

struct MethodCond_1_is : public MethodCond {
    virtual bool valid( Type *, Type *type_1, Type * ) const { return equal( type_1->name, type ); }
    const char *type;
};

struct MethodCond_2_is : public MethodCond {
    virtual bool valid( Type *, Type *, Type *type_2 ) const { return equal( type_2->name, type ); }
    const char *type;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODCOND_H
