#include "HttpServer.h"
#include "System.h"

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

static bool find_beg_post( const char *&extr_c ) {
    for( ; *extr_c; ++extr_c ) {
        if ( extr_c[ 0 ] == '\n' ) {
            if ( extr_c[ 1 ] == '\r' and extr_c[ 2 ] == '\n' ) {
                extr_c += 3;
                return true;
            } else if ( extr_c[ 1 ] == '\n' ) {
                extr_c += 2;
                return true;
            }
        }
    }
    return false;
}


static bool read_requ( String &inp, String &dat, int sd_current ) {
    // read first line
    String line, extr;
    while ( true ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        if ( size == 0 ) return false;
        int posn = find_n( data, size );
        if ( posn >= 0 ) {
            line << String( NewString( data, data + posn ) );
            extr << String( NewString( data + posn + 1, data + size ) );
            break;
        }
        line << String( NewString( data, data + size ) );
    }

    // analyze first line
    const char *l = line.c_str();
    if ( line.begins_by( "GET " ) ) {
        int poss = find_s( l + 4 );
        if ( poss >= 0 )
            inp = NewString( l + 4, l + 4 + poss );
    } else if ( line.begins_by( "POST " ) ) {
        int poss = find_s( l + 5 );
        if ( poss >= 0 )
            inp = NewString( l + 5, l + 5 + poss );

        // read length of post data
        int posc;
        while ( ( posc = extr.find( "Content-Length: " ) ) < 0 ) {
            char data[ 1024 ];
            int size = read( sd_current, data, 1024 );
            if ( size == 0 ) return false;
            extr << String( NewString( data, data + size ) );
        }
        const char *extr_c = extr.c_str() + posc + 16;
        ST length = String::read_int( extr_c );

        // find start of post data
        while ( not find_beg_post( extr_c ) ) {
            char data[ 1024 ];
            int size = read( sd_current, data, 1024 );
            if ( size == 0 ) return false;
            extr << String( NewString( data, data + size ) );
            extr_c = extr.c_str();
        }

        // read post data
        dat = NewString( extr_c );
        length -= dat.size();
        while ( length > 0 ) {
            char data[ 1024 ];
            int size = read( sd_current, data, 1024 );
            if ( size == 0 ) return false;
            dat << String( NewString( data, data + size ) );
            length -= size;
        }
    } else {
        PRINT( line );
        PRINT( extr );
        return false;
    }

    return true;
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

void HttpServer::send_http_ok( String &out, const String &mime_type ) {
    out << "HTTP/1.0 200 OK\n";
    out << "Content-Type : " << mime_type << "\n";
    out << "\n";
}

bool HttpServer::send_page( String &out, const String &addr, const String &dir ) {
    if ( addr == "/" )
        return send_page( out, "index.html", dir );

    String file = dir + '/' + addr;
    if ( file_exists( file ) ) {
        send_http_ok( out, "text/HTML" );

        File fout( file );
        out << fout.c_str();
        return true;
    }
    return false;
}

END_METIL_NAMESPACE;
