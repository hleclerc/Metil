#ifndef METHODINFO_H
#define METHODINFO_H

#include "Methods.h"

BEG_METIL_LEVEL1_NAMESPACE;

//typedef MO   Method_OC     ( MO  a );
//typedef ST   Method_GC_ST  ( MO  a );
//typedef bool Method_GC_bool( MO  a );
//typedef SI32 Method_GC_SI32( MO  a );
//typedef SI64 Method_GC_SI64( MO  a );
//typedef FP32 Method_GC_FP32( MO  a );
//typedef FP64 Method_GC_FP64( MO  a );
//typedef FP80 Method_GC_FP80( MO  a );
//typedef vptr Method_GC_vptr( MO  a );
//typedef void Method_VCG_Str( MO  a, String &os );
//typedef vptr Method_GO_vptr( MO &a );
//typedef void Method_VO     ( MO &a );
//typedef void Method_VOG_Str( MO &a, String &os );
//typedef void Method_VOGG_CS( MO &a, const vptr *p, ST s );
//typedef void Method_VCGG_PS( MO  a, vptr *p, ST s );

//// binary
//typedef MO   (* Method_OCC)( MO  a, MO b );
//typedef bool (* Method_BCC)( MO  a, MO b );
//typedef void (* Method_VOC)( MO &a, MO b );
//typedef MO   (* Method_OOC)( MO &a, MO b );

// template<class TM>
// typedef MethodInfo {};
// 
// template<> typedef MethodInfo<Method_OC     > { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_ST  > { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_bool> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_SI32> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_SI64> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_FP32> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_FP64> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_FP80> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GC_vptr> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_VCG_Str> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_GO_vptr> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_VO     > { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_VOG_Str> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_VOGG_CS> { enum { nb_args = 1 }; };
// template<> typedef MethodInfo<Method_VCGG_PS> { enum { nb_args = 1 }; };


END_METIL_LEVEL1_NAMESPACE;

#endif // METHODINFO_H
