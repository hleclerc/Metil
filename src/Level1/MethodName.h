#ifndef METHODNAME_H
#define METHODNAME_H

#include "TypeWithoutPtr.h"
#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

// MethodName_add, MethodName_sub, ...
#define DECL_MET( TYPE, NAME ) \
   struct MethodName_##NAME { \
       typedef Type::Method_##TYPE TA; \
       typedef TypeWithoutPtr<Type::Method_##TYPE>::T TM; \
       static TA *&access( Type *type ) { return type->NAME; } \
       static const char *get_name() { return #NAME; } \
   }
   #include "DeclMethods.h"
#undef DECL_MET

END_METIL_LEVEL1_NAMESPACE

#endif // METHODNAME_H
