#include "HttpServer.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


BEG_METIL_NAMESPACE;

static int socket_check( int v, const char *file, int line ) {
    if ( v == -1 ) {
        fprintf( stderr, "in %s, %i, ", file, line );
        perror( file );
        exit( 1 );
    }
    return v;
}
#define SC( f ) socket_check( f, __FILE__, __LINE__ )



HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

static int find_n( const char *data, int size ) {
    for( int i = 0; i < size; ++i )
        if ( data[ i ] == '\n' )
            return i;
    return -1;
}

static int find_s( const char *data ) {
    for( int i = 0; data[ i ]; ++i )
        if ( data[ i ] == ' ' )
            return i;
    return -1;
}

static void read_requ( String &inp, String &dat, int sd_current ) {
    // read first line
    String line, extr;
    while ( true ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        int posn = find_n( data, size );
        if ( posn >= 0 ) {
            line << String( NewString( data, data + posn ) );
            extr << String( NewString( data + posn + 1, data + size ) );
            break;
        }
        line << String( NewString( data, data + size ) );
    }

    // analyze first line
    if ( line.begins_by( "GET " ) ) {
        const char *l = line.c_str();
        int poss = find_s( l + 4 );
        if ( poss >= 0 )
            inp = NewString( l + 4, l + 4 + poss );
    }
    // PRINT( extr );

    //

//    String extr;
//    for( bool cont = true; cont; ) {
//        char data[ 1024 ];
//        int len = read( sd_current, data, sizeof data );
//        for( int i = 0; i < len; ++i ) {
//            if ( data[ i ] == '\n' ) {
//                line << String( NewString( data, data + i ) );
//                extr << String( NewString( data + i + 1, data + len ) );
//                if ( line.begins_by( "GET" ) ) {

//                    cont = false;
//                } else {
//                    PRINT( line );
//                    PRINT( extr );
//                }
//                break;
//            }
//        }
//    }
}

bool HttpServer::run( int port ) {
    // get an internet domain socket
    int sd = SC( socket( PF_INET, SOCK_STREAM, 0 ) );

    // complete the socket structure
    sockaddr_in sin;
    memset( &sin, 0, sizeof sin );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port = htons( port );

    int yes = 1;
    // lose the pesky "Address already in use" error message
    if ( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == -1 ) {
        perror( "setsockopt" );
        exit( 1 );
    }

    // bind the socket to the port number
    int rb = bind( sd, (struct sockaddr *)&sin, sizeof sin );
    if ( rb == -1 )
        return false;

    // show that we are willing to listen
    SC( listen( sd, 5 ) );
    while ( true ) {
        // wait for a client to talk to us
        socklen_t addrlen = sizeof( sockaddr_in );
        sockaddr_in pin;
        int sd_current = SC( accept( sd, (struct sockaddr *)&pin, &addrlen ) );

        // read input data. We assume that the message is ended by a void STDIN
        String inp, dat;
        read_requ( inp, dat, sd_current );

        // request
        Socket out( sd_current );
        request( out, inp, dat );

        // close socket
        close( sd_current );
    }

    close( sd );
    return true;
}

END_METIL_NAMESPACE;
