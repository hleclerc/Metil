#include "TypeConstructor_Select.h"
#include "TypeConstructor_Array.h"
#include "TypeConstructor_Cst.h"
#include "MethodFinder.h"
#include "Tokenize.h"

BEG_METIL_LEVEL1_NAMESPACE;

static TypeConstructor_Array *sc( Type *type ) {
    return static_cast<TypeConstructor_Array *>( type->constructor );
}

void metil_gen_allocate_array__when__b__isa__Cst( MethodWriter &mw, const Mos *args, const String &ret ) {
    mw.add_include( "Level1/TypeConstructor_Array.h" );

    // type
    TypeConstructor_Cst *c = static_cast<TypeConstructor_Cst *>( mw.get_type( 1 )->constructor );
    SI64 size; c->conversion_to( size );
    String type_vec, item_type = mw.get_type( 0 )->name;
    type_vec << "Array_" << item_type.size() << item_type << "_1_" << size << '_' << size;
    mw.add_type_decl( type_vec);
    int ss = mw.get_type( 0 )->constructor->static_size_in_bytes();
    ASSERT( ss >= 0, "TODO: static vectors of varying sizes" );

    // data
    mw.n << args[ 0 ].type << " = &metil_type_bas_" << type_vec << ";";
    mw.n << args[ 0 ].data << " = MALLOC( Number<" << size * ss << ">() );";
    mw.n << ret << args[ 0 ].data << ";";
}

void metil_gen_allocate_array__when__b__isa__Int( MethodWriter &mw, const Mos *args, const String &ret ) {
    // get type
    String type_vec, item_type = mw.get_type( 0 )->name;
    type_vec << "Array_" << item_type.size() << item_type << "_1_m_m_CptUse";
    mw.add_type_decl( type_vec );

    mw.n << args[ 0 ].type << " = &metil_type_bas_" << type_vec << ";";
    mw.n << ret << "CM_2( allocate, " << args[ 0 ] << ", " << args[ 1 ] << " );";
}

void metil_gen_allocate__when__a__isa__Array__and__b__isa__Int__pert__1( MethodWriter &mw, const Mos *args, const String &ret ) {
    TypeConstructor_Array *c = sc( mw.get_type( 0 ) );
    if ( c->len() == 0 ) // nothing to allocate
        return;
    // wanted size
    call_gene<MethodName_convert_to_SI64>( mw, mw.get_type( 1 ), 0, 0, args + 1, "ST size = " );

    // rese_mem
    c->write_get_static_s( mw, "ss" );
    if ( c->need_header() ) {
        c->write_get_t_header( mw, "AH" );
        mw.n << "ST rese_mem = sizeof( AH ) + size * ss;";

        // fill header
        mw.n << "AH *header = (AH *)MALLOC( rese_mem );";
        mw.n << "new( header ) AH;";
        mw.n << "header->rese_mem = rese_mem;";
        mw.n << "header->size[ 0 ] = size;";
        mw.n << "header->rese[ 0 ] = ( rese_mem - sizeof( AH ) ) / ss;";

        // ret
        mw.n << args->data << " = header;";
        mw.n << ret << "header;";
    } else {
        mw.n << "ST rese_mem = size * ss;";
        mw.n << "void *header = MALLOC( rese_mem );";
    }
    // mw.n << "set_machine_id( wmi, header, mid );";

    mw.n << ret << "header;";
}

void metil_gen_init_arg__when__a__isa__Array__pert__1( MethodWriter &mw, const Mos *args, const String &ret ) {
    TypeConstructor_Array *c = sc( mw.get_type( 0 ) );
    c->write_smp_beg_loop( mw, args[ 0 ].data, false );
    Mos loc_args[ 2 ] = { Mos( "d", "" ), args[ 1 ] };
    if ( c->item_type_bas )
        call_gene<MethodName_init_arg>( mw, c->item_type_bas, mw.get_type( 1 ), 0, loc_args );
    else
        call_gene<MethodName_copy>( mw, mw.get_type( 1 ), 0, 0, args + 1, "*d = " );
    c->write_smp_end_loop( mw );
}



void metil_gen_select_C__when__a__isa__Array__pert__1( MethodWriter &cw, const Mos *args, const String &ret ) {
    TypeConstructor_Array *c = sc( cw.get_type( 0 ) );

    // header
    c->write_get_t_header( cw, "AH" );
    c->write_get_header( cw, "h", args[ 0 ].data, "AH" );
    c->write_get_data_ptr( cw, true, "d", "h", args[ 0 ].data );
    c->write_get_index( cw, "index", cw.get_type( 1 )->constructor, args[ 1 ], "h" );

    if ( c->item_type_bas ) {
        Mos d; d.data << "d + index * " << c->item_type_bas->constructor->static_size_in_bytes();
        call_gene<MethodName_copy>( cw, c->item_type_bas, 0, 0, &d );
    } else
        cw.n << ret << "CM_1( copy, d[ index ] );";
}

