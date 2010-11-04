#include "TypeConstructor_Select.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_reassign__when__a__isa__Select__pert__1( MethodWriter &mw, const Mos *args, const String & ) {
    TypeConstructor_Select *c = static_cast<TypeConstructor_Select *>( mw.type[ 0 ]->constructor );
    c->type_a->constructor->write_select_op( mw, args, c->type_b->constructor, "reassign" );
}

void TypeConstructor_Select::write_copy( MethodWriter &mw, const Mos *args, const String & ) const {
    type_a->constructor->write_select_op( mw, args, type_b->constructor, "copy" );
}

void TypeConstructor_Select::write_del( MethodWriter &mw, const Mos *a, const String & ) const {
    ASSERT( type_b->constructor->is_a_POD(), "TODO" );
    mw.n << "FREE( " << a[ 0 ].data << ", Number< sizeof( void * ) + "
         << type_b->constructor->static_size_in_bytes() << " >() );";
}

void TypeConstructor_Select::init( Type *type ) {
    TypeConstructor::init( type );
    const char *name = type->name + 7; // Select_
    String str_type_a = String::read_sized( name );
    String str_type_b = String::read_sized( name );
    type_a = Type::find_with_name( str_type_a.c_str() );
    type_b = Type::find_with_name( str_type_b.c_str() );
}

END_METIL_LEVEL1_NAMESPACE;
