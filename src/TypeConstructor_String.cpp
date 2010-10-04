#include "TypeConstructor_StringConcat.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_append__when__a__isa__String__and__b__isa__String__pert_0( MO a, MO b ) {
    Owcp<2> *res = NEW( Owcp<2>, &metil_type_bas_StringConcat, a, b );
    return MO( res, &metil_type_bas_StringConcat );
}

END_METIL_LEVEL1_NAMESPACE;
