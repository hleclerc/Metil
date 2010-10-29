#include "TypeConstructor_Array.h"
#include "Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_self_append__when__a__isa__String__and__b__isa__Array__pert__1( MethodWriter &cw, Mos *args ) {
    TypeConstructor_Array *c = static_cast<TypeConstructor_Array *>( cw.type[ 1 ]->constructor );
    if ( c->len() == 0 ) // nothing to display
        return;

    // header
    c->write_get_header( cw, "h", args[ 1 ].data );
    c->write_get_data_ptr( cw, true, "d", "h" );
    if ( c->item_type_bas )
        cw << "Type *type = reinterpret_cast<TypeConstructor_Array *>( " << args[ 1 ].type << "->constructor )->item_type_bas;\n";
    cw << "String &os = static_cast<String &>( a );\n";

    // beg loop
    for(int d = c->dim() - 1; d >= 0; --d ) {
        c->write_beg_loop( cw, "h", d );
        cw << "if ( i_" << d << " ) os.write_separator( " << d << " );\n";
    }

    if ( c->item_type_bas ) {
        // item_type_bas->constructor->write_write_str( cw, MOS( "d", "type" ) );
        TODO;
    } else
        cw << "os << *d;\n";

    // end loop
    for(int d = 0; d < c->dim(); ++d )
        c->write_end_loop( cw, "h", d, "d" );
}


void TypeConstructor_Array::default_mw( MethodWriter &mw ) const {
    TypeConstructor::default_mw( mw );
    mw.add_include( "String.h" );
    mw.add_include( "Level1/ArrayHeader.h" );
}

int TypeConstructor_Array::dim() const {
    return size.size();
}

int TypeConstructor_Array::tensor_order() const {
    return dim();
}

int TypeConstructor_Array::len() const {
    int res = 1;
    for( int d = 0; d < size.size(); ++d ) {
        if ( size[ d ] < 0 )
            return -1;
        res *= size[ d ];
    }
    return res;
}

bool TypeConstructor_Array::dyn() const {
    return len() < 0;
}

int TypeConstructor_Array::len_size() const {
    int res = 0;
    for( int d = 0; d < size.size(); ++d )
        res += size[ d ] < 0;
    return res;
}

int TypeConstructor_Array::len_rese() const {
    int res = 0;
    for( int d = 0; d < rese.size(); ++d )
        res += rese[ d ] < 0;
    return res;
}

int TypeConstructor_Array::needed_alignement_in_bits() const {
    TODO;
    return 0;
}

int TypeConstructor_Array::static_size_in_bits() const {
    int al = item_type_bas ? item_type_bas->constructor->needed_alignement_in_bits() : 8;
    ASSERT( al <= 8, "TODO" );
    //
    if ( len() < 0 )
        return -1;
    if ( item_type_bas ) {
        int sb = item_type_bas->constructor->static_size_in_bits();
        return sb >= 0 ? sb * len() : -1;
    }
    return sizeof( MO ) * len();
}

void TypeConstructor_Array::write_get_header( MethodWriter &cw, const String &name_header, const String &data ) const {
    if ( len_size() or len_rese() or want_CptUse or want_ExtPtr )  {
        String h; h << "ArrayHeader<" << len_size() << "," << len_rese() << "," << want_CptUse << "," << want_ExtPtr << ">";
        cw << h << " *" << name_header << " = reinterpret_cast<" << h << " *>( " << data << " );\n";
    }
}

void TypeConstructor_Array::write_get_data_ptr( MethodWriter &cw, bool want_const, const String &name_data, const String &name_header ) const {
    String type = String( want_const ? "const " : "" ) + ( item_type_bas ? "void" : "MO" ) + " *";
    if ( want_ExtPtr ) {
        cw << type << name_data << " = reinterpret_cast<" << type << ">( " << name_header << "->ext_ptr );\n";
    } else {
        String offset; offset << "sizeof( *" << name_header << " )";
        cw << type << name_data << " = reinterpret_cast<" << type << ">( (char *)" << name_header << " + " << offset << " );\n";
    }
}

void TypeConstructor_Array::write_get_len( MethodWriter &cw, const String &name_res, const String &name_header ) const {
    cw << "ST " << name_res << " = ";
    if ( dyn() ) {
        for( int d = 0, c = 0; d < dim(); ++d ) {
            if ( size[ d ] < 0 )
                cw << ( d ? " * " : "" ) << name_header << "->size[ " << c++ << " ]";
            else
                cw << ( d ? " * " : "" ) << size[ d ] << " ]";
        }
    } else
        cw << len();
    cw << ";\n";
}

void TypeConstructor_Array::write_beg_loop( MethodWriter &cw, const String &name_header, int d ) const {
    cw << "for( ST i_" << d << " = 0; i_" << d << " < " << get_size_n( name_header, d ) << "; ++i_" << d << " ) {\n";
}

void TypeConstructor_Array::write_end_loop( MethodWriter &cw, const String &name_header, int d, const String &ptr_on_data, const String &inc ) const {
    if ( d and ptr_on_data.size() )
        cw << ptr_on_data << " += " << inc << " * ( " <<
              get_rese_n( name_header, d - 1 ) << " - " <<
              get_size_n( name_header, d - 1 ) << " );\n";
    cw << "}\n";
}

String TypeConstructor_Array::get_size_n( const String &name_header, int d ) const {
    int c = 0;
    for( int n = 0; n < d; ++n )
        c += size[ n ] < 0;
    if ( size[ d ] < 0 )
        return name_header + "->size[ " + String( c )  + " ]";
    return size[ d ];
}

String TypeConstructor_Array::get_rese_n( const String &name_header, int d ) const {
    int c = 0;
    for( int n = 0; n < d; ++n )
        c += rese[ n ] < 0;
    if ( rese[ d ] < 0 )
        return name_header + "->rese[ " + String( c )  + " ]";
    return rese[ d ];
}

static int read_int( const String &str ) {
    if ( str == "m" )
        return -1;
    return Val( str );
}

void TypeConstructor_Array::init( Type *type ) {
    want_CptUse = false;
    want_ExtPtr = false;
    item_type_bas = 0;

    const char *name = type->name + 6;

    // type_name
    int len_name_sub_type = 0;
    for( ; is_a_number( *name ); ++name )
        len_name_sub_type = 10 * len_name_sub_type + ( *name - '0' );
    String type_name = NewString( name, name + len_name_sub_type );
    name += len_name_sub_type;

    BasicVec<String> lst = tokenize( name + 1, '_' );

    int dim = Val( lst[ 0 ] );
    size.resize( dim );
    rese.resize( dim );
    for( int d = 0; d < dim; ++d ) {
        size[ d ] = read_int( lst[ 1 + 2 * d ] );
        rese[ d ] = read_int( lst[ 2 + 2 * d ] );
    }

    for( int d = 1 + 2 * dim; d < lst.size(); ++d ) {
        if ( lst[ d ] == "CptUse" ) want_CptUse = true;
        if ( lst[ d ] == "ExtPtr" ) want_ExtPtr = true;
    }
}

END_METIL_LEVEL1_NAMESPACE;
