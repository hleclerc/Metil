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
extern TypeWithoutPtr<MethodName_add::TM>::T metil_def_add__VoidString_VoidString;

// 
void reg_def() {
    static MethodFinder<MethodName_add>::Item item_metil_def_add__VoidString_VoidString;
    item_metil_def_add__VoidString_VoidString.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__VoidString_VoidString.cond = 0;
    item_metil_def_add__VoidString_VoidString.meth = metil_def_add__VoidString_VoidString;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__VoidString_VoidString;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // AVOID_GEN
