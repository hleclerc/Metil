#include "TypeConstructor_Select.h"
#include "TypeConstructor_Array.h"
#include "Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

static TypeConstructor_Array *sc( Type *type ) {
    return static_cast<TypeConstructor_Array *>( type->constructor );
}

void metil_gen_self_append__when__a__isa__String__and__b__isa__Array__pert__1( MethodWriter &cw, Mos *args ) {
    TypeConstructor_Array *c = sc( cw.type[ 1 ] );
    if ( c->len() == 0 ) // nothing to display
        return;

    // header
    c->write_get_header( cw, "h", args[ 1 ].data );
    c->write_get_data_ptr( cw, true, "d", "h", args[ 1 ].data );
    if ( c->item_type_bas )
        cw.n << "Type *type = reinterpret_cast<TypeConstructor_Array *>( " << args[ 1 ].type << "->constructor )->item_type_bas;";
    cw.n << "String &os = static_cast<String &>( a );";

    // beg loop
    for(int d = c->dim() - 1; d >= 0; --d ) {
        c->write_beg_loop( cw, "h", d );
        cw.n << "if ( i_" << d << " ) os.write_separator( " << d << " );";
    }

    if ( c->item_type_bas ) {
        // item_type_bas->constructor->write_write_str( cw, MOS( "d", "type" ) );
        TODO;
    } else
        cw.n << "os << *d;";

    // end loop
    for(int d = 0; d < c->dim(); ++d )
        c->write_end_loop( cw, "h", d, "d" );
}

void TypeConstructor_Array::write_get_index( MethodWriter &cw, const String &name_res, const TypeConstructor *c_1, const Mos &d_1, const String &name_header ) const {
    int to = c_1->tensor_order();
    if ( to == 0 ) {
        cw.n << "ST index = static_cast<const Val &>( " << d_1 << " );";
    } else if ( to == 1 ) {
        cw.n << "ST i = 0, c = 1, index = 0;";
        for( int d = 0; d < tensor_order(); ++d ) {
            if ( d )
                cw.n << "i = " << d << ";";
            cw.n << "index += c * static_cast<const Val &>( CM_2( select_C, " << d_1 << ", REF_Number( i ) ) );";
            if ( d < tensor_order() - 1 )
                cw.n << "c *= " << get_rese_n( "h", d ) << ";";
        }
    }
}

void metil_gen_select_C__when__a__isa__Array__pert__1( MethodWriter &cw, Mos *args ) {
    TypeConstructor_Array *c = sc( cw.type[ 0 ] );

    // header
    c->write_get_header( cw, "h", args[ 0 ].data );
    c->write_get_data_ptr( cw, true, "d", "h", args[ 0 ].data );
    c->write_get_index( cw, "index", cw.type[ 1 ]->constructor, args[ 1 ], "h" );

    if ( c->item_type_bas ) {
        // item_type_bas->constructor->write_write_str( cw, MOS( "d", "type" ) );
        TODO;
    } else
        cw.n << "return CM_1( copy, d[ index ] );";
}

void metil_gen_select__when__a__isa__Array__pert__1( MethodWriter &cw, Mos *args ) {
    cw.add_include( "Pair.h" );
    cw.add_include( "Level1/TypeConstructor_Select.h" );
    TypeConstructor_Array *c_0 = static_cast<TypeConstructor_Array *>( cw.type[ 0 ]->constructor );
    TypeConstructor *c_1 = cw.type[ 1 ]->constructor;

    String select_type = "Select_";
    select_type << strlen( cw.type[ 0 ]->name ) << cw.type[ 0 ]->name;
    select_type << "8Int_s_64";

    c_0->write_get_header( cw, "h", args[ 0 ].data );
    c_0->write_get_index( cw, "index", c_1, args[ 1 ], "h" );

    cw.add_preliminary( "DECL_TYPE( " + select_type + " );\n" );
    cw.add_preliminary( "DEFI_TYPE( Select, " + select_type + " );\n" );
    cw.n << "typedef Pair<void *,ST> P;";
    cw.n << "return MO( NEW( P, " << args[ 0 ].data << ", index ), &metil_type_bas_" << select_type << " );";
}

void metil_gen_del__when__a__isa__Array( MethodWriter &cw, Mos *args ) {
    TypeConstructor_Array *c = sc( cw.type[ 0 ] );
    if ( c->len() == 0 ) // nothing to del
        return;
    if ( c->want_CptUse or c->dyn() )
        c->write_get_header( cw, "h", args[ 0 ].data );

    //
    if ( c->want_CptUse ) {
        cw.n << "if ( --h->cpt_use >= 0 )";
        cw.n << "return;";
    }

    // destroy items
    if ( c->item_type_bas ) {
        TODO;
    } else {
        c->write_get_data_ptr( cw, false, "d", "h", args[ 0 ].data );
        for(int d = c->dim() - 1; d >= 0; --d )
            c->write_beg_loop( cw, "h", d );
        cw.n << "CM_1( del, *d );";
        for(int d = 0; d < c->dim(); ++d )
            c->write_end_loop( cw, "h", d, "d" );
    }

    // free data
    if ( c->dyn() ) {
        cw.n << "FREE( h, h->rese_mem );";
    } else {
        TODO;
    }
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

void TypeConstructor_Array::write_select_op( MethodWriter &mw, const Mos *a, TypeConstructor *index_type, const String &op ) const {
    mw.add_include("Level1/ArrayHeader.h");
    mw.add_include("String.h");
    mw.add_include("Pair.h");
    if ( index_type->tensor_order() == 0 ) {
        mw.n << "typedef Pair<void *,ST> P;";
        mw.n << "P *select_data = reinterpret_cast<P *>( " << a[ 0 ].data << " );";
        write_get_header( mw, "h", "select_data->a" );
        write_get_data_ptr( mw, false, "d", "h", "select_data->a" );
        mw.n << "ST index = select_data->b;";
        if ( item_type_bas ) {
            TODO;
        } else {
            if ( op == "copy" )
                mw.n << "return CM_1( " << op << ", d[ index ] );";
            else
                mw.n << "CM_2( " << op << ", d[ index ], " << a[ 1 ] << " );";
        }
    } else {
        TODO;
    }
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

void TypeConstructor_Array::write_get_data_ptr( MethodWriter &cw, bool want_const, const String &name_data, const String &name_header, const String &data ) const {
    String type; type << ( want_const ? "const " : "" ) << ( item_type_bas ? "void" : "MO" ) << " *";
    if ( want_ExtPtr ) {
        cw << type << name_data << " = reinterpret_cast<" << type << ">( " << name_header << "->ext_ptr );\n";
    } else {
        if ( dyn() ) {
            String offset; offset << "sizeof( *" << name_header << " )";
            cw << type << name_data << " = reinterpret_cast<" << type << ">( (char *)" << name_header << " + " << offset << " );\n";
        } else {
            cw << type << name_data << " = reinterpret_cast<" << type << ">( " << data << " );\n";
        }
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
    if ( ptr_on_data.size() ) {
        if ( d )
            cw << ptr_on_data << " += " << inc << " * ( " <<
                  get_rese_n( name_header, d - 1 ) << " - " <<
                  get_size_n( name_header, d - 1 ) << " );\n";
        else
            cw << "++" << ptr_on_data << ";\n";
    }
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
    TypeConstructor::init( type );

    want_CptUse = false;
    want_ExtPtr = false;
    item_type_bas = 0;

    const char *name = type->name + 6;

    // type_name
    String type_name = String::read_sized( name );

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
