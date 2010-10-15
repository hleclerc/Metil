#include "TypeConstructor_Socket.h"
#include "StringHelp.h"
#include <sys/socket.h>

BEG_METIL_LEVEL1_NAMESPACE;

// del
void metil_def_del__when__a__isa__Socket__pert__1( MO &a ) {
}

// << const char *
void metil_def_self_append__when__a__isa__Socket__and__b__isa__ConstCharPtr__pert__1( MO &a, MO b ) {
    const char *ptr = reinterpret_cast<const char *>( b.data );
    if ( ptr )
        send( ST( a.data ), ptr, strlen( ptr ), 0 );
}

// write
void metil_def_write__when__a__isa__Socket__pert__1( MO &a, const void *data, ST size ) {
    send( ST( a.data ), data, size, 0 );
}

END_METIL_LEVEL1_NAMESPACE;
