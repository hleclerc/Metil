// generated file. Do not edit
#ifndef AVOID_GEN

#include "metil_gen.h"
#include "MethodFinder.h"

#include "TypeConstructor_ConstCharPtr.h"
#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "TypeConstructor_Cst.h"
#include "TypeConstructor_File.h"
#include "TypeConstructor_FileWithoutClose.h"
#include "TypeConstructor_Flt.h"
#include "TypeConstructor_Int.h"
#include "TypeConstructor_OwcpString.h"
#include "TypeConstructor_String.h"
#include "TypeConstructor_StringConcat.h"
#include "TypeConstructor_VoidString.h"

BEG_METIL_LEVEL1_NAMESPACE;


// Type definition
static TypeConstructor_ConstCharPtr type_constructor_ConstCharPtr;
Type metil_type_cst_ConstCharPtr( &type_constructor_ConstCharPtr, "ConstCharPtr", 0, 0, &metil_type_cst_ConstCharPtr, Type::Ref );

static TypeConstructor_ConstCharPtrWithSize type_constructor_ConstCharPtrWithSize;
Type metil_type_bas_ConstCharPtrWithSize( &type_constructor_ConstCharPtrWithSize, "ConstCharPtrWithSize", &metil_type_bas_ConstCharPtrWithSize, 0, 0, Type::Bas );

static TypeConstructor_Cst type_constructor_Cst_zero;
Type metil_type_cst_Cst_zero( &type_constructor_Cst_zero, "Cst_zero", 0, 0, &metil_type_cst_Cst_zero, Type::Ref );

static TypeConstructor_File type_constructor_File;
Type metil_type_bas_File( &type_constructor_File, "File", &metil_type_bas_File, 0, 0, Type::Bas );

static TypeConstructor_FileWithoutClose type_constructor_FileWithoutClose;
Type metil_type_ref_FileWithoutClose( &type_constructor_FileWithoutClose, "FileWithoutClose", 0, &metil_type_ref_FileWithoutClose, 0, Type::Cst );

static TypeConstructor_Flt type_constructor_Flt_32;
Type metil_type_bas_Flt_32( &type_constructor_Flt_32, "Flt_32", &metil_type_bas_Flt_32, &metil_type_ref_Flt_32, 0, Type::Bas );
Type metil_type_ref_Flt_32( &type_constructor_Flt_32, "Flt_32", &metil_type_bas_Flt_32, &metil_type_ref_Flt_32, 0, Type::Cst );

static TypeConstructor_Flt type_constructor_Flt_64;
Type metil_type_bas_Flt_64( &type_constructor_Flt_64, "Flt_64", &metil_type_bas_Flt_64, &metil_type_ref_Flt_64, 0, Type::Bas );
Type metil_type_ref_Flt_64( &type_constructor_Flt_64, "Flt_64", &metil_type_bas_Flt_64, &metil_type_ref_Flt_64, 0, Type::Cst );

