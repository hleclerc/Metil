#include "MethodFinder.h"
#include "MethodName.h"

BEG_METIL_LEVEL1_NAMESPACE;

#define DECL_MET( T, N ) template<> MethodFinder<MethodName_##N>::Item *MethodFinder<MethodName_##N>::last = 0;
#include "DeclMethods.h"
#undef DECL_MET

END_METIL_LEVEL1_NAMESPACE;
