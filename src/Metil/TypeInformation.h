#ifndef TYPEINFORMATION_H
#define TYPEINFORMATION_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

template<class T>
struct TypeInformation {
};

#define DECL_TYPEINFORMATION( T ) template<> struct TypeInformation<T> { static const char *type() { return #T; } }

DECL_TYPEINFORMATION( SI8  );
DECL_TYPEINFORMATION( PI8  );
DECL_TYPEINFORMATION( SI16 );
DECL_TYPEINFORMATION( PI16 );
DECL_TYPEINFORMATION( SI32 );
DECL_TYPEINFORMATION( SI64 );
DECL_TYPEINFORMATION( FP32 );
DECL_TYPEINFORMATION( FP64 );

END_METIL_NAMESPACE;

#endif // TYPEINFORMATION_H
