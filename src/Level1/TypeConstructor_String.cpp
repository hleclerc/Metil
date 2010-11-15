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
MO metil_def_equal__when__a__isa__String__and__b__isa__String( MO a, MO b ) { // TODO: optimize !
    char *sa = (char *)CM_1( new_ptr_z, a );
    char *sb = (char *)CM_1( new_ptr_z, b );
    MO res = NEW_Number( equal( sa, sb ) );
    std::free( sa );
    std::free( sb );
    return res;
}

// String < String
MO metil_def_inf__when__a__isa__String__and__b__isa__String( MO a, MO b ) { // TODO: optimize !
    char *sa = (char *)CM_1( new_ptr_z, a );
    char *sb = (char *)CM_1( new_ptr_z, b );
    MO res = NEW_Number( strcmp( sa, sb ) < 0 );
    std::free( sa );
    std::free( sb );
    return res;
}

//
bool metil_def_convert_to_Bool__when__a__isa__String( MO a ) {
    return Val( CM_1( size, a ) );
}

//
MO metil_def_rfind__when__a__isa__String__and__b__isa__String( MO a, MO b ) {
    char *sa = (char *)CM_1( new_ptr_z, a );
    char *sb = (char *)CM_1( new_ptr_z, b );
    MO res = NEW_Number( rfind( sa, sb ) );
    std::free( sa );
    std::free( sb );
    return res;
}

//
MO metil_def_find__when__a__isa__String__and__b__isa__String( MO a, MO b ) {
    char *sa = (char *)CM_1( new_ptr_z, a );
    char *sb = (char *)CM_1( new_ptr_z, b );
    MO res = NEW_Number( find( sa, sb ) );
    std::free( sa );
    std::free( sb );
    return res;
}

//
MO metil_def_end_from__when__a__isa__String__and__b__isa__Int( MO a, MO b ) {
    char *sa = (char *)CM_1( new_ptr_z, a );
    SI32 sb = CM_1( convert_to_SI32, b );
    NewString res( sa + sb );
    std::free( sa );
    return MO( res.data, &Level1::metil_type_bas_OwcpString );
}

//
MO metil_def_beg_upto__when__a__isa__String__and__b__isa__Int( MO a, MO b ) {
    char *sa = (char *)CM_1( new_ptr_z, a );
    SI32 sb = CM_1( convert_to_SI32, b );
    NewString res( sa, sa + sb );
    std::free( sa );
    return MO( res.data, &Level1::metil_type_bas_OwcpString );
}

END_METIL_LEVEL1_NAMESPACE;
