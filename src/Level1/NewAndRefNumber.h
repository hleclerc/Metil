#ifndef NEWANDREFNUMBER_H
#define NEWANDREFNUMBER_H

#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

#define DECL_REF_AND_NEW( T, M ) \
    inline MO NEW_Number( T  v ) { return MO( NEW( T, v ), &Level1::metil_type_bas_##M ); } \
    inline MO REF_Number( T &v ) { return MO(        &v  , &Level1::metil_type_ref_##M ); }

DECL_REF_AND_NEW( SI8 , Int_s_8  );
DECL_REF_AND_NEW( SI16, Int_s_16 );
DECL_REF_AND_NEW( SI32, Int_s_32 );
DECL_REF_AND_NEW( SI64, Int_s_64 );

DECL_REF_AND_NEW( PI8 , Int_p_8  );
DECL_REF_AND_NEW( PI16, Int_p_16 );
DECL_REF_AND_NEW( PI32, Int_p_32 );
DECL_REF_AND_NEW( PI64, Int_p_64 );

DECL_REF_AND_NEW( NI8 , Int_n_8  );
DECL_REF_AND_NEW( NI16, Int_n_16 );
DECL_REF_AND_NEW( NI32, Int_n_32 );
DECL_REF_AND_NEW( NI64, Int_n_64 );

DECL_REF_AND_NEW( FP32, Flt_32 );
DECL_REF_AND_NEW( FP64, Flt_64 );
DECL_REF_AND_NEW( FP80, Flt_80 );

#undef DECL_REF_AND_NEW


END_METIL_LEVEL1_NAMESPACE;

#endif // NEWANDREFNUMBER_H
