#include "TypeConstructor_MORef.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

// ... metil_def__...__when__a__isa__MORef( ... ) { Ad v = CM_1( copy, a ); return ... }
#include "def_MORef.h"

#define AVOID_DEL
#define AVOID_COPY

#define DECL_MET( T, N ) MET_##T( N )
#include "DeclMethods.h"
#undef DECL_MET

#define DECL_MET( T, N ) MET_1_##T( N )
#include "DeclMethodsBinary.h"
#undef DECL_MET


END_METIL_LEVEL1_NAMESPACE;