static TypeConstructor_Flt type_constructor_Flt_80;
Type metil_type_bas_Flt_80( &type_constructor_Flt_80, "Flt_80", &metil_type_bas_Flt_80, &metil_type_ref_Flt_80, 0, Type::Bas );
Type metil_type_ref_Flt_80( &type_constructor_Flt_80, "Flt_80", &metil_type_bas_Flt_80, &metil_type_ref_Flt_80, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_n_16;
Type metil_type_bas_Int_n_16( &type_constructor_Int_n_16, "Int_n_16", &metil_type_bas_Int_n_16, &metil_type_ref_Int_n_16, 0, Type::Bas );
Type metil_type_ref_Int_n_16( &type_constructor_Int_n_16, "Int_n_16", &metil_type_bas_Int_n_16, &metil_type_ref_Int_n_16, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_n_32;
Type metil_type_bas_Int_n_32( &type_constructor_Int_n_32, "Int_n_32", &metil_type_bas_Int_n_32, &metil_type_ref_Int_n_32, 0, Type::Bas );
Type metil_type_ref_Int_n_32( &type_constructor_Int_n_32, "Int_n_32", &metil_type_bas_Int_n_32, &metil_type_ref_Int_n_32, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_n_64;
Type metil_type_bas_Int_n_64( &type_constructor_Int_n_64, "Int_n_64", &metil_type_bas_Int_n_64, &metil_type_ref_Int_n_64, 0, Type::Bas );
Type metil_type_ref_Int_n_64( &type_constructor_Int_n_64, "Int_n_64", &metil_type_bas_Int_n_64, &metil_type_ref_Int_n_64, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_n_8;
Type metil_type_bas_Int_n_8( &type_constructor_Int_n_8, "Int_n_8", &metil_type_bas_Int_n_8, &metil_type_ref_Int_n_8, 0, Type::Bas );
Type metil_type_ref_Int_n_8( &type_constructor_Int_n_8, "Int_n_8", &metil_type_bas_Int_n_8, &metil_type_ref_Int_n_8, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_p_16;
Type metil_type_bas_Int_p_16( &type_constructor_Int_p_16, "Int_p_16", &metil_type_bas_Int_p_16, &metil_type_ref_Int_p_16, 0, Type::Bas );
Type metil_type_ref_Int_p_16( &type_constructor_Int_p_16, "Int_p_16", &metil_type_bas_Int_p_16, &metil_type_ref_Int_p_16, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_p_32;
Type metil_type_bas_Int_p_32( &type_constructor_Int_p_32, "Int_p_32", &metil_type_bas_Int_p_32, &metil_type_ref_Int_p_32, 0, Type::Bas );
Type metil_type_ref_Int_p_32( &type_constructor_Int_p_32, "Int_p_32", &metil_type_bas_Int_p_32, &metil_type_ref_Int_p_32, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_p_64;
Type metil_type_bas_Int_p_64( &type_constructor_Int_p_64, "Int_p_64", &metil_type_bas_Int_p_64, &metil_type_ref_Int_p_64, 0, Type::Bas );
Type metil_type_ref_Int_p_64( &type_constructor_Int_p_64, "Int_p_64", &metil_type_bas_Int_p_64, &metil_type_ref_Int_p_64, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_p_8;
Type metil_type_bas_Int_p_8( &type_constructor_Int_p_8, "Int_p_8", &metil_type_bas_Int_p_8, &metil_type_ref_Int_p_8, 0, Type::Bas );
Type metil_type_ref_Int_p_8( &type_constructor_Int_p_8, "Int_p_8", &metil_type_bas_Int_p_8, &metil_type_ref_Int_p_8, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_s_16;
Type metil_type_bas_Int_s_16( &type_constructor_Int_s_16, "Int_s_16", &metil_type_bas_Int_s_16, &metil_type_ref_Int_s_16, 0, Type::Bas );
Type metil_type_ref_Int_s_16( &type_constructor_Int_s_16, "Int_s_16", &metil_type_bas_Int_s_16, &metil_type_ref_Int_s_16, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_s_32;
Type metil_type_bas_Int_s_32( &type_constructor_Int_s_32, "Int_s_32", &metil_type_bas_Int_s_32, &metil_type_ref_Int_s_32, 0, Type::Bas );
Type metil_type_ref_Int_s_32( &type_constructor_Int_s_32, "Int_s_32", &metil_type_bas_Int_s_32, &metil_type_ref_Int_s_32, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_s_64;
Type metil_type_bas_Int_s_64( &type_constructor_Int_s_64, "Int_s_64", &metil_type_bas_Int_s_64, &metil_type_ref_Int_s_64, 0, Type::Bas );
Type metil_type_ref_Int_s_64( &type_constructor_Int_s_64, "Int_s_64", &metil_type_bas_Int_s_64, &metil_type_ref_Int_s_64, 0, Type::Cst );

static TypeConstructor_Int type_constructor_Int_s_8;
Type metil_type_bas_Int_s_8( &type_constructor_Int_s_8, "Int_s_8", &metil_type_bas_Int_s_8, &metil_type_ref_Int_s_8, 0, Type::Bas );
Type metil_type_ref_Int_s_8( &type_constructor_Int_s_8, "Int_s_8", &metil_type_bas_Int_s_8, &metil_type_ref_Int_s_8, 0, Type::Cst );

static TypeConstructor_OwcpString type_constructor_OwcpString;
Type metil_type_bas_OwcpString( &type_constructor_OwcpString, "OwcpString", &metil_type_bas_OwcpString, 0, 0, Type::Bas );

static TypeConstructor_StringConcat type_constructor_StringConcat;
Type metil_type_bas_StringConcat( &type_constructor_StringConcat, "StringConcat", &metil_type_bas_StringConcat, 0, 0, Type::Bas );

static TypeConstructor_VoidString type_constructor_VoidString;
Type metil_type_cst_VoidString( &type_constructor_VoidString, "VoidString", 0, 0, &metil_type_cst_VoidString, Type::Ref );


// method references
extern MethodName_del::TM metil_def_del__when__a__isa__File;
extern MethodName_self_append::TM metil_def_self_append__pert_0;
extern MethodName_reassign::TM metil_def_reassign__pert_0;
extern MethodName_add_parent::TM metil_def_add_parent__pert_0;
extern MethodName_rem_parent::TM metil_def_rem_parent__pert_0;
extern MethodName_convert_to_SI32::TM metil_def_convert_to_SI32__when__a__is__Cst_zero;
extern MethodName_copy::TM metil_def_copy__when__a__isa__ConstCharPtr;
extern MethodName_size::TM metil_def_size__when__a__isa__ConstCharPtr;
extern MethodName_ptr_z::TM metil_def_ptr_z__when__a__isa__ConstCharPtr;
extern MethodName_new_ptr_z::TM metil_def_new_ptr_z__when__a__isa__ConstCharPtr;
extern MethodName_copy_data::TM metil_def_copy_data__when__a__isa__ConstCharPtr;
extern MethodName_equal::TM metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
extern MethodName_find::TM metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
extern MethodName_end_from::TM metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
extern MethodName_beg_upto::TM metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
extern MethodName_del::TM metil_def_del__when__a__isa__OwcpString;
extern MethodName_copy::TM metil_def_copy__when__a__isa__OwcpString;
extern MethodName_size::TM metil_def_size__when__a__isa__OwcpString;
extern MethodName_ptr_z::TM metil_def_ptr_z__when__a__isa__OwcpString;
extern MethodName_new_ptr_z::TM metil_def_new_ptr_z__when__a__isa__OwcpString;
extern MethodName_copy_data::TM metil_def_copy_data__when__a__isa__OwcpString;
extern MethodName_find::TM metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;
extern MethodName_beg_upto::TM metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
extern MethodName_end_from::TM metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
extern MethodName_flush::TM metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
extern MethodName_write::TM metil_def_write__when__a__isa__FileWithoutClose__pert__1;
extern MethodName_convert_to_Bool::TM metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;
extern MethodName_self_append::TM metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;
extern MethodName_ptr_z::TM metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1;
extern MethodName_del::TM metil_def_del__when__a__is__Int_s_64;
extern MethodName_del::TM metil_def_del__when__a__is__Int_s_32;
extern MethodName_copy::TM metil_def_copy__when__a__is__Int_s_32;
extern MethodName_copy::TM metil_def_copy__when__a__is__Int_s_64;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;
extern MethodName_convert_to_Bool::TM metil_def_convert_to_Bool__when__a__is__Int_s_64;
extern MethodName_convert_to_SI32::TM metil_def_convert_to_SI32__when__a__is__Int_s_64;
extern MethodName_convert_to_SI64::TM metil_def_convert_to_SI64__when__a__is__Int_s_64;
extern MethodName_convert_to_Bool::TM metil_def_convert_to_Bool__when__a__is__Int_s_32;
extern MethodName_convert_to_SI32::TM metil_def_convert_to_SI32__when__a__is__Int_s_32;
extern MethodName_convert_to_SI64::TM metil_def_convert_to_SI64__when__a__is__Int_s_32;
extern MethodName_add::TM metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_add::TM metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_add::TM metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_add::TM metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_sub::TM metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_sub::TM metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_sub::TM metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_sub::TM metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_mul::TM metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_mul::TM metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_mul::TM metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_mul::TM metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_sup::TM metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_sup::TM metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_sup::TM metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_sup::TM metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_supeq::TM metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_supeq::TM metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_supeq::TM metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_supeq::TM metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_inf::TM metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_inf::TM metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_inf::TM metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_inf::TM metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_infeq::TM metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_infeq::TM metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_infeq::TM metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_infeq::TM metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_boolean_or::TM metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_boolean_or::TM metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_boolean_or::TM metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_boolean_or::TM metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_boolean_and::TM metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32;
extern MethodName_boolean_and::TM metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64;
extern MethodName_boolean_and::TM metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32;
extern MethodName_boolean_and::TM metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64;
extern MethodName_append::TM metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
extern MethodName_equal::TM metil_def_equal__when__a__isa__String__and__b__isa__String;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;
extern MethodName_size::TM metil_def_size__when__a__isa__StringConcat;
extern MethodName_copy_data::TM metil_def_copy_data__when__a__isa__StringConcat;
extern MethodName_ptr_z::TM metil_def_ptr_z__when__a__isa__StringConcat;
extern MethodName_new_ptr_z::TM metil_def_new_ptr_z__when__a__isa__StringConcat;
extern MethodName_del::TM metil_def_del__when__a__isa__ConstCharPtrWithSize;
extern MethodName_copy::TM metil_def_copy__when__a__isa__ConstCharPtrWithSize;
extern MethodName_new_ptr_z::TM metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize;
extern MethodName_ptr_z::TM metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize;
extern MethodName_del::TM metil_def_del__when__a__has__Owcp_size_0__pert__1;
extern MethodName_del::TM metil_def_del__when__a__has__Owcp_size_1__pert__1;
extern MethodName_del::TM metil_def_del__when__a__has__Owcp_size_2__pert__1;
extern MethodName_del::TM metil_def_del__when__a__has__Owcp_size_3__pert__1;
extern MethodName_copy::TM metil_def_copy__when__a__has__Owcp_type__pert__1;
extern MethodName_self_append::TM metil_def_self_append__when__a__isa__VoidString__pert__100;
extern MethodName_self_append::TM metil_def_self_append__when__b__isa__VoidString__pert__101;


// reg_def
void reg_def() {
    static MethodCond_0_isa<TypeConstructor_File> cond_metil_def_del__when__a__isa__File;

    static const char *string_0 = "./src/TypeConstructor_File.cpp";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__isa__File;
    item_metil_def_del__when__a__isa__File.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__isa__File.cond = &cond_metil_def_del__when__a__isa__File;
    item_metil_def_del__when__a__isa__File.meth = metil_def_del__when__a__isa__File;
    item_metil_def_del__when__a__isa__File.file = string_0;
    item_metil_def_del__when__a__isa__File.line = 6;
    item_metil_def_del__when__a__isa__File.pert = 0;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__isa__File;

    static MethodCond_True cond_metil_def_self_append__pert_0;

    static const char *string_1 = "./src/TypeConstructor.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__pert_0.cond = &cond_metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.meth = metil_def_self_append__pert_0;
    item_metil_def_self_append__pert_0.file = string_1;
    item_metil_def_self_append__pert_0.line = 6;
    item_metil_def_self_append__pert_0.pert = 0;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__pert_0;

    static MethodFinder<MethodName_reassign>::Item item_metil_def_reassign__pert_0;
    item_metil_def_reassign__pert_0.prev = MethodFinder<MethodName_reassign>::last;
    item_metil_def_reassign__pert_0.cond = &cond_metil_def_self_append__pert_0;
    item_metil_def_reassign__pert_0.meth = metil_def_reassign__pert_0;
    item_metil_def_reassign__pert_0.file = string_1;
    item_metil_def_reassign__pert_0.line = 8;
    item_metil_def_reassign__pert_0.pert = 0;
    MethodFinder<MethodName_reassign>::last = &item_metil_def_reassign__pert_0;

    static MethodFinder<MethodName_add_parent>::Item item_metil_def_add_parent__pert_0;
    item_metil_def_add_parent__pert_0.prev = MethodFinder<MethodName_add_parent>::last;
    item_metil_def_add_parent__pert_0.cond = &cond_metil_def_self_append__pert_0;
    item_metil_def_add_parent__pert_0.meth = metil_def_add_parent__pert_0;
    item_metil_def_add_parent__pert_0.file = string_1;
    item_metil_def_add_parent__pert_0.line = 10;
    item_metil_def_add_parent__pert_0.pert = 0;
    MethodFinder<MethodName_add_parent>::last = &item_metil_def_add_parent__pert_0;

    static MethodFinder<MethodName_rem_parent>::Item item_metil_def_rem_parent__pert_0;
    item_metil_def_rem_parent__pert_0.prev = MethodFinder<MethodName_rem_parent>::last;
    item_metil_def_rem_parent__pert_0.cond = &cond_metil_def_self_append__pert_0;
    item_metil_def_rem_parent__pert_0.meth = metil_def_rem_parent__pert_0;
    item_metil_def_rem_parent__pert_0.file = string_1;
    item_metil_def_rem_parent__pert_0.line = 11;
    item_metil_def_rem_parent__pert_0.pert = 0;
    MethodFinder<MethodName_rem_parent>::last = &item_metil_def_rem_parent__pert_0;

    static MethodCond_0_is cond_metil_def_convert_to_SI32__when__a__is__Cst_zero;
    cond_metil_def_convert_to_SI32__when__a__is__Cst_zero.type = "Cst_zero";

    static const char *string_2 = "./src/TypeConstructor_Cst.cpp";

    static MethodFinder<MethodName_convert_to_SI32>::Item item_metil_def_convert_to_SI32__when__a__is__Cst_zero;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.prev = MethodFinder<MethodName_convert_to_SI32>::last;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.cond = &cond_metil_def_convert_to_SI32__when__a__is__Cst_zero;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.meth = metil_def_convert_to_SI32__when__a__is__Cst_zero;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.file = string_2;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.line = 5;
    item_metil_def_convert_to_SI32__when__a__is__Cst_zero.pert = 0;
    MethodFinder<MethodName_convert_to_SI32>::last = &item_metil_def_convert_to_SI32__when__a__is__Cst_zero;

    static MethodCond_0_isa<TypeConstructor_ConstCharPtr> cond_metil_def_copy__when__a__isa__ConstCharPtr;

    static const char *string_3 = "./src/TypeConstructor_ConstCharPtr.cpp";

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_copy__when__a__isa__ConstCharPtr.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__isa__ConstCharPtr.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_copy__when__a__isa__ConstCharPtr.meth = metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_copy__when__a__isa__ConstCharPtr.file = string_3;
    item_metil_def_copy__when__a__isa__ConstCharPtr.line = 9;
    item_metil_def_copy__when__a__isa__ConstCharPtr.pert = 0;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__isa__ConstCharPtr;

    static MethodFinder<MethodName_size>::Item item_metil_def_size__when__a__isa__ConstCharPtr;
    item_metil_def_size__when__a__isa__ConstCharPtr.prev = MethodFinder<MethodName_size>::last;
    item_metil_def_size__when__a__isa__ConstCharPtr.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_size__when__a__isa__ConstCharPtr.meth = metil_def_size__when__a__isa__ConstCharPtr;
    item_metil_def_size__when__a__isa__ConstCharPtr.file = string_3;
    item_metil_def_size__when__a__isa__ConstCharPtr.line = 11;
    item_metil_def_size__when__a__isa__ConstCharPtr.pert = 0;
    MethodFinder<MethodName_size>::last = &item_metil_def_size__when__a__isa__ConstCharPtr;

    static MethodFinder<MethodName_ptr_z>::Item item_metil_def_ptr_z__when__a__isa__ConstCharPtr;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.prev = MethodFinder<MethodName_ptr_z>::last;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.meth = metil_def_ptr_z__when__a__isa__ConstCharPtr;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.file = string_3;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.line = 13;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtr.pert = 0;
    MethodFinder<MethodName_ptr_z>::last = &item_metil_def_ptr_z__when__a__isa__ConstCharPtr;

    static MethodFinder<MethodName_new_ptr_z>::Item item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.prev = MethodFinder<MethodName_new_ptr_z>::last;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.meth = metil_def_new_ptr_z__when__a__isa__ConstCharPtr;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.file = string_3;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.line = 15;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr.pert = 0;
    MethodFinder<MethodName_new_ptr_z>::last = &item_metil_def_new_ptr_z__when__a__isa__ConstCharPtr;

    static MethodFinder<MethodName_copy_data>::Item item_metil_def_copy_data__when__a__isa__ConstCharPtr;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.prev = MethodFinder<MethodName_copy_data>::last;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.cond = &cond_metil_def_copy__when__a__isa__ConstCharPtr;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.meth = metil_def_copy_data__when__a__isa__ConstCharPtr;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.file = string_3;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.line = 17;
    item_metil_def_copy_data__when__a__isa__ConstCharPtr.pert = 0;
    MethodFinder<MethodName_copy_data>::last = &item_metil_def_copy_data__when__a__isa__ConstCharPtr;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_ConstCharPtr>,MethodCond_1_isa<TypeConstructor_ConstCharPtr> > cond_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;

    static MethodFinder<MethodName_equal>::Item item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_equal>::last;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.meth = metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.file = string_3;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.line = 19;
    item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_equal>::last = &item_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;

    static MethodFinder<MethodName_find>::Item item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_find>::last;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.meth = metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.file = string_3;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.line = 21;
    item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_find>::last = &item_metil_def_find__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_ConstCharPtr>,MethodCond_1_isa<TypeConstructor_Int> > cond_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;

    static MethodFinder<MethodName_end_from>::Item item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.prev = MethodFinder<MethodName_end_from>::last;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.cond = &cond_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.meth = metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.file = string_3;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.line = 25;
    item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.pert = 1;
    MethodFinder<MethodName_end_from>::last = &item_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;

    static MethodFinder<MethodName_beg_upto>::Item item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.prev = MethodFinder<MethodName_beg_upto>::last;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.cond = &cond_metil_def_end_from__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.meth = metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.file = string_3;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.line = 29;
    item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1.pert = 1;
    MethodFinder<MethodName_beg_upto>::last = &item_metil_def_beg_upto__when__a__isa__ConstCharPtr__and__b__isa__Int__pert__1;

    static MethodCond_0_isa<TypeConstructor_OwcpString> cond_metil_def_del__when__a__isa__OwcpString;

    static const char *string_4 = "./src/TypeConstructor_OwcpString.cpp";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_del__when__a__isa__OwcpString.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_del__when__a__isa__OwcpString.meth = metil_def_del__when__a__isa__OwcpString;
    item_metil_def_del__when__a__isa__OwcpString.file = string_4;
    item_metil_def_del__when__a__isa__OwcpString.line = 10;
    item_metil_def_del__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__isa__OwcpString;

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__isa__OwcpString;
    item_metil_def_copy__when__a__isa__OwcpString.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_copy__when__a__isa__OwcpString.meth = metil_def_copy__when__a__isa__OwcpString;
    item_metil_def_copy__when__a__isa__OwcpString.file = string_4;
    item_metil_def_copy__when__a__isa__OwcpString.line = 16;
    item_metil_def_copy__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__isa__OwcpString;

    static MethodFinder<MethodName_size>::Item item_metil_def_size__when__a__isa__OwcpString;
    item_metil_def_size__when__a__isa__OwcpString.prev = MethodFinder<MethodName_size>::last;
    item_metil_def_size__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_size__when__a__isa__OwcpString.meth = metil_def_size__when__a__isa__OwcpString;
    item_metil_def_size__when__a__isa__OwcpString.file = string_4;
    item_metil_def_size__when__a__isa__OwcpString.line = 21;
    item_metil_def_size__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_size>::last = &item_metil_def_size__when__a__isa__OwcpString;

    static MethodFinder<MethodName_ptr_z>::Item item_metil_def_ptr_z__when__a__isa__OwcpString;
    item_metil_def_ptr_z__when__a__isa__OwcpString.prev = MethodFinder<MethodName_ptr_z>::last;
    item_metil_def_ptr_z__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_ptr_z__when__a__isa__OwcpString.meth = metil_def_ptr_z__when__a__isa__OwcpString;
    item_metil_def_ptr_z__when__a__isa__OwcpString.file = string_4;
    item_metil_def_ptr_z__when__a__isa__OwcpString.line = 26;
    item_metil_def_ptr_z__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_ptr_z>::last = &item_metil_def_ptr_z__when__a__isa__OwcpString;

    static MethodFinder<MethodName_new_ptr_z>::Item item_metil_def_new_ptr_z__when__a__isa__OwcpString;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.prev = MethodFinder<MethodName_new_ptr_z>::last;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.meth = metil_def_new_ptr_z__when__a__isa__OwcpString;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.file = string_4;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.line = 31;
    item_metil_def_new_ptr_z__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_new_ptr_z>::last = &item_metil_def_new_ptr_z__when__a__isa__OwcpString;

    static MethodFinder<MethodName_copy_data>::Item item_metil_def_copy_data__when__a__isa__OwcpString;
    item_metil_def_copy_data__when__a__isa__OwcpString.prev = MethodFinder<MethodName_copy_data>::last;
    item_metil_def_copy_data__when__a__isa__OwcpString.cond = &cond_metil_def_del__when__a__isa__OwcpString;
    item_metil_def_copy_data__when__a__isa__OwcpString.meth = metil_def_copy_data__when__a__isa__OwcpString;
    item_metil_def_copy_data__when__a__isa__OwcpString.file = string_4;
    item_metil_def_copy_data__when__a__isa__OwcpString.line = 36;
    item_metil_def_copy_data__when__a__isa__OwcpString.pert = 0;
    MethodFinder<MethodName_copy_data>::last = &item_metil_def_copy_data__when__a__isa__OwcpString;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_OwcpString>,MethodCond_1_isa<TypeConstructor_ConstCharPtr> > cond_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;

    static MethodFinder<MethodName_find>::Item item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_find>::last;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.meth = metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.file = string_4;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.line = 41;
    item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_find>::last = &item_metil_def_find__when__a__isa__OwcpString__and__b__isa__ConstCharPtr__pert__1;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_OwcpString>,MethodCond_1_isa<TypeConstructor_Int> > cond_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;

    static MethodFinder<MethodName_beg_upto>::Item item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.prev = MethodFinder<MethodName_beg_upto>::last;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.cond = &cond_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.meth = metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.file = string_4;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.line = 46;
    item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1.pert = 1;
    MethodFinder<MethodName_beg_upto>::last = &item_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;

    static MethodFinder<MethodName_end_from>::Item item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.prev = MethodFinder<MethodName_end_from>::last;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.cond = &cond_metil_def_beg_upto__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.meth = metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.file = string_4;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.line = 53;
    item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1.pert = 1;
    MethodFinder<MethodName_end_from>::last = &item_metil_def_end_from__when__a__isa__OwcpString__and__b__isa__Int__pert__1;

    static MethodCond_0_isa<TypeConstructor_FileWithoutClose> cond_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;

    static const char *string_5 = "./src/TypeConstructor_FileWithoutClose.cpp";

    static MethodFinder<MethodName_flush>::Item item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.prev = MethodFinder<MethodName_flush>::last;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.cond = &cond_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.meth = metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.file = string_5;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.line = 12;
    item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1.pert = 1;
    MethodFinder<MethodName_flush>::last = &item_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;

    static MethodFinder<MethodName_write>::Item item_metil_def_write__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.prev = MethodFinder<MethodName_write>::last;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.cond = &cond_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.meth = metil_def_write__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.file = string_5;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.line = 15;
    item_metil_def_write__when__a__isa__FileWithoutClose__pert__1.pert = 1;
    MethodFinder<MethodName_write>::last = &item_metil_def_write__when__a__isa__FileWithoutClose__pert__1;

    static MethodFinder<MethodName_convert_to_Bool>::Item item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.prev = MethodFinder<MethodName_convert_to_Bool>::last;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.cond = &cond_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.meth = metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.file = string_5;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.line = 21;
    item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1.pert = 1;
    MethodFinder<MethodName_convert_to_Bool>::last = &item_metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_FileWithoutClose>,MethodCond_1_isa<TypeConstructor_ConstCharPtr> > cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.cond = &cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.meth = metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.file = string_5;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.line = 26;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_FileWithoutClose>,MethodCond_1_isa<TypeConstructor_OwcpString> > cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.cond = &cond_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.meth = metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.file = string_5;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.line = 33;
    item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1;

    static MethodCond_and<MethodCond_1_isa<TypeConstructor_ConstCharPtrWithSize>,MethodCond_0_isa<TypeConstructor_FileWithoutClose> > cond_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.cond = &cond_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.meth = metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.file = string_5;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.line = 39;
    item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1;

    static MethodFinder<MethodName_ptr_z>::Item item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.prev = MethodFinder<MethodName_ptr_z>::last;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.cond = &cond_metil_def_flush__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.meth = metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.file = string_5;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.line = 45;
    item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1.pert = 1;
    MethodFinder<MethodName_ptr_z>::last = &item_metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1;

    static MethodCond_0_is cond_metil_def_del__when__a__is__Int_s_64;
    cond_metil_def_del__when__a__is__Int_s_64.type = "Int_s_64";

    static const char *string_6 = "./src/TypeConstructor_Int.cpp";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_del__when__a__is__Int_s_64.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__is__Int_s_64.cond = &cond_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_del__when__a__is__Int_s_64.meth = metil_def_del__when__a__is__Int_s_64;
    item_metil_def_del__when__a__is__Int_s_64.file = string_6;
    item_metil_def_del__when__a__is__Int_s_64.line = 9;
    item_metil_def_del__when__a__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__is__Int_s_64;

    static MethodCond_0_is cond_metil_def_del__when__a__is__Int_s_32;
    cond_metil_def_del__when__a__is__Int_s_32.type = "Int_s_32";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_del__when__a__is__Int_s_32.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__is__Int_s_32.cond = &cond_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_del__when__a__is__Int_s_32.meth = metil_def_del__when__a__is__Int_s_32;
    item_metil_def_del__when__a__is__Int_s_32.file = string_6;
    item_metil_def_del__when__a__is__Int_s_32.line = 10;
    item_metil_def_del__when__a__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__is__Int_s_32;

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__is__Int_s_32;
    item_metil_def_copy__when__a__is__Int_s_32.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__is__Int_s_32.cond = &cond_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_copy__when__a__is__Int_s_32.meth = metil_def_copy__when__a__is__Int_s_32;
    item_metil_def_copy__when__a__is__Int_s_32.file = string_6;
    item_metil_def_copy__when__a__is__Int_s_32.line = 12;
    item_metil_def_copy__when__a__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__is__Int_s_32;

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__is__Int_s_64;
    item_metil_def_copy__when__a__is__Int_s_64.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__is__Int_s_64.cond = &cond_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_copy__when__a__is__Int_s_64.meth = metil_def_copy__when__a__is__Int_s_64;
    item_metil_def_copy__when__a__is__Int_s_64.file = string_6;
    item_metil_def_copy__when__a__is__Int_s_64.line = 13;
    item_metil_def_copy__when__a__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__is__Int_s_64;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_is > cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;
    cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.cond_1.type = "Int_s_64";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.cond = &cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.meth = metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.file = string_6;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.line = 15;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000.pert = 1000;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_64__pert__1000;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_is > cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;
    cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.cond_1.type = "Int_s_32";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.cond = &cond_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.meth = metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.file = string_6;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.line = 18;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000.pert = 1000;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__String__and__b__is__Int_s_32__pert__1000;

    static MethodFinder<MethodName_convert_to_Bool>::Item item_metil_def_convert_to_Bool__when__a__is__Int_s_64;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.prev = MethodFinder<MethodName_convert_to_Bool>::last;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.cond = &cond_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.meth = metil_def_convert_to_Bool__when__a__is__Int_s_64;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.file = string_6;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.line = 22;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_convert_to_Bool>::last = &item_metil_def_convert_to_Bool__when__a__is__Int_s_64;

    static MethodFinder<MethodName_convert_to_SI32>::Item item_metil_def_convert_to_SI32__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.prev = MethodFinder<MethodName_convert_to_SI32>::last;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.cond = &cond_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.meth = metil_def_convert_to_SI32__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.file = string_6;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.line = 23;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_convert_to_SI32>::last = &item_metil_def_convert_to_SI32__when__a__is__Int_s_64;

    static MethodFinder<MethodName_convert_to_SI64>::Item item_metil_def_convert_to_SI64__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.prev = MethodFinder<MethodName_convert_to_SI64>::last;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.cond = &cond_metil_def_del__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.meth = metil_def_convert_to_SI64__when__a__is__Int_s_64;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.file = string_6;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.line = 24;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_convert_to_SI64>::last = &item_metil_def_convert_to_SI64__when__a__is__Int_s_64;

    static MethodFinder<MethodName_convert_to_Bool>::Item item_metil_def_convert_to_Bool__when__a__is__Int_s_32;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.prev = MethodFinder<MethodName_convert_to_Bool>::last;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.cond = &cond_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.meth = metil_def_convert_to_Bool__when__a__is__Int_s_32;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.file = string_6;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.line = 26;
    item_metil_def_convert_to_Bool__when__a__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_convert_to_Bool>::last = &item_metil_def_convert_to_Bool__when__a__is__Int_s_32;

    static MethodFinder<MethodName_convert_to_SI32>::Item item_metil_def_convert_to_SI32__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.prev = MethodFinder<MethodName_convert_to_SI32>::last;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.cond = &cond_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.meth = metil_def_convert_to_SI32__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.file = string_6;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.line = 27;
    item_metil_def_convert_to_SI32__when__a__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_convert_to_SI32>::last = &item_metil_def_convert_to_SI32__when__a__is__Int_s_32;

    static MethodFinder<MethodName_convert_to_SI64>::Item item_metil_def_convert_to_SI64__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.prev = MethodFinder<MethodName_convert_to_SI64>::last;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.cond = &cond_metil_def_del__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.meth = metil_def_convert_to_SI64__when__a__is__Int_s_32;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.file = string_6;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.line = 28;
    item_metil_def_convert_to_SI64__when__a__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_convert_to_SI64>::last = &item_metil_def_convert_to_SI64__when__a__is__Int_s_32;

    static MethodCond_and<MethodCond_0_is,MethodCond_1_is > cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.cond_0.type = "Int_s_32";
    cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.cond_1.type = "Int_s_32";

    static MethodFinder<MethodName_add>::Item item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 36;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodCond_and<MethodCond_0_is,MethodCond_1_is > cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.cond_0.type = "Int_s_32";
    cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.cond_1.type = "Int_s_64";

    static MethodFinder<MethodName_add>::Item item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 36;
    item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodCond_and<MethodCond_0_is,MethodCond_1_is > cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.cond_0.type = "Int_s_64";
    cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.cond_1.type = "Int_s_32";

    static MethodFinder<MethodName_add>::Item item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 36;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodCond_and<MethodCond_0_is,MethodCond_1_is > cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.cond_0.type = "Int_s_64";
    cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.cond_1.type = "Int_s_64";

    static MethodFinder<MethodName_add>::Item item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_add>::last;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 36;
    item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_add>::last = &item_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_sub>::Item item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_sub>::last;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 37;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_sub>::last = &item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_sub>::Item item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_sub>::last;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 37;
    item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_sub>::last = &item_metil_def_sub__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_sub>::Item item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_sub>::last;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 37;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_sub>::last = &item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_sub>::Item item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_sub>::last;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 37;
    item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_sub>::last = &item_metil_def_sub__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_mul>::Item item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_mul>::last;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 38;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_mul>::last = &item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_mul>::Item item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_mul>::last;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 38;
    item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_mul>::last = &item_metil_def_mul__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_mul>::Item item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_mul>::last;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 38;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_mul>::last = &item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_mul>::Item item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_mul>::last;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 38;
    item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_mul>::last = &item_metil_def_mul__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_sup>::Item item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_sup>::last;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 40;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_sup>::last = &item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_sup>::Item item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_sup>::last;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 40;
    item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_sup>::last = &item_metil_def_sup__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_sup>::Item item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_sup>::last;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 40;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_sup>::last = &item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_sup>::Item item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_sup>::last;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 40;
    item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_sup>::last = &item_metil_def_sup__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_supeq>::Item item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_supeq>::last;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 41;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_supeq>::last = &item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_supeq>::Item item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_supeq>::last;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 41;
    item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_supeq>::last = &item_metil_def_supeq__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_supeq>::Item item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_supeq>::last;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 41;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_supeq>::last = &item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_supeq>::Item item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_supeq>::last;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 41;
    item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_supeq>::last = &item_metil_def_supeq__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_inf>::Item item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_inf>::last;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 42;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_inf>::last = &item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_inf>::Item item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_inf>::last;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 42;
    item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_inf>::last = &item_metil_def_inf__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_inf>::Item item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_inf>::last;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 42;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_inf>::last = &item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_inf>::Item item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_inf>::last;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 42;
    item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_inf>::last = &item_metil_def_inf__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_infeq>::Item item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_infeq>::last;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 43;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_infeq>::last = &item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_infeq>::Item item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_infeq>::last;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 43;
    item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_infeq>::last = &item_metil_def_infeq__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_infeq>::Item item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_infeq>::last;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 43;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_infeq>::last = &item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_infeq>::Item item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_infeq>::last;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 43;
    item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_infeq>::last = &item_metil_def_infeq__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_boolean_or>::Item item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_boolean_or>::last;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 45;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_boolean_or>::last = &item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_boolean_or>::Item item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_boolean_or>::last;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 45;
    item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_boolean_or>::last = &item_metil_def_boolean_or__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_boolean_or>::Item item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_boolean_or>::last;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 45;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_boolean_or>::last = &item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_boolean_or>::Item item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_boolean_or>::last;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 45;
    item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_boolean_or>::last = &item_metil_def_boolean_or__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodFinder<MethodName_boolean_and>::Item item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.prev = MethodFinder<MethodName_boolean_and>::last;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.meth = metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.file = string_6;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.line = 46;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_boolean_and>::last = &item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_32;

    static MethodFinder<MethodName_boolean_and>::Item item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.prev = MethodFinder<MethodName_boolean_and>::last;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.meth = metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.file = string_6;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.line = 46;
    item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_boolean_and>::last = &item_metil_def_boolean_and__when__a__is__Int_s_32__and__b__is__Int_s_64;

    static MethodFinder<MethodName_boolean_and>::Item item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.prev = MethodFinder<MethodName_boolean_and>::last;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.meth = metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.file = string_6;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.line = 46;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32.pert = 0;
    MethodFinder<MethodName_boolean_and>::last = &item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_32;

    static MethodFinder<MethodName_boolean_and>::Item item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.prev = MethodFinder<MethodName_boolean_and>::last;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.cond = &cond_metil_def_add__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.meth = metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.file = string_6;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.line = 46;
    item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64.pert = 0;
    MethodFinder<MethodName_boolean_and>::last = &item_metil_def_boolean_and__when__a__is__Int_s_64__and__b__is__Int_s_64;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_isa<TypeConstructor_String> > cond_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;

    static const char *string_7 = "./src/TypeConstructor_String.cpp";

    static MethodFinder<MethodName_append>::Item item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.prev = MethodFinder<MethodName_append>::last;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.cond = &cond_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.meth = metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.file = string_7;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.line = 8;
    item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0.pert = 0;
    MethodFinder<MethodName_append>::last = &item_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;

    static MethodFinder<MethodName_equal>::Item item_metil_def_equal__when__a__isa__String__and__b__isa__String;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.prev = MethodFinder<MethodName_equal>::last;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.cond = &cond_metil_def_append__when__a__isa__String__and__b__isa__String__pert_0;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.meth = metil_def_equal__when__a__isa__String__and__b__isa__String;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.file = string_7;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.line = 14;
    item_metil_def_equal__when__a__isa__String__and__b__isa__String.pert = 0;
    MethodFinder<MethodName_equal>::last = &item_metil_def_equal__when__a__isa__String__and__b__isa__String;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_is > cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;
    cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.cond_1.type = "Flt_64";

    static const char *string_8 = "./src/TypeConstructor_Flt.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.cond = &cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.meth = metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.file = string_8;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.line = 7;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000.pert = 1000;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_is > cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;
    cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.cond_1.type = "Flt_32";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.cond = &cond_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.meth = metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.file = string_8;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.line = 12;
    item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000.pert = 1000;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__String__and__b__is__Flt_32__pert__1000;

    static MethodCond_and<MethodCond_0_isa<TypeConstructor_String>,MethodCond_1_isa<TypeConstructor_StringConcat> > cond_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;

    static const char *string_9 = "./src/TypeConstructor_StringConcat.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.cond = &cond_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.meth = metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.file = string_9;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.line = 10;
    item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1.pert = 1;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1;

    static MethodCond_0_isa<TypeConstructor_StringConcat> cond_metil_def_size__when__a__isa__StringConcat;

    static MethodFinder<MethodName_size>::Item item_metil_def_size__when__a__isa__StringConcat;
    item_metil_def_size__when__a__isa__StringConcat.prev = MethodFinder<MethodName_size>::last;
    item_metil_def_size__when__a__isa__StringConcat.cond = &cond_metil_def_size__when__a__isa__StringConcat;
    item_metil_def_size__when__a__isa__StringConcat.meth = metil_def_size__when__a__isa__StringConcat;
    item_metil_def_size__when__a__isa__StringConcat.file = string_9;
    item_metil_def_size__when__a__isa__StringConcat.line = 15;
    item_metil_def_size__when__a__isa__StringConcat.pert = 0;
    MethodFinder<MethodName_size>::last = &item_metil_def_size__when__a__isa__StringConcat;

    static MethodFinder<MethodName_copy_data>::Item item_metil_def_copy_data__when__a__isa__StringConcat;
    item_metil_def_copy_data__when__a__isa__StringConcat.prev = MethodFinder<MethodName_copy_data>::last;
    item_metil_def_copy_data__when__a__isa__StringConcat.cond = &cond_metil_def_size__when__a__isa__StringConcat;
    item_metil_def_copy_data__when__a__isa__StringConcat.meth = metil_def_copy_data__when__a__isa__StringConcat;
    item_metil_def_copy_data__when__a__isa__StringConcat.file = string_9;
    item_metil_def_copy_data__when__a__isa__StringConcat.line = 23;
    item_metil_def_copy_data__when__a__isa__StringConcat.pert = 0;
    MethodFinder<MethodName_copy_data>::last = &item_metil_def_copy_data__when__a__isa__StringConcat;

    static MethodFinder<MethodName_ptr_z>::Item item_metil_def_ptr_z__when__a__isa__StringConcat;
    item_metil_def_ptr_z__when__a__isa__StringConcat.prev = MethodFinder<MethodName_ptr_z>::last;
    item_metil_def_ptr_z__when__a__isa__StringConcat.cond = &cond_metil_def_size__when__a__isa__StringConcat;
    item_metil_def_ptr_z__when__a__isa__StringConcat.meth = metil_def_ptr_z__when__a__isa__StringConcat;
    item_metil_def_ptr_z__when__a__isa__StringConcat.file = string_9;
    item_metil_def_ptr_z__when__a__isa__StringConcat.line = 32;
    item_metil_def_ptr_z__when__a__isa__StringConcat.pert = 0;
    MethodFinder<MethodName_ptr_z>::last = &item_metil_def_ptr_z__when__a__isa__StringConcat;

    static MethodFinder<MethodName_new_ptr_z>::Item item_metil_def_new_ptr_z__when__a__isa__StringConcat;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.prev = MethodFinder<MethodName_new_ptr_z>::last;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.cond = &cond_metil_def_size__when__a__isa__StringConcat;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.meth = metil_def_new_ptr_z__when__a__isa__StringConcat;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.file = string_9;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.line = 47;
    item_metil_def_new_ptr_z__when__a__isa__StringConcat.pert = 0;
    MethodFinder<MethodName_new_ptr_z>::last = &item_metil_def_new_ptr_z__when__a__isa__StringConcat;

    static MethodCond_0_isa<TypeConstructor_ConstCharPtrWithSize> cond_metil_def_del__when__a__isa__ConstCharPtrWithSize;

    static const char *string_10 = "./src/TypeConstructor_ConstCharPtrWithSize.cpp";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.cond = &cond_metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.meth = metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.file = string_10;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.line = 9;
    item_metil_def_del__when__a__isa__ConstCharPtrWithSize.pert = 0;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__isa__ConstCharPtrWithSize;

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.cond = &cond_metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.meth = metil_def_copy__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.file = string_10;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.line = 13;
    item_metil_def_copy__when__a__isa__ConstCharPtrWithSize.pert = 0;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__isa__ConstCharPtrWithSize;

    static MethodFinder<MethodName_new_ptr_z>::Item item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.prev = MethodFinder<MethodName_new_ptr_z>::last;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.cond = &cond_metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.meth = metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.file = string_10;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.line = 18;
    item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize.pert = 0;
    MethodFinder<MethodName_new_ptr_z>::last = &item_metil_def_new_ptr_z__when__a__isa__ConstCharPtrWithSize;

    static MethodFinder<MethodName_ptr_z>::Item item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.prev = MethodFinder<MethodName_ptr_z>::last;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.cond = &cond_metil_def_del__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.meth = metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.file = string_10;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.line = 23;
    item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize.pert = 0;
    MethodFinder<MethodName_ptr_z>::last = &item_metil_def_ptr_z__when__a__isa__ConstCharPtrWithSize;

    static TypeConstructor::C0_has_Owcp_size_0 cond_metil_def_del__when__a__has__Owcp_size_0__pert__1;

    static const char *string_11 = "./src/Owcp.cpp";

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__has__Owcp_size_0__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.cond = &cond_metil_def_del__when__a__has__Owcp_size_0__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.meth = metil_def_del__when__a__has__Owcp_size_0__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.file = string_11;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.line = 6;
    item_metil_def_del__when__a__has__Owcp_size_0__pert__1.pert = 1;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__has__Owcp_size_0__pert__1;

    static TypeConstructor::C0_has_Owcp_size_1 cond_metil_def_del__when__a__has__Owcp_size_1__pert__1;

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__has__Owcp_size_1__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.cond = &cond_metil_def_del__when__a__has__Owcp_size_1__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.meth = metil_def_del__when__a__has__Owcp_size_1__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.file = string_11;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.line = 12;
    item_metil_def_del__when__a__has__Owcp_size_1__pert__1.pert = 1;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__has__Owcp_size_1__pert__1;

    static TypeConstructor::C0_has_Owcp_size_2 cond_metil_def_del__when__a__has__Owcp_size_2__pert__1;

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__has__Owcp_size_2__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.cond = &cond_metil_def_del__when__a__has__Owcp_size_2__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.meth = metil_def_del__when__a__has__Owcp_size_2__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.file = string_11;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.line = 18;
    item_metil_def_del__when__a__has__Owcp_size_2__pert__1.pert = 1;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__has__Owcp_size_2__pert__1;

    static TypeConstructor::C0_has_Owcp_size_3 cond_metil_def_del__when__a__has__Owcp_size_3__pert__1;

    static MethodFinder<MethodName_del>::Item item_metil_def_del__when__a__has__Owcp_size_3__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.prev = MethodFinder<MethodName_del>::last;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.cond = &cond_metil_def_del__when__a__has__Owcp_size_3__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.meth = metil_def_del__when__a__has__Owcp_size_3__pert__1;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.file = string_11;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.line = 24;
    item_metil_def_del__when__a__has__Owcp_size_3__pert__1.pert = 1;
    MethodFinder<MethodName_del>::last = &item_metil_def_del__when__a__has__Owcp_size_3__pert__1;

    static TypeConstructor::C0_has_Owcp_type cond_metil_def_copy__when__a__has__Owcp_type__pert__1;

    static MethodFinder<MethodName_copy>::Item item_metil_def_copy__when__a__has__Owcp_type__pert__1;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.prev = MethodFinder<MethodName_copy>::last;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.cond = &cond_metil_def_copy__when__a__has__Owcp_type__pert__1;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.meth = metil_def_copy__when__a__has__Owcp_type__pert__1;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.file = string_11;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.line = 30;
    item_metil_def_copy__when__a__has__Owcp_type__pert__1.pert = 1;
    MethodFinder<MethodName_copy>::last = &item_metil_def_copy__when__a__has__Owcp_type__pert__1;

    static MethodCond_0_isa<TypeConstructor_VoidString> cond_metil_def_self_append__when__a__isa__VoidString__pert__100;

    static const char *string_12 = "./src/TypeConstructor_VoidString.cpp";

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__a__isa__VoidString__pert__100;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.cond = &cond_metil_def_self_append__when__a__isa__VoidString__pert__100;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.meth = metil_def_self_append__when__a__isa__VoidString__pert__100;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.file = string_12;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.line = 6;
    item_metil_def_self_append__when__a__isa__VoidString__pert__100.pert = 100;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__a__isa__VoidString__pert__100;

    static MethodCond_1_isa<TypeConstructor_VoidString> cond_metil_def_self_append__when__b__isa__VoidString__pert__101;

    static MethodFinder<MethodName_self_append>::Item item_metil_def_self_append__when__b__isa__VoidString__pert__101;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.prev = MethodFinder<MethodName_self_append>::last;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.cond = &cond_metil_def_self_append__when__b__isa__VoidString__pert__101;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.meth = metil_def_self_append__when__b__isa__VoidString__pert__101;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.file = string_12;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.line = 7;
    item_metil_def_self_append__when__b__isa__VoidString__pert__101.pert = 101;
    MethodFinder<MethodName_self_append>::last = &item_metil_def_self_append__when__b__isa__VoidString__pert__101;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // AVOID_GEN