void metil_gen_select__when__a__isa__Array__pert__1( MethodWriter &cw, const Mos *args, const String &ret ) {
    cw.add_include( "Pair.h" );
    cw.add_include( "Level1/TypeConstructor_Select.h" );
    TypeConstructor_Array *c_0 = static_cast<TypeConstructor_Array *>( cw.get_type( 0 )->constructor );
    TypeConstructor *c_1 = cw.get_type( 1 )->constructor;

    String select_type = "Select_";
    select_type << strlen( cw.get_type( 0 )->name ) << cw.get_type( 0 )->name;
    select_type << "8Int_s_64";

    if ( c_0->dim() > 1 )
        c_0->write_get_header( cw, "h", args[ 0 ].data );
    c_0->write_get_index( cw, "index", c_1, args[ 1 ], "h" );

    cw.add_type_decl( select_type );
    cw.n << "typedef Pair<void *,ST> P;";
    cw.n << ret << "MO( NEW( P, " << args[ 0 ].data << ", index ), &metil_type_bas_" << select_type << " );";
}


void metil_gen_set_values__when__a__isa__Array__and__b__has__tensor_order_0__pert__1( MethodWriter &cw, const Mos *args, const String &ret ) {
    TypeConstructor_Array *c = static_cast<TypeConstructor_Array *>( cw.get_type( 0 )->constructor );
    c->write_get_t_header( cw, "AH" );
    c->write_get_header( cw, "h", args[ 0 ].data, "AH" );
    c->write_get_data_ptr( cw, false, "d", "h", args[ 0 ].data );

    // beg loop
    for(int d = c->dim() - 1; d >= 0; --d )
        c->write_beg_loop( cw, "h", d );

    if ( c->item_type_bas ) {
        Mos d[ 2 ];
        d[ 0 ].data << "d";
        d[ 1 ] = args[ 1 ];
        call_gene<MethodName_reassign_inplace>( cw, c->item_type_bas, cw.get_type( 1 ), 0, d );
    } else {
        cw.n << "CM_2( reassign, *d, " << args[ 1 ] << " );";
    }

    // end loop
    for(int d = 0; d < c->dim(); ++d )
        c->write_end_loop( cw, "h", d, "d" );
}


void TypeConstructor_Array::write_del( MethodWriter &cw, const Mos *args, const String & ) const {
    if ( len() == 0 ) // nothing to del
        return;
    if ( want_CptUse or dyn() ) {
        write_get_t_header( cw, "AH" );
        write_get_header( cw, "h", args[ 0 ].data, "AH" );
    }

    //
    if ( want_CptUse ) {
        cw.n << "if ( --h->cpt_use >= 0 )";
        cw.n << "return;";
    }

    // destroy items
    if ( item_type_bas ) {
        if ( not item_type_bas->constructor->is_a_POD() ) {
            TODO;
        }
    } else {
        write_get_data_ptr( cw, false, "d", "h", args[ 0 ].data );
        for(int d = dim() - 1; d >= 0; --d )
            write_beg_loop( cw, "h", d );
        cw.n << "CM_1( del, *d );";
        for(int d = 0; d < dim(); ++d )
            write_end_loop( cw, "h", d, "d" );
    }

    // free data
    if ( dyn() ) {
        cw.n << "FREE( h, h->rese_mem );";
    } else {
        cw.n << "FREE( " << args->data << ", Number<" << static_size_in_bytes() << ">() );";
    }
}

void TypeConstructor_Array::write_init( MethodWriter &cw, const Mos *args, const String & ) const {
    if ( item_type_bas and item_type_bas->constructor->is_a_POD() )
        return;
    // TODO;
    write_get_t_header( cw, "AH" );
    write_get_header( cw, "h", args[ 0 ].data, "AH" );
    write_get_data_ptr( cw, false, "d", "h", args[ 0 ].data );
    for(int d = dim() - 1; d >= 0; --d )
        write_beg_loop( cw, "h", d );
    // cw.n << "CM_1( del, *d );";
    cw.n << "TODO;";
    for(int d = 0; d < dim(); ++d )
        write_end_loop( cw, "h", d, "d" );
}

