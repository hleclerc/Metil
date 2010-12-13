#include "Level1/SymbolHeader.h"
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

Val Val::read_from_type_name( const char *&name ) {
    String op = String::read_sized( name );
    if ( op == "equal" ) {
        Val a = read_from_type_name( ++name );
        Val b = read_from_type_name( ++name );
        return a == b;
    } else if ( op == "_0" ) {
        return _0;
    } else if ( op == "_1" ) {
        return _1;
    } else if ( op == "_2" ) {
        return _2;
    } else {
        ERROR( "unknown op %s", op.c_str() );
    }
    return zero;
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

static Level1::SymbolHeader s_0( "_0", "f_0" );
static Level1::SymbolHeader s_1( "_1", "f_1" );
static Level1::SymbolHeader s_2( "_2", "f_2" );

Val _0( Level1::MO( &s_0, &Level1::metil_type_cst_Symbol ) );
Val _1( Level1::MO( &s_1, &Level1::metil_type_cst_Symbol ) );
Val _2( Level1::MO( &s_2, &Level1::metil_type_cst_Symbol ) );

END_METIL_NAMESPACE
