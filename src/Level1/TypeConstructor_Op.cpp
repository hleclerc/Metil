#include "TypeConstructor_Op.h"

BEG_METIL_LEVEL1_NAMESPACE;

void TypeConstructor_Op::write_write_str( MethodWriter &mw ) const {
    mw.n << "Owcp<" << child_types.size() << "> *s = reinterpret_cast<Owcp<" << child_types.size() << "> *>( " << mw.arg[ 0 ].data << " );";
    mw << "os << \"" << name << "(\"";
    for( int i = 0; i < child_types.size(); ++i )
        mw << ( i ? " << ','": "" ) << " << s->ch( " << i << " )";
    mw.n << " << ')';";
}

int TypeConstructor_Op::Owcp_size() const {
    return child_types.size();
}

void TypeConstructor_Op::init( Type *type ) {
    name = type->name + 3;

    ST p = name.find( "_" );
    if ( p >= 0 ) {
        for( ST o = p + 1; o < name.size(); ++o ) {
            if ( name[ o ] == "V" ) { child_types << V_child; continue; }
            if ( name[ o ] == "P" ) { child_types << P_child; continue; }
            if ( name[ o ] == "N" ) { child_types << N_child; continue; }
            ERROR( "unknown type child for %s", name.c_str() );
        }
        name = name.beg_upto( p );
    }
}

END_METIL_LEVEL1_NAMESPACE;
