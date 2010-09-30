#ifndef TYPE_H
#define TYPE_H

#include "Methods.h"
#include "Malloc.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct TypeConstructor;

/** @brief collection of method for basic Metil objects


*/
class Type {
public:
    CANNOT_BE_DERIVED;
    typedef enum { Bas, Ref, Cst } BRC;

    Type( TypeConstructor *constructor, const char *name, Type *bas, Type *ref, Type *cst, BRC k );
    ~Type();

    int              number;      ///< id of the type. must be the first attribute of Type
    Type            *prev_type;   ///< prev_type on the list that contains all the types
    const char      *name;        ///< type name like "SI32"...
    TypeConstructor *constructor; ///< what to do during first initialisation, basic type information, ...

    Type            *bas_type;    ///< base type (like e.g. "int")
    Type            *ref_type;    ///< reference type (like e.g. "int &")
    Type            *cst_type;    ///< constant reference (e.g. "const int &")
    BRC             k;

    Type *init_if_necessary(); ///< called the first time a method a called

    #define DECL_MET( T, N ) Method_##T *N
    #include "DeclMethods.h"
    #undef DECL_MET
};

/// Call Method
#define CM_1( M, A ) (A).type->M( A )
#define CM_2( M, A, B ) (A).type->M[ (B).type->number ]( A, B )

END_METIL_LEVEL1_NAMESPACE;

// generated file
#include "metil_gen.h"

#endif // TYPE_H

