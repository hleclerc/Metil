#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "TypeConstructor_Socket.h"
#include "OwcpStringData.h"
#include "../MetilString.h"
#include "StringHelp.h"
#include <sys/socket.h>

BEG_METIL_LEVEL1_NAMESPACE;

// del
void metil_def_del__when__a__isa__Socket__pert__1( MO &a ) {
}

// << const char *
void metil_def_self_append__when__a__isa__Socket__and__b__isa__ConstCharPtr__pert__2( MO &a, MO b ) {
    const char *ptr = reinterpret_cast<const char *>( b.data );
    if ( ptr )
        send( ST( a.data ), ptr, strlen( ptr ), 0 );
}

// << OwcpString
void metil_def_self_append__when__a__isa__Socket__and__b__isa__OwcpString__pert__2( MO &a, MO b ) {
    Level1::OwcpStringData *o = reinterpret_cast<Level1::OwcpStringData *>( b.data );
    send( ST( a.data ), o->ptr(), o->size(), 0 );
}

// << const char * + size
void metil_def_self_append__when__a__isa__Socket__and__b__isa__ConstCharPtrWithSize__pert__2( MO &a, MO b ) {
    const TypeConstructor_ConstCharPtrWithSize::Data *o = reinterpret_cast<const TypeConstructor_ConstCharPtrWithSize::Data *>( b.data );
    send( ST( a.data ), o->data, o->size, 0 );
}

// write
void metil_def_write__when__a__isa__Socket__pert__1( MO &a, const void *data, ST size ) {
    send( ST( a.data ), data, size, 0 );
}

END_METIL_LEVEL1_NAMESPACE;
