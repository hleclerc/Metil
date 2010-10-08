// arithmetic, binary
#include "DeclMethodsBinaryArithmetic.h"

// base
DECL_MET( VoO       , reassign                ); // =

// arithmetic, self binary
DECL_MET( VoO       , self_add                ); // +=
DECL_MET( VoO       , self_sub                ); // -=
DECL_MET( VoO       , self_mul                ); // *=
DECL_MET( VoO       , self_div                ); // /=
DECL_MET( VoO       , self_quo                ); // //=
DECL_MET( VoO       , self_mod                ); // %=
DECL_MET( VoO       , self_pow                ); // ^=

DECL_MET( VoO       , reassign_inplace        ); // =, but try to keep type

// arithmetic, self binary
DECL_MET( VoO       , self_add_inplace        ); // +=
DECL_MET( VoO       , self_sub_inplace        ); // -=
DECL_MET( VoO       , self_mul_inplace        ); // *=
DECL_MET( VoO       , self_div_inplace        ); // /=
DECL_MET( VoO       , self_quo_inplace        ); // //=
DECL_MET( VoO       , self_mod_inplace        ); // %=
DECL_MET( VoO       , self_pow_inplace        ); // ^=

// stream
DECL_MET( VoO       , set_ok                  ); //
DECL_MET( VoO       , rewind                  ); //


// vector
DECL_MET( OoO       , select                  ); // obj[ Val index ]
DECL_MET( OOO       , select_C                ); // obj[ Val index ]

DECL_MET( VoO       , self_append             ); // add a list to self
DECL_MET( VoO       , self_push_back          ); // add an element to self

DECL_MET( OOO       , append                  ); // add a list to a list
DECL_MET( OOO       , push_back               ); // add an element to an element

DECL_MET( OOO       , find                    ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OOO       , rfind                   ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OOO       , ends_with               ); // return true obj_0 (list, string, ...) ends with obj_1
DECL_MET( OOO       , begs_with               ); // return true obj_0 (list, string, ...) begins with obj_1
DECL_MET( OOO       , beg_upto                ); // "abcd".beg_upto( 1 ) -> "a"
DECL_MET( OOO       , end_from                ); // "abcd".end_from( 1 ) -> "bcd"

DECL_MET( BOO       , always_equal            ); //
