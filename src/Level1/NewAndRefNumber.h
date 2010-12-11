#ifndef NEWANDREFNUMBER_H
#define NEWANDREFNUMBER_H

#include "Type.h"
#include "../S.h"

BEG_METIL_LEVEL1_NAMESPACE;

#define DECL_REF_AND_NEW( T, M, SI ) \
    inline MO NEW_Number( T  v ) { return MO( NEW( T, v ), &Level1::metil_type_bas_##M ); } \
    inline MO REF_Number( T &v ) { return MO(        &v  , &Level1::metil_type_ref_##M ); } \
    inline MO REF_Vec( Number<1>, T *v ) { return MO( v, &Level1::metil_type_cst_Array_##SI##M##_1_1_1 ); } \
    inline MO REF_Vec( Number<2>, T *v ) { return MO( v, &Level1::metil_type_cst_Array_##SI##M##_1_2_2 ); } \
    inline MO REF_Vec( Number<3>, T *v ) { return MO( v, &Level1::metil_type_cst_Array_##SI##M##_1_3_3 ); } \
    inline MO REF_Vec( Number<4>, T *v ) { return MO( v, &Level1::metil_type_cst_Array_##SI##M##_1_4_4 ); } \
    inline Type *type_ptr( S<T> ) { return &Level1::metil_type_bas_##M; }

DECL_REF_AND_NEW( SI8 , Int_s_8 , 7 );
DECL_REF_AND_NEW( SI16, Int_s_16, 8 );
DECL_REF_AND_NEW( SI32, Int_s_32, 8 );
DECL_REF_AND_NEW( SI64, Int_s_64, 8 );

DECL_REF_AND_NEW( PI8 , Int_p_8 , 7 );
DECL_REF_AND_NEW( PI16, Int_p_16, 8 );
DECL_REF_AND_NEW( PI32, Int_p_32, 8 );
DECL_REF_AND_NEW( PI64, Int_p_64, 8 );

DECL_REF_AND_NEW( NI8 , Int_n_8 , 7 );
DECL_REF_AND_NEW( NI16, Int_n_16, 8 );
DECL_REF_AND_NEW( NI32, Int_n_32, 8 );
DECL_REF_AND_NEW( NI64, Int_n_64, 8 );

DECL_REF_AND_NEW( FP32, Flt_0_23_23_8_31_1_127   , 22 );
DECL_REF_AND_NEW( FP64, Flt_0_52_52_11_63_1_1023 , 24 );
DECL_REF_AND_NEW( FP80, Flt_0_64_64_15_79_1_16383, 25 );

#undef DECL_REF_AND_NEW

inline MO NEW_Number( bool v ) { return v ? &metil_type_cst_Cst_1 : &metil_type_cst_Cst_0; }

template<class T>
MO REF_Vec( ST s, T *v ) {
    if ( s == 1 ) return REF_Vec( Number<1>(), v );
    if ( s == 2 ) return REF_Vec( Number<2>(), v );
    if ( s == 3 ) return REF_Vec( Number<3>(), v );
    if ( s == 4 ) return REF_Vec( Number<4>(), v );
    ERROR( "... s=%i", s );
    return 0;
}

END_METIL_LEVEL1_NAMESPACE;

BEG_METIL_NAMESPACE;

template<class T> Level1::Type *type_ptr() { return Level1::type_ptr( S<T>() ); }

END_METIL_NAMESPACE;

#endif // NEWANDREFNUMBER_H
