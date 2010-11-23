#include "TypeConstructor_LazyObject.h"
#include "LazyObjectData.h"
#include "MethodFinder.h"

BEG_METIL_LEVEL1_NAMESPACE;

static TypeConstructor_LazyObject *sc( Type *type ) {
    return static_cast<TypeConstructor_LazyObject *>( type->constructor );
}

// ... metil_def__...__when__a__isa__MORef( ... ) { Ad v = CM_1( copy, a ); return ... }
#include "def_LazyObj.h"

#define AVOID_DEL
#define AVOID_COPY

#define DECL_MET( T, N ) MET_##T( N )
#include "DeclMethods.h"
#undef DECL_MET

#define DECL_MET( T, N ) MET_1_##T( N )
#include "DeclMethodsBinary.h"
#undef DECL_MET


void TypeConstructor_LazyObject::default_mw( MethodWriter &mw ) const {
    mw.add_include( "Level1/LazyObjectData.h" );
}

END_METIL_LEVEL1_NAMESPACE;
