// arithmetic, binary
#include "DeclMethodsBinaryArithmetic.h"

// base
DECL_MET( VOC       , reassign                ); // =

// arithmetic, self binary
DECL_MET( VOC       , self_add                ); // +=
DECL_MET( VOC       , self_sub                ); // -=
DECL_MET( VOC       , self_mul                ); // *=
DECL_MET( VOC       , self_div                ); // /=
DECL_MET( VOC       , self_quo                ); // //=
DECL_MET( VOC       , self_mod                ); // %=
DECL_MET( VOC       , self_pow                ); // ^=

DECL_MET( VOC       , reassign_inplace        ); // =, but try to keep type

// arithmetic, self binary
DECL_MET( VOC       , self_add_inplace        ); // +=
DECL_MET( VOC       , self_sub_inplace        ); // -=
DECL_MET( VOC       , self_mul_inplace        ); // *=
DECL_MET( VOC       , self_div_inplace        ); // /=
DECL_MET( VOC       , self_quo_inplace        ); // //=
DECL_MET( VOC       , self_mod_inplace        ); // %=
DECL_MET( VOC       , self_pow_inplace        ); // ^=

// stream
DECL_MET( VOC       , set_ok                  ); //
DECL_MET( VOC       , rewind                  ); //


// vector
DECL_MET( OOC       , select                  ); // obj[ Val index ]
DECL_MET( OCC       , select_C                ); // obj[ Val index ]

//DECL_MET( OCC       , left_to                 ); //
//DECL_MET( OCC       , right_from              ); //

DECL_MET( VOC       , self_append             ); // add a list to self
DECL_MET( VOC       , self_push_back          ); // add an element to self

DECL_MET( OCC       , append                  ); // add a list to a list
DECL_MET( OCC       , push_back               ); // add an element to an element

DECL_MET( OCC       , find                    ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OCC       , rfind                   ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OCC       , ends_with               ); // return true obj_0 (list, string, ...) ends with obj_1
DECL_MET( OCC       , begs_with               ); // return true obj_0 (list, string, ...) begins with obj_1
DECL_MET( OCC       , left_to                 ); // "abcd".left_to   (1) -> "a"
DECL_MET( OCC       , right_from              ); // "abcd".right_from(1) -> "bcd"

DECL_MET( BCC       , always_equal            ); //
