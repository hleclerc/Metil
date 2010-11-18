#include "ValReader.h"
#include "Val.h"

BEG_METIL_NAMESPACE;

Val::Val( const String &str ) {
    BasicVec<String> sym;
    Level1::ValReader reader( str, sym );
    type = reader.res.type;
    data = reader.res.data;
    reader.res.type = &Level1::metil_type_cst_Cst_0; // to avoid del of the result
}

Val::Val( const char *str ) {
    new( this ) Val( String( str ) );
}


//static SI32 data_one_half   [] = { 1, 2 };
//static SI32 data_one_quarter[] = { 1, 4 };
//static PI32 zero_PI32 = 0;
//static PI32 one_PI32 = 1;
//
Val zero             ( Level1::MO( &Level1::metil_type_cst_Cst_0   ) );
Val one              ( Level1::MO( &Level1::metil_type_cst_Cst_1   ) );
Val two              ( Level1::MO( &Level1::metil_type_cst_Cst_2   ) );
Val three            ( Level1::MO( &Level1::metil_type_cst_Cst_3   ) );
Val four             ( Level1::MO( &Level1::metil_type_cst_Cst_4   ) );
Val five             ( Level1::MO( &Level1::metil_type_cst_Cst_5   ) );
Val minus_one        ( Level1::MO( &Level1::metil_type_cst_Cst_m_1 ) );
Val pi               ( Level1::MO( &Level1::metil_type_cst_Cst_pi  ) );
Val i                ( Level1::MO( &Level1::metil_type_cst_Cst_i   ) );
Val inf              ( Level1::MO( &Level1::metil_type_cst_Cst_inf ) );
Val exp_1            ( Level1::MO( &Level1::metil_type_cst_Cst_exp ) );
Val nan              ( Level1::MO( &Level1::metil_type_cst_Cst_nan ) );

Val one_half         ( Level1::MO( &Level1::metil_type_cst_Cst_1_2   ) );
Val minus_one_half   ( Level1::MO( &Level1::metil_type_cst_Cst_m_1_2 ) );
Val one_quarter      ( Level1::MO( &Level1::metil_type_cst_Cst_1_4   ) );
Val minus_one_quarter( Level1::MO( &Level1::metil_type_cst_Cst_m_1_4 ) );
//Val zero_as_PI32     ( Level1::MO( &zero_PI32       , &Level1::type_PI32_Ref ) );
//Val one_as_PI32      ( Level1::MO( &one_PI32        , &Level1::type_PI32_Ref ) );
//Val minus_one_as_NI32( Level1::MO( &one_PI32        , &Level1::type_NI32_Ref ) );

END_METIL_NAMESPACE
