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

static void read_requ( String &inp, String &dat, int sd_current ) {
    char data[ 1024 ];
    String line;
    while ( true ) {
        int len = read( sd_current, data, sizeof data );
    }

    if (  ) {
    }

//    while ( true ) {
//        for( int i = 0; i < len + 1; ++i )
//            PRINT( int( data[ i ] ) );
//        inp << String( NewString( data, data + len ) );
//        break;
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
    PRINT( rb );
    if ( rb == -1 )
        return false;
    PRINT( port );

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
        PRINT( inp );

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
