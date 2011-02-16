#include "TypeConstructor_SymbolicArray.h"

BEG_METIL_LEVEL1_NAMESPACE;

void TypeConstructor_SymbolicArray::write_convert_to_Bool( MethodWriter &mw ) const {
    PRINT( op.type->name );
    PRINT( Level1::metil_type_bas_Op_equal_P_P.name );
    if ( op.type == &Level1::metil_type_bas_Op_equal_P_P ) {
        // TODO use of types
        mw.add_include( "Vec.h" );
        mw.n << "const Owcp<2> *vo = reinterpret_cast<const Owcp<2> *>( " << mw.arg[ 0 ].data << " );"; // HUM
        mw.n << "const Vec &va = static_cast<const Vec &>( vo->ch( 0 ) );"; // HUM
        mw.n << "const Vec &vb = static_cast<const Vec &>( vo->ch( 1 ) );"; // HUM
        mw.n << "if ( va.size() != vb.size() ) return false;";
        mw.n << "for( int i = 0; i < va.size(); ++i )";
        mw.n << "    if( va[ i ] != vb[ i ] )";
        mw.n << "        return false;";
        mw.n << "return true;";
    } else {
        mw.n << "TODO;";
        mw.ret() << "false;";
    }
}

void TypeConstructor_SymbolicArray::write_write_str( MethodWriter &mw ) const {
    mw.n << "TODO;";
}

int TypeConstructor_SymbolicArray::Owcp_size() const {
    return children.size();
}

void TypeConstructor_SymbolicArray::init( Type *type ) {
    const char *name = type->name + 14;

    int nb_children = String::read_int( name ); ++name;
    for( int i = 0; i < nb_children; ++i ) {
        String type_name = String::read_sized( name ); ++name;
        children << Type::find_with_name( type_name.c_str() );
        children.back()->init_if_necessary();
    }
    op = Val::read_from_type_name( name );
}

END_METIL_LEVEL1_NAMESPACE;
