#include "TypeConstructor_Symbol.h"

BEG_METIL_LEVEL1_NAMESPACE;

//
void metil_gen_del__when__a__isa__Symbol__pert__2( MethodWriter &mw ) {
    mw.n << "SymbolHeader *o = reinterpret_cast<SymbolHeader *>( " << mw.arg[ 0 ].data << " );";
    mw.n << "if ( --o->cpt_use < 0 ) DEL( o );";
}

void TypeConstructor_Symbol::write_write_str( MethodWriter &mw ) const {
    mw.n << "os << reinterpret_cast<SymbolHeader *>( " << mw.arg[ 0 ].data << " )->data.cpp;";
}

void TypeConstructor_Symbol::default_mw( MethodWriter &mw ) const {
    TypeConstructor_SymbolicExpression::default_mw( mw );
    mw.add_include( "Metil/Level1/SymbolHeader.h" );
}

END_METIL_LEVEL1_NAMESPACE;
