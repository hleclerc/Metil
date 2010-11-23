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
MO metil_def_get_child__when__a__has__Owcp_type__pert__1( MO a, ST i ) {
    Owcp<2> *o = reinterpret_cast<Owcp<2> *>( a.data ); // would be the same result with s != 2
    return o->ch( i );
}

//
void metil_gen_del__when__a__has__Owcp_type__pert__0( MethodWriter &mw, const Mos *args, const String & ) {
    PRINT(__FILE__);
    mw.n << "reinterpret_cast<Owcp<" << mw.get_type( 0 )->constructor->Owcp_size() << "," << mw.get_type( 0 )->constructor->Owcp_data() << " > *>( " << args[ 0 ].data << " )->dec_ref();";
}

END_METIL_LEVEL1_NAMESPACE;
