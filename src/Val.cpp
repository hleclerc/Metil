#include "ValReader.h"
#include "Val.h"

BEG_METIL_NAMESPACE;

Val::Val( const String &str ) {
    BasicVec<String> sym;
    Level1::ValReader reader( str, sym );
    type = reader.res.type;
    data = reader.res.data;
    reader.res.type = &Level1::metil_type_cst_Cst__zero;
}

Val::Val( const char *str ) {
    new( this ) Val( String( str ) );
}


//static SI32 data_one_half   [] = { 1, 2 };
//static SI32 data_one_quarter[] = { 1, 4 };
//static PI32 zero_PI32 = 0;
//static PI32 one_PI32 = 1;
//
//Val zero             ( Level1::MO( &Level1::type_Zero     ) );
//Val one              ( Level1::MO( &Level1::type_One      ) );
//Val minus_one        ( Level1::MO( &Level1::type_MinusOne ) );
//Val pi               ( Level1::MO( &Level1::type_Pi       ) );
//Val i                ( Level1::MO( &Level1::type_I        ) );
//Val inf              ( Level1::MO( &Level1::type_Inf      ) );
//Val exp_1            ( Level1::MO( &Level1::type_Exp_1    ) );
//Val nan              ( Level1::MO( &Level1::type_Nan      ) );
//Val one_half         ( Level1::MO( data_one_half    , Level1::type_PR( 32, 32, 0, 1 ) ) );
//Val minus_one_half   ( Level1::MO( data_one_half    , Level1::type_NR( 32, 32, 0, 1 ) ) );
//Val one_quarter      ( Level1::MO( data_one_quarter , Level1::type_PR( 32, 32, 0, 1 ) ) );
//Val minus_one_quarter( Level1::MO( data_one_quarter , Level1::type_NR( 32, 32, 0, 1 ) ) );
//Val two              ( Level1::MO( data_one_half + 1, &Level1::type_PI32_Ref ) );
//Val zero_as_PI32     ( Level1::MO( &zero_PI32       , &Level1::type_PI32_Ref ) );
//Val one_as_PI32      ( Level1::MO( &one_PI32        , &Level1::type_PI32_Ref ) );
//Val minus_one_as_NI32( Level1::MO( &one_PI32        , &Level1::type_NI32_Ref ) );
//#endif

END_METIL_NAMESPACE
