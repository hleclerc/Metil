#include "Owcp.h"
#include "String.h"

BEG_METIL_LEVEL1_NAMESPACE;

//
void metil_def_del__when__a__has__Owcp_size_0__pert__1( MO &a ) {
    Owcp<0> *o = reinterpret_cast<Owcp<0> *>( a.data );
    if ( --o->cpt_use < 0 ) DEL( o );
}

//
void metil_def_del__when__a__has__Owcp_size_1__pert__1( MO &a ) {
    Owcp<1> *o = reinterpret_cast<Owcp<1> *>( a.data );
    if ( --o->cpt_use < 0 ) DEL( o );
}

//
void metil_def_del__when__a__has__Owcp_size_2__pert__1( MO &a ) {
    Owcp<2> *o = reinterpret_cast<Owcp<2> *>( a.data );
    if ( --o->cpt_use < 0 ) DEL( o );
}

//
void metil_def_del__when__a__has__Owcp_size_3__pert__1( MO &a ) {
    Owcp<3> *o = reinterpret_cast<Owcp<3> *>( a.data );
    if ( --o->cpt_use < 0 ) DEL( o );
}

//
MO metil_def_copy__when__a__has__Owcp_type__pert__1( MO a ) {
    ++reinterpret_cast<OwcpAncestor *>( a.data )->cpt_use;
    return a;
}


END_METIL_LEVEL1_NAMESPACE;
