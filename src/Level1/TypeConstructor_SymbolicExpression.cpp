#include "TypeConstructor_SymbolicExpression.h"

BEG_METIL_LEVEL1_NAMESPACE;

void tmp_bootstrap() {
    metil_type_bas_Op_Add.init_if_necessary();
}

void metil_gen_add__when__a__isa__SymbolicExpression__or__b__isa__SymbolicExpression__pert__2( MethodWriter &mw, const Mos *args, const String &ret ) {
    mw.n << "Type *type = &metil_type_bas_Op_Add;";
    mw.n << ret << "MO( NEW( Owcp<2>, type, " << args[ 0 ] << ", " << args[ 1 ] << " ), type );";
}

void TypeConstructor_SymbolicExpression::default_mw( MethodWriter &mw ) const {
    TypeConstructor::default_mw( mw );
    mw.add_include( "Level1/Owcp.h" );
}

END_METIL_LEVEL1_NAMESPACE;
