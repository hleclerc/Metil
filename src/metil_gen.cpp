// generated file. Do not edit
#ifndef AVOID_GEN

#include "metil_gen.h"
#include "MethodFinder.h"

#include "TypeConstructor_ConstCharPtr.h"
#include "TypeConstructor_FileWithoutClose.h"
#include "TypeConstructor_String.h"
#include "TypeConstructor_StringConcat.h"
#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;


// Type definition
static TypeConstructor_ConstCharPtr type_constructor_ConstCharPtr;
Type metil_type_cst_ConstCharPtr( &type_constructor_ConstCharPtr, "ConstCharPtr", 0, 0, &metil_type_cst_ConstCharPtr, Type::Ref );
static TypeConstructor_FileWithoutClose type_constructor_FileWithoutClose;
Type metil_type_ref_FileWithoutClose( &type_constructor_FileWithoutClose, "FileWithoutClose", 0, &metil_type_ref_FileWithoutClose, 0, Type::Cst );
static TypeConstructor_StringConcat type_constructor_StringConcat;
Type metil_type_bas_StringConcat( &type_constructor_StringConcat, "StringConcat", &metil_type_bas_StringConcat, 0, 0, Type::Bas );
static TypeConstructor_VoidString type_constructor_VoidString;
Type metil_type_cst_VoidString( &type_constructor_VoidString, "VoidString", 0, 0, &metil_type_cst_VoidString, Type::Ref );

// method references
extern MethodName_self_append::TM metil_def_self_append__pert_0;extern MethodName_copy::TM metil_def_copy__when__a__isa__ConstCharPtr__pert__1;extern MethodName_self_append::TM metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;extern MethodName_append::TM metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;extern MethodName_self_append::TM metil_def_self_append__when__a__isa__VoidString__pert__1;extern MethodName_self_append::TM metil_def_self_append__when__b__isa__VoidString__pert__2;

// reg_def
void reg_def() {
    static MethodCond_True cond_metil_def_self_append__pert_0;

    static const char *string_0 = "./src/TypeConstructor.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__pert_0.cond = &cond_metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.meth = metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.file = string_0;
    item_metil_def_self_append__pert_0.line = 6;
    item_metil_def_self_append__pert_0.pert = 0;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__pert_0;

    static MethodCond_Cons_0_IsChildOf<TypeConstructor_ConstCharPtr> cond_metil_def_copy__when__a__isa__ConstCharPtr__pert__1;

    static const char *string_1 = "./src/TypeConstructor_ConstCharPtr.cpp";

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr__pert__1;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.meth = metil_def_copy__when__a__isa__ConstCharPtr__pert__1;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.file = string_1;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.line = 5;
    item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__isa__ConstCharPtr__pert__1;

    static MethodCond_And<MethodCond_Cons_0_IsChildOf<TypeConstructor_FileWithoutClose>,MethodCond_Cons_1_IsChildOf<TypeConstructor_ConstCharPtr> > cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;

    static const char *string_2 = "./src/TypeConstructor_FileWithoutClose.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.meth = metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.file = string_2;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.line = 9;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;

    static MethodCond_And<MethodCond_Cons_0_IsChildOf<TypeConstructor_String>,MethodCond_Cons_1_IsChildOf<TypeConstructor_String> > cond_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;

    static const char *string_3 = "./src/TypeConstructor_String.cpp";

    static MethodFinder<MethodName_append>::Item item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.prev = MethodFinder<MethodName_append>::last;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.cond = &cond_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.meth = metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.file = string_3;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.line = 5;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.pert = 0;
    MethodFinder<MethodName_append>::last = &item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;

    static MethodCond_Cons_0_IsChildOf<TypeConstructor_VoidString> cond_metil_def_self_append__when__a__isa__VoidString__pert__1;

    static const char *string_4 = "./src/TypeConstructor_VoidString.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__VoidString__pert__1;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.cond = &cond_metil_def_self_append__when__a__isa__VoidString__pert__1;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.meth = metil_def_self_append__when__a__isa__VoidString__pert__1;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.file = string_4;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.line = 6;
    item_metil_def_self_append__when__a__isa__VoidString__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__VoidString__pert__1;

    static MethodCond_Cons_1_IsChildOf<TypeConstructor_VoidString> cond_metil_def_self_append__when__b__isa__VoidString__pert__2;

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__b__isa__VoidString__pert__2;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.cond = &cond_metil_def_self_append__when__b__isa__VoidString__pert__2;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.meth = metil_def_self_append__when__b__isa__VoidString__pert__2;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.file = string_4;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.line = 7;
    item_metil_def_self_append__when__b__isa__VoidString__pert__2.pert = 2;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__b__isa__VoidString__pert__2;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // AVOID_GEN
