#include "TypeConstructor_OwcpString.h"
#include "OwcpStringData.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_del__when__a__isa__OwcpString( MO &a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    if ( --o->cpt_use < 0 )
        FREE( o, o->rese() );
}

MO metil_def_copy__when__a__isa__OwcpString( MO a ) {
    ++reinterpret_cast<OwcpStringData *>( a.data )->cpt_use;
    return a;
}

END_METIL_LEVEL1_NAMESPACE;
