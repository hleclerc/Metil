// arithmetic, binary
#include "DeclMethodsBinaryArithmetic.h"
#include "DeclMethodsBinarySelfOp.h"
#include "DeclMethodsBinarySelfOpInplace.h"

//
DECL_MET( PoO, allocate       ); // allocate( array with type defined but data, size or other kind of argument ). If size is
// DECL_MET( poO, allocate_vec   ); // allocate a vector of type a->type and size defined by b. returns a pointer on data.
DECL_MET( VoO, init_arg       ); // obj->init( arg )

// stream
DECL_MET( VoO, set_ok         ); //
DECL_MET( VoO, rewind         ); //


// vector
DECL_MET( OoO, select         ); // obj[ Val index ]
DECL_MET( OOO, select_C       ); // obj[ Val index ]

DECL_MET( VoO, self_append    ); // add a list to self
DECL_MET( VoO, self_push_back ); // add an element to self

DECL_MET( OOO, append         ); // add a list to a list
DECL_MET( OOO, push_back      ); // add an element to an element

DECL_MET( OOO, find           ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OOO, rfind          ); // index in obj_0 of first sub-part equal to obj_1
DECL_MET( OOO, ends_with      ); // return true obj_0 (list, string, ...) ends with obj_1
DECL_MET( OOO, begs_with      ); // return true obj_0 (list, string, ...) begins with obj_1
DECL_MET( OOO, beg_upto       ); // "abcd".beg_upto( 1 ) -> "a"
DECL_MET( OOO, end_from       ); // "abcd".end_from( 1 ) -> "bcd"

DECL_MET( BOO, always_equal   ); //

DECL_MET( VoO, set_values     ); // obj[ ... ] = val

DECL_MET( VOO, call_C         ); // used e.g. functor objects
