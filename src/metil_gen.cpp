// generated file. Do not edit
#ifndef AVOID_GEN

#include "metil_gen.h"
#include "MethodFinder.h"

#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;


// Type definition
static TypeConstructor_VoidString type_constructor_VoidString;
Type metil_type_bas_VoidString( &type_constructor_VoidString, "VoidString", &metil_type_bas_VoidString, 0, 0, Type::Bas );

// declaration of methods
extern TypeWithoutPtr<MethodName_add::TM>::T metil_def_add__VoidString__VoidString;

// 
void reg_def() {
    static MethodCond_And<MethodCond_Cons_0_IsChildOf<TypeConstructor_VoidString>,MethodCond_Cons_1_IsChildOf<TypeConstructor_VoidString> > cond_metil_def_add__VoidString__VoidString;
    static MethodFinder<MethodName_add>::Item item_metil_def_add__VoidString__VoidString;
    item_metil_def_add__VoidString__VoidString.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__VoidString__VoidString.cond = &cond_metil_def_add__VoidString__VoidString;
    item_metil_def_add__VoidString__VoidString.meth = metil_def_add__VoidString__VoidString;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__VoidString__VoidString;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // AVOID_GEN
