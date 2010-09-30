// basic methods
#ifndef DONT_WANT_UNARY_BASIC
DECL_MET( GC_ST  , size_in_mem             ); // size occupied in memory by the data
#ifndef AVOID_DEL
DECL_MET( VO     , del                     ); // call destroy and free
#endif // AVOID_DEL
DECL_MET( VO     , free                    ); // free memory used by object
DECL_MET( VO     , destroy                 ); // call destructor
#ifndef AVOID_COPY
DECL_MET( OC     , copy                    ); // make a copy of self
#endif // AVOID_COPY
DECL_MET( OC     , copy_ref                ); // make a copy of a data reference @see RefOn
#endif // DONT_WANT_UNARY_BASIC

DECL_MET( VCG_Str, write_str               ); // string or file output
DECL_MET( VCG_Str, write_dot               ); // string or file output
DECL_MET( VCG_Str, write_tex               ); // string or file output

DECL_MET( VOG_Str, read_str                ); // string or file input

DECL_MET( VO     , flush                   ); //
DECL_MET( VOGG_CS, write                   ); // a.write( ptr, size )
DECL_MET( VCGG_PS, read                    ); // a.read ( ptr, size )

// vector
DECL_MET( OC     , size                    ); // size of data (nb items). Returns a scalar
DECL_MET( OC     , sizes                   ); // size of data (nb items / axes). Returns a vector

// string
DECL_MET( GO_vptr, ptr                     ); // return a ptr on data
DECL_MET( GO_vptr, ptr_z                   ); // return a ptr on data with a zero at the end (usefull for c_str)
DECL_MET( GC_vptr, new_ptr                 ); // return a new ptr on copy of data
DECL_MET( GC_vptr, new_ptr_z               ); // return a new ptr on copy of data with a zero at the end (usefull for c_str)
// DECL_MET( TOT       , copy_in                 ); // copy data to ptr given as argument and return ptr + room for the data

// arithmetic, unary
#ifndef DONT_WANT_UNARY_ARITHMETIC
#include "DeclMethodsUnaryArithmetic.h"
#endif // DONT_WANT_UNARY_ARITHMETIC

// conversions
DECL_MET( GC_bool, convert_to_Bool         ); // operator bool
DECL_MET( GC_SI32, convert_to_SI32         ); // operator SI32
DECL_MET( GC_SI64, convert_to_SI64         ); // operator SI64
DECL_MET( GC_FP32, convert_to_FP32         ); // operator FP32
DECL_MET( GC_FP64, convert_to_FP64         ); // operator FP64
DECL_MET( GC_FP80, convert_to_FP80         ); // operator FP80

DECL_MET( GC_bool, ok                      ); //

// display
DECL_MET( GC_FP64, priority                ); // + -> 10, * -> 20, ...


//// graph and lazy evaluation
//DECL_MET( GC<ST>              , nb_children   ); // return -1 if not an Owcp
//DECL_MET( GO<MetilException *>, exec_node     ); // exec_node
//DECL_MET( OCS                 , get_child     ); //
//DECL_MET( VOY                 , add_parent    ); // add_parent( OwcpChild )
//DECL_MET( VOY                 , rem_parent    ); // rem_parent( OwcpChild )
//DECL_MET( YC                  , get_parent    ); // get_parent
//DECL_MET( GC<MO *>            , get_op_mp     ); // return op_mp if an Owcp, 0 if not
//DECL_MET( GC<bool>            , cur_op_id     ); //
