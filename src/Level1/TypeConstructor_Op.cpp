#include "TypeConstructor_Op.h"

BEG_METIL_LEVEL1_NAMESPACE;

void TypeConstructor_Op::write_write_str( MethodWriter &mw, const Mos *a, const String & ) const {
    mw.n << "Owcp<2> *s = reinterpret_cast<Owcp<2> *>( " << a->data << " );";
    mw.n << "os << \"" << name << "(\" << s->ch( 0 ) << ',' << s->ch( 1 ) << ')';";
}

void TypeConstructor_Op::init( Type *type ) {
    name = type->name + 3;
    nb_children = 2;
}

END_METIL_LEVEL1_NAMESPACE;
