#include "TypeConstructor_FileWithoutClose.h"
#include "Dout.h"

#include <cstdio>
#include <cstring>

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1( MO &a, MO b ) {
    const char *ptr = reinterpret_cast<const char *>( b.data );
    DOUT( std::strlen( ptr ) );
    std::fwrite( ptr, 1, std::strlen( ptr ), reinterpret_cast<FILE *>( a.data ) );
}

END_METIL_LEVEL1_NAMESPACE;
