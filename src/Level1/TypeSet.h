#ifndef TYPESET_H
#define TYPESET_H

#include "../MetilString.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct TypeConstructor;

struct TypeSetAncestor {
    NEW_AND_DEL_COMPATIBLE_PURE_VIRTUAL;
    TypeSetAncestor( const String &name, TypeConstructor *constructor ) :
        name( name.new_c_str() ),
        bas_type( constructor, this->name, &bas_type, &ref_type, &cst_type, Type::Bas ),
        ref_type( constructor, this->name, &bas_type, &ref_type, &cst_type, Type::Ref ),
        cst_type( constructor, this->name, &bas_type, &ref_type, &cst_type, Type::Cst ) {
    }

    virtual ~TypeSetAncestor() {
        std::free( name );
    }

    char *name;
    Type bas_type;
    Type ref_type;
    Type cst_type;
};

template<class TypeConstructorKind>
struct TypeSet : public TypeSetAncestor {
    NEW_AND_DEL_COMPATIBLE;
    TypeSet( const String &name ) : TypeSetAncestor( name, &constructor ) {}

    TypeConstructorKind constructor;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPESET_H
