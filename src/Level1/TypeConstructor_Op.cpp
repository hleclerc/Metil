#include "TypeConstructor_Op.h"

BEG_METIL_LEVEL1_NAMESPACE;

void toto() { metil_type_bas_Op_Add.init_if_necessary(); }

void metil_gen_del__when__a__isa__Op( MethodWriter &mw, const Mos *args, const String &ret ) {
    mw.n << ret << "owcp_DEL( reinterpret_cast<Owcp<2> *>( " << args->data << " ) );";
}

void TypeConstructor_Op::write_write_str( MethodWriter &mw, const Mos *a, const String & ) const {
    mw.n << "Owcp<2> *s = reinterpret_cast<Owcp<2> *>( " << a->data << " );";
    mw.n << "os << \"" << name << "(\" << s->ch( 0 ) << ',' << s->ch( 1 ) << ')';";
}

void TypeConstructor_Op::default_mw( MethodWriter &mw ) const {
    TypeConstructor_SymbolicExpression::default_mw( mw );
    mw.add_include( "Level1/Owcp.h" );
}

void TypeConstructor_Op::init( Type *type ) {
    name = type->name + 3;
    nb_children = 2;
}

END_METIL_LEVEL1_NAMESPACE;