void TypeConstructor_Array::write_copy( MethodWriter &mw, const Mos *a, const String &ret_ins ) const {
    if ( want_CptUse ) {
        write_get_t_header( mw, "AH" );
        write_get_header( mw, "h", a->data, "AH" );
        mw.n << "++h->cpt_use;";
        mw.n << ret_ins << *a << ";";
    } else {
        mw.add_include( "Level1/StringHelp.h" );
        if ( need_header() ) {
            write_get_t_header( mw, "AH" );
            write_get_header( mw, "h", a->data, "AH" );
            mw.n << "ST rese_mem = h->rese_mem;";
            mw.n << "AH *data = (AH *)MALLOC( rese_mem );";
            if ( item_type_bas and item_type_bas->constructor->is_a_POD() )
                mw.n << "memcpy( data, " << a->data << ", h->rese_mem );";
            else
                mw.n << "TODO;";
            mw.n << ret_ins << "MO( data, " << a->type << "->bas_type );";
        } else {
            int s = static_size_in_bytes();
            ASSERT( s >= 0, "..." );
            mw.n << "Number<" << s << "> sn;";
            mw.n << "void *data = MALLOC( sn );";
            if ( item_type_bas and item_type_bas->constructor->is_a_POD() )
                mw.n << "memcpy( data, " << a->data << ", sn );";
            else
                mw.n << "TODO;";
            mw.n << ret_ins << "MO( data, " << a->type << "->bas_type );";
        }
    }
}

void TypeConstructor_Array::write_size( MethodWriter &mw, const Mos *a, const String &ret_ins ) const {
    if ( len() == 0 ) // nothing to del
        mw.n << ret_ins << "&metil_type_cst_Cst_0;";
    else {
        write_get_t_header( mw, "AH" );
        write_get_header( mw, "h", a[ 0 ].data, "AH" );
        write_get_len( mw, "res", "h" );
        mw.n << ret_ins << "NEW_Number( res );";
    }
}

void TypeConstructor_Array::write_sizes( MethodWriter &mw, const Mos *a, const String &ret_ins ) const {
    if ( dim() == 0 ) {
        mw.n << ret_ins << "&metil_type_cst_Array_4NULL_0;";
        return;
    }

    write_get_t_header( mw, "AH" );
    write_get_header( mw, "h", a->data, "AH" );
    if ( len_size() == dim() ) {
        String type_vec_32, type_vec_64;
        type_vec_32 << "Array_8Int_s_32_1_" << dim() << "_" << dim();
        type_vec_64 << "Array_8Int_s_64_1_" << dim() << "_" << dim();
        mw.add_type_decl( type_vec_32 );
        mw.add_type_decl( type_vec_64 );
        mw << "ST *data = h->size;";
        mw.n << "Type *type = sizeof( void *) == 8 ? &metil_type_cst_" << type_vec_64 << " : &metil_type_cst_" << type_vec_32 << ";";
        mw.n << ret_ins << "MO( data, type );";
    } else {
        String type; type << "Array_8Int_s_64_1_" << dim() << "_" << dim();
        mw.add_type_decl( type );
        mw.n << "SI64 *data = ALLOC_STATIC_VEC( SI64, " << dim() << " );";
        for(int d = 0; d < dim(); ++d )
            mw.n << "data[ " << d << " ] = " << get_size_n( "h", d ) << ";";
        mw.n << ret_ins << "MO( data, &metil_type_bas_" << type << " );";
    }
}

void TypeConstructor_Array::write_machine_id( MethodWriter &mw, const Mos *a, const String &ret_ins ) const {
    if ( want_MachineId ) {
        write_get_t_header( mw, "AH" );
        write_get_header( mw, "h", a[ 0 ].data, "AH" );
        mw.n << ret_ins << "h->machine_id;";
    } else {
        mw.n << ret_ins << "MachineId::cur();";
    }
}

