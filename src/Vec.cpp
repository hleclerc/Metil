#include "Level1/ArrayHeader.h"
#include "Array.h"

BEG_METIL_NAMESPACE;

Vec::Vec() {
    type = &Level1::metil_type_cst_Array_4NULL_1_0_0;
}

Vec::Vec( const Val &v_0 ) {
    Level1::MO *vec = ALLOC_STATIC_VEC( Level1::MO, 1 );
    type = &Level1::metil_type_bas_Array_4NULL_1_1_1;
    data = vec;
    vec[ 0 ] = CM_1( copy, v_0 );
}

Vec::Vec( const Val &v_0, const Val &v_1 ) {
    Level1::MO *vec = ALLOC_STATIC_VEC( Level1::MO, 2 );
    type = &Level1::metil_type_bas_Array_4NULL_1_2_2;
    data = vec;
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2 ) {
    Level1::MO *vec = ALLOC_STATIC_VEC( Level1::MO, 3 );
    type = &Level1::metil_type_bas_Array_4NULL_1_3_3;
    data = vec;
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3 ) {
    Level1::MO *vec = ALLOC_STATIC_VEC( Level1::MO, 4 );
    type = &Level1::metil_type_bas_Array_4NULL_1_4_4;
    data = vec;
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
    vec[ 3 ] = CM_1( copy, v_3 );
}

Vec::Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3, const Val &v_4 ) {
    Level1::MO *vec = ALLOC_STATIC_VEC( Level1::MO, 5 );
    type = &Level1::metil_type_bas_Array_4NULL_1_5_5;
    data = vec;
    vec[ 0 ] = CM_1( copy, v_0 );
    vec[ 1 ] = CM_1( copy, v_1 );
    vec[ 2 ] = CM_1( copy, v_2 );
    vec[ 3 ] = CM_1( copy, v_3 );
    vec[ 4 ] = CM_1( copy, v_4 );
}

Vec::Vec( Size, ST size ) {
    type = &Level1::metil_type_bas_Array_4NULL_1_m_m_CptUse;
    CM_2( allocate, *this, Level1::REF_Number( size ) );
    CM_2( init_arg, *this, Level1::MO( &Level1::metil_type_cst_Cst_0 ) );
}

Vec::Vec( Size, ST size, Level1::Type *item_type, const MachineId */*machine_id*/ ) {
    type = item_type;
    CM_2( allocate_array, *this, Level1::REF_Number( size ) );
}

END_METIL_NAMESPACE;
