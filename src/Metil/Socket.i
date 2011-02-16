%{
    #include "String.h"
%}

namespace Metil {
    struct Socket {
        Socket( int socket_id );
    };
    %extend Socket {
        void write( const char *data ) { *self << data; }
        void write( const char *data, int size ) { self->write( data, size ); }
    };
}