void TypeConstructor_Array::write_write_str( MethodWriter &mw, const Mos *args, const String &ret ) const {
    if ( len() == 0 ) // nothing to display
        return;

    // header
    write_get_t_header( mw, "AH" );
    write_get_header( mw, "h", args->data, "AH" );
    write_get_data_ptr( mw, true, "d", "h", args->data );

    // beg loop
    for(int d = dim() - 1; d >= 0; --d ) {
        write_beg_loop( mw, "h", d );
        mw.n << "if ( i_" << d << " ) os.write_separator( " << d << " );";
    }

    if ( item_type_bas ) {
        Mos d[ 2 ];
        d[ 0 ] = Mos( "os" );
        d[ 1 ].data << "d";
        call_gene<MethodName_self_append>( mw, mw.get_type( 0 ), item_type_bas, 0, d );
    } else
        mw.n << "os << *d;";

    // end loop
    for(int d = 0; d < dim(); ++d )
        write_end_loop( mw, "h", d, "d" );
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
        write_get_t_header( mw, "AH" );
        write_get_header( mw, "h", "select_data->a", "AH" );
        write_get_data_ptr( mw, false, "d", "h", "select_data->a" );
        mw.n << "ST index = select_data->b;";
        if ( item_type_bas ) {
            Mos d[ 2 ];
            d[ 0 ].data << "d + index * " << item_type_bas->constructor->static_size_in_bytes();
            if ( op == "copy" )
                call_gene<MethodName_copy>( mw, item_type_bas, 0, 0, d );
            else
                d[ 1 ] = a[ 1 ];

            #define DECL_MET( T, N ) if ( op == #N ) call_gene<MethodName_##N##_inplace>( mw, item_type_bas, mw.get_type( 1 ), 0, d );
            #include "DeclMethodsBinarySelfOp.h"
            #undef DECL_MET
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
    if ( item_type_bas )
        return item_type_bas->constructor->needed_alignement_in_bits();
    return 1;
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

bool TypeConstructor_Array::need_header() const {
    return len_size() or len_rese() or want_CptUse or want_ExtPtr;
}

void TypeConstructor_Array::write_get_t_header( MethodWriter &cw, const String &name_type ) const {
    if ( need_header() ) {
        int al = bas_type ? bas_type->constructor->needed_alignement_in_bytes_if_in_vec(
                                want_Gpu ? MachineId::gpu( MachineId::cur(), 0 ) : MachineId::cur()
                                           ) : 1;
        cw.n << "typedef ArrayHeader<"
           << len_size() << ","
           << len_rese() << ","
           << want_CptUse << ","
           << want_ExtPtr << ","
           << want_MachineId << ","
           << al << "> " << name_type << ";";
    }
}

void TypeConstructor_Array::write_get_static_s( MethodWriter &mw, const String &res ) const {
    mw << "const ST " << res << " = ";
    if ( item_type_bas )
        mw.n << item_type_bas->constructor->static_size_in_bytes() << ";";
    else
        mw.n << "sizeof( MO );";
}

void TypeConstructor_Array::write_get_header( MethodWriter &cw, const String &name_header, const String &data, const String &name_type ) const {
    if ( need_header() )
        cw << name_type << " *" << name_header << " = reinterpret_cast<" << name_type << " *>( " << data << " );\n";
}

void TypeConstructor_Array::write_get_data_ptr( MethodWriter &cw, bool want_const, const String &name_data, const String &name_header, const String &data ) const {
    String type; type << ( want_const ? "const " : "" ) << ( item_type_bas ? "char" : "MO" ) << " *";
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
        else {
            if ( item_type_bas )
                cw << ptr_on_data << " += " << item_type_bas->constructor->static_size_in_bytes() << ";\n";
            else
                cw << "++" << ptr_on_data << ";\n";
        }
    }
    cw << "}\n";
}

void TypeConstructor_Array::write_smp_beg_loop( MethodWriter &mw, const String &data, bool want_const ) const {
    if ( len() == 0 )
        return;
    write_get_t_header( mw, "AH" );
    write_get_header( mw, "h", data, "AH" );
    write_get_data_ptr( mw, want_const, "d", "h", data );
    for(int d = dim() - 1; d >= 0; --d )
        write_beg_loop( mw, "h", d );
}

void TypeConstructor_Array::write_smp_end_loop( MethodWriter &mw ) const {
    if ( len() == 0 )
        return;
    for(int d = 0; d < dim(); ++d )
        write_end_loop( mw, "h", d, "d" );
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

    want_CptUse    = false;
    want_ExtPtr    = false;
    want_Gpu       = false;
    want_MachineId = false;
    item_type_bas  = 0;

    // start parsing
    const char *name = type->name + 6;

    // type_name
    String type_name = String::read_sized( name );
    item_type_bas = Type::find_with_name( type_name.c_str() );

    BasicVec<String> lst = tokenize( name + 1, '_' );

    int dim = Val( lst[ 0 ] );
    size.resize( dim );
    rese.resize( dim );
    for( int d = 0; d < dim; ++d ) {
        size[ d ] = read_int( lst[ 1 + 2 * d ] );
        rese[ d ] = read_int( lst[ 2 + 2 * d ] );
    }

    for( int d = 1 + 2 * dim; d < lst.size(); ++d ) {
        if ( lst[ d ] == "CptUse" ) { want_CptUse = true; }
        if ( lst[ d ] == "ExtPtr" ) { want_ExtPtr = true; }
        if ( lst[ d ] == "Gpu"    ) { want_Gpu    = true; want_MachineId = true; }
    }
}

END_METIL_LEVEL1_NAMESPACE;
