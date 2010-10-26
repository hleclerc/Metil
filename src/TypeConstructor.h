#ifndef TYPECONSTRUCTOR_H
#define TYPECONSTRUCTOR_H

#include "MethodCond.h"
#include "MethodWriter.h"

BEG_METIL_LEVEL1_NAMESPACE;

class TypeConstructor {
public:
    TypeConstructor();
    virtual void init( Type *type );

    #define DECL_COND( N ) \
        struct C0_has_##N : public MethodCond { virtual bool valid( Type *type_0, Type *, Type * ) const { return type_0->constructor->N(); } }; \
        struct C1_has_##N : public MethodCond { virtual bool valid( Type *, Type *type_1, Type * ) const { return type_1->constructor->N(); } }; \
        struct C2_has_##N : public MethodCond { virtual bool valid( Type *, Type *, Type *type_2 ) const { return type_2->constructor->N(); } }; \
        virtual bool N() const

    DECL_COND( Owcp_type ) { return Owcp_size() >= 0; }
    DECL_COND( Owcp_size_0 ) { return Owcp_size() == 0; }
    DECL_COND( Owcp_size_1 ) { return Owcp_size() == 1; }
    DECL_COND( Owcp_size_2 ) { return Owcp_size() == 2; }
    DECL_COND( Owcp_size_3 ) { return Owcp_size() == 3; }

    #undef DECL_COND

    virtual int Owcp_size() const;
    virtual void default_mw( MethodWriter &mw ) const;
    virtual int static_size_in_bytes() const;
    virtual int static_size_in_bits() const;
    virtual int tensor_order() const;
    virtual int needed_alignement_in_bits() const;

    bool have_been_initialized;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_H
