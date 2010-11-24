#include "TypeConstructor.h"
#include "String.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

//
MO metil_def_copy__when__a__has__Owcp_type__pert__1( MO a ) {
    ++reinterpret_cast<OwcpAncestor *>( a.data )->cpt_use;
    return a;
}

//
ST metil_def_nb_children__when__a__has__Owcp_type__pert__1( MO a ) {
    return a.type->constructor->Owcp_size();
}

//
OwcpChild *metil_def_get_parent__when__a__has__Owcp_type__pert__1( MO a ) {
    return reinterpret_cast<OwcpAncestor *>( a.data )->first_parent;
}

void metil_def_add_parent__when__a__has__Owcp_type__pert__1( MO &a, struct OwcpChild *b ) {
    reinterpret_cast<OwcpAncestor *>( a.data )->add_parent( b );
}

void metil_def_rem_parent__when__a__has__Owcp_type__pert__1( MO &a, struct OwcpChild *b ) {
    reinterpret_cast<OwcpAncestor *>( a.data )->rem_parent( b );
}

//
MO metil_def_get_child__when__a__has__Owcp_type__pert__1( MO a, ST i ) {
    Owcp<2> *o = reinterpret_cast<Owcp<2> *>( a.data ); // would be the same result with s != 2
    return o->ch( i );
}

MO metil_def_get_op_mp__when__a__has__Owcp_type__pert__1( MO a ) {
    return reinterpret_cast<OwcpAncestor *>( a.data )->op_mp;
}

void metil_def_set_op_mp__when__a__has__Owcp_type__pert__1( MO &a, void *data, void *type ) {
    reinterpret_cast<OwcpAncestor *>( a.data )->op_mp.data = data;
    reinterpret_cast<OwcpAncestor *>( a.data )->op_mp.type = reinterpret_cast<Type *>( type );
}

//
void metil_gen_del__when__a__has__Owcp_type__pert__0( MethodWriter &mw ) {
    mw.n << "reinterpret_cast<Owcp<" << mw.get_type( 0 )->constructor->Owcp_size() << "," << mw.get_type( 0 )->constructor->Owcp_data() << " > *>( " << mw.arg[ 0 ].data << " )->dec_ref();";
}

END_METIL_LEVEL1_NAMESPACE;
