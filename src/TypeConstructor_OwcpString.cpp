#include "TypeConstructor_OwcpString.h"
#include "OwcpStringData.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_del__when__a__isa__OwcpString( MO &a ) {
    OwcpStringData *o = reinterpret_cast<OwcpStringData *>( a.data );
    FREE( o, o->rese() );
}

END_METIL_LEVEL1_NAMESPACE;
