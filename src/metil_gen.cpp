// generated file. Do not edit
#ifndef AVOID_GEN

#include "metil_gen.h"
#include "MethodFinder.h"

#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;


// Type definition
static TypeConstructor_VoidString type_constructor_VoidString;
Type metil_type_bas_VoidString( &type_constructor_VoidString, "VoidString", &metil_type_bas_VoidString, 0, 0, Type::Bas );

// method references
extern MethodName_add::TM metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;
// reg_def
void reg_def() {
    static MethodCond_And<MethodCond_Cons_0_IsChildOf<TypeConstructor_VoidString>,MethodCond_Cons_1_IsChildOf<TypeConstructor_VoidString> > cond_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;

    static MethodFinder<MethodName_add>::Item item_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;
    item_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString.cond = &cond_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;
    item_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString.meth = metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // AVOID_GEN
