#include "TypeConstructor.h"
#include "BasicMethods.h"
#include "Dout.h"

BEG_METIL_LEVEL1_NAMESPACE;

static int nb_types = 1; ///< Nb types of @em instantiated objects (i.e. nb types that have been used at least one time). type number 0 is fake.
static Type *last_type = 0; ///< pointer on type list. Contains all the types, including the non instantiated ones

template<class TM>
void init_method( TM *m, int nb_types, const char *name ) {
    *m = generator
}

template<class TM>
void init_method( TM **m, int nb_types, const char *name ) {
}

Type::Type( TypeConstructor *constructor, const char *name, Type *bas, Type *ref, Type *cst, BRC k ) : number( 0 ), name( name ), constructor( constructor ), bas_type( bas ), ref_type( ref ), cst_type( cst )  {
    prev_type = last_type;
    last_type = this;

    // initilisation of method ptr with "generators"
//    #define DECL_MET( T, N ) MethodManagerOf<MethodName_##N>::init( this, nb_types )
//    #include "DeclMethods.h"
//    #undef DECL_MET
    #define DECL_MET( T, N ) init_method( N, nb_types, #N )
    #include "DeclMethods.h"
    #undef DECL_MET

}

Type::~Type() {
}

Type *Type::init_if_necessary() {
    return this;
}

END_METIL_LEVEL1_NAMESPACE;
