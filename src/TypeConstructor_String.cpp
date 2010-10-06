#include "TypeConstructor_StringConcat.h"
#include "NewAndRefNumber.h"
#include "StringHelp.h"

BEG_METIL_LEVEL1_NAMESPACE;

// append( String, String )
MO metil_def_append__when__a__isa__String__and__b__isa__String__pert_0( MO a, MO b ) {
    Owcp<2> *res = NEW( Owcp<2>, &metil_type_bas_StringConcat, a, b );
    return MO( res, &metil_type_bas_StringConcat );
}

// String == String
MO metil_def_equal__when__a__isa__String__and__b__isa__String( MO a, MO b ) { // TODO: optimize
    char *sa = (char *)CM_1( new_ptr_z, a );
    char *sb = (char *)CM_1( new_ptr_z, b );
    MO res = NEW_Number( equal( sa, sb ) );
    std::free( sa );
    std::free( sb );
    return res;
}

END_METIL_LEVEL1_NAMESPACE;
