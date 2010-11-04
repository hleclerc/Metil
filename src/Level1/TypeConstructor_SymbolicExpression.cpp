#include "TypeConstructor_SymbolicExpression.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_add__when__a__isa__SymbolicExpression__and__b__isa__SymbolicExpression__pert__2( MethodWriter &mw, const Mos *args, const String &ret ) {
    mw.add_include( "Level1/Owcp.h" );
    mw.n << "Type *type = &metil_type_bas_Op_Add;";
    mw.n << ret << "MO( NEW( Owcp<2>, type, " << args[ 0 ] << ", " << args[ 1 ] << " ), type );";
}

END_METIL_LEVEL1_NAMESPACE;
