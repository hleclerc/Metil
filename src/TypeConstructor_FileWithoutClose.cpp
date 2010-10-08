#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "TypeConstructor_FileWithoutClose.h"
#include "OwcpStringData.h"
#include "Dout.h"

#include <cstdio>
#include <cstring>

BEG_METIL_LEVEL1_NAMESPACE;

// const char *
void metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__1( MO &a, MO b ) {
    const char *ptr = reinterpret_cast<const char *>( b.data );
    if ( ptr )
        std::fwrite( ptr, 1, std::strlen( ptr ), reinterpret_cast<FILE *>( a.data ) );
}

// OwcpString
void metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1( MO &a, MO b ) {
    Level1::OwcpStringData *o = reinterpret_cast<Level1::OwcpStringData *>( b.data );
    std::fwrite( o->ptr(), 1, o->size(), reinterpret_cast<FILE *>( a.data ) );
}

// const char * + size
void metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1( MO &a, MO b ) {
    const TypeConstructor_ConstCharPtrWithSize::Data *o = reinterpret_cast<const TypeConstructor_ConstCharPtrWithSize::Data *>( b.data );
    std::fwrite( o->data, 1, o->size, reinterpret_cast<FILE *>( a.data ) );
}

END_METIL_LEVEL1_NAMESPACE;
