#include "Level1/StringHelp.h"
#include "HttpServer.h"
#include "BasicVec.h"
#include "System.h"
#include "Math.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>

#include <fastcgi.h>

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

static bool read_from_socket( int sd, char *ptr, int len ) {
    while ( len ) {
        ssize_t res = read( sd, ptr, len );
        if ( res < 0 )
            return false;
        len -= res;
        ptr += res;
    }
    return true;
}


static int find_n( const char *data, int size ) {
    for( int i = 0; i < size; ++i )
        if ( data[ i ] == '\n' )
            return i;
    return -1;
}

static int find_s( const char *data, int size ) {
    for( int i = 0; i < size; ++i )
        if ( data[ i ] == ' ' )
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

static bool read_get__requ( String &inp, int sd_current, String *extr = 0 ) {
    while ( true ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        if ( size <= 0 )
            return false;
        int poss = find_s( data, size );
        if ( poss >= 0 ) {
            inp  << String( NewString( data, data + poss ) );
            if ( extr )
                *extr << String( NewString( data + poss + 1, data + size ) );
            break;
        }
        inp << String( NewString( data, data + size ) );
    }
    return true;
}

static bool read_post_requ( String &inp, String &dat, int sd_current ) {
    // skip first space
    char data;
    if ( read( sd_current, &data, 1 ) <= 0 )
        return false;

    // read address
    String extr;
    if ( not read_get__requ( inp, sd_current, &extr ) )
        return false;

    // read length of post data
    int posc;
    while ( ( posc = extr.find( "Content-Length: " ) ) < 0 ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        if ( size < 0 )
            return false;
        extr << String( NewString( data, data + size ) );
    }
    const char *extr_c = extr.c_str() + posc + 16;
    ST length = String::read_int( extr_c );

    // find start of post data
    while ( not find_beg_post( extr_c ) ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        if ( size <= 0 )
            return false;
        extr << String( NewString( data, data + size ) );
        extr_c = extr.c_str();
    }

    // read post data
    dat = NewString( extr_c );
    length -= dat.size();
    while ( length > 0 ) {
        char data[ 1024 ];
        int size = read( sd_current, data, 1024 );
        if ( size <= 0 )
            return false;
        dat << String( NewString( data, data + size ) );
        length -= size;
    }
    return true;
}

static int get_fcgi_len( char *content_data, int &i ) {
    if ( content_data[ i ] >> 7 )
        return ((unsigned)( content_data[ i++ ] & 0x7F ) << 24 ) +
               ((unsigned)  content_data[ i++ ]          << 16 ) +
               ((unsigned)  content_data[ i++ ]          <<  8 ) +
               ((unsigned)  content_data[ i++ ]                );
    return content_data[ i++ ];
}

static void get_fcgi_param( String &inp, char *content_data, int content_size, const String &name ) {
    for( int i = 0; i < content_size; ++i ) {
        int name_len = get_fcgi_len( content_data, i );
        if ( name_len == 0 )
            break;
        int data_len = get_fcgi_len( content_data, i );
        if ( data_len == 0 )
            break;
        const char *p = content_data + i;
        //PRINT( String( NewString( p, p + name_len ) ) );
        //PRINT( String( NewString( p + name_len, p + name_len + data_len ) ) );
        if ( name == String( NewString( p, p + name_len ) ) ) {
            inp = NewString( p + name_len, p + name_len + data_len );
            return;
        }
        i += name_len + data_len;
    }
}

static bool write_to_socket( int socket_id, const char *ptr, int len ) {
    while ( len > 0 ) {
        int res = write( socket_id, ptr, len );
        if ( res < 0 )
            return false;
        len -= res;
        ptr += res;
    }
    return true;
}

static bool write_to_socket( int socket_id, const void *ptr, int len ) {
    return write_to_socket( socket_id, (const char *)ptr, len );
}

static void send_end_record( int socket_id, int request_id ) {
    FCGI_EndRequestRecord rec;
    rec.header.version         = 1;
    rec.header.type            = FCGI_END_REQUEST;
    rec.header.requestIdB1     = request_id >> 8;
    rec.header.requestIdB0     = request_id & 0x0F;
    rec.header.contentLengthB1 = 0;
    rec.header.contentLengthB0 = 8;
    rec.header.paddingLength   = 0;
    rec.header.reserved        = 0;

    rec.body.appStatusB3    = 0;
    rec.body.appStatusB2    = 0;
    rec.body.appStatusB1    = 0;
    rec.body.appStatusB0    = 0;
    rec.body.protocolStatus = FCGI_REQUEST_COMPLETE;

    write_to_socket( socket_id, &rec, sizeof rec );
}

static void send_out_record( int socket_id, int request_id, const char *ptr, int len ) {
    FCGI_Header rec;
    rec.version         = 1;
    rec.type            = FCGI_STDOUT;
    rec.requestIdB1     = request_id >> 8;
    rec.requestIdB0     = request_id & 0xFF;
    rec.reserved        = 0;

    while( true ) {
        int yop;
        if ( len > FCGI_MAX_LENGTH ) {
            rec.contentLengthB1 = 0xFF;
            rec.contentLengthB0 = 0xFF;
            rec.paddingLength   = 0;
            yop = 0xFFFF;
        } else {
            rec.contentLengthB1 = len >> 8;
            rec.contentLengthB0 = len & 0xFF;
            rec.paddingLength   = ceil( len, 8 ) - len;
            yop = len;
        }

        write_to_socket( socket_id,         &rec,        sizeof rec );
        write_to_socket( socket_id,          ptr,               len );
        write_to_socket( socket_id,   "        ", rec.paddingLength );

        if ( len == 0 )
            break;
        len -= yop;
        ptr += yop;
    }
}

static void send_out_record( int sd_current, int request_id, const char *ptr ) {
    send_out_record( sd_current, request_id, ptr, strlen( ptr ) );
}


struct FcgiRequest {
    FcgiRequest() : inp_ok( false ), dat_ok( false ) {}
    bool inp_ok;
    bool dat_ok;
    String inp;
    String dat;
};

bool HttpServer::handle_incoming_request( int sd_current ) {
    // read first 4 characters
    char data[ 4 ];
    if ( not read_from_socket( sd_current, data, 4 ) )
        return false;

    // GET
    if ( data[ 0 ] == 'G' and data[ 1 ] == 'E' and data[ 2 ] == 'T' and data[ 3 ] == ' ' ) { // GET
        String inp, dat;
        if ( read_get__requ( inp, sd_current ) ) {
            Socket out( sd_current );
            out << "HTTP/1.0 200 OK\n";
            request( out, inp, dat );
        }
        return true;
    }

    // POST
    if ( data[ 0 ] == 'P' and data[ 1 ] == 'O' and data[ 2 ] == 'S' and data[ 3 ] == 'T' ) {
        String inp, dat;
        if ( read_post_requ( inp, dat, sd_current ) ) {
            Socket out( sd_current );
            out << "HTTP/1.0 200 OK\n";
            request( out, inp, dat );
        }
        return true;
    }

    // FCGI
    std::map<int,FcgiRequest> fcgi_requests;

    FCGI_Header header;
    Level1::memcpy( &header, data, Number<4>() );
    if ( not read_from_socket( sd_current, (char *)&header + 4, sizeof( FCGI_Header ) - 4 ) )
        return false;

    while ( true ) {
        int request_id = ( header.requestIdB1 << 8 ) + header.requestIdB0;
        int content_length = ( header.contentLengthB1 << 8 ) + header.contentLengthB0;
        FcgiRequest &r = fcgi_requests[ request_id ];

        if ( not content_length ) {
            r.inp_ok |= header.type == FCGI_PARAMS;
            r.dat_ok |= header.type == FCGI_STDIN;
            if ( r.inp_ok and r.dat_ok ) {
                String out;
                request( out, r.inp, r.dat );
                send_out_record( sd_current, request_id, out.c_str(), out.size() );
                send_end_record( sd_current, request_id );

                fcgi_requests.erase( request_id );
                if ( not fcgi_requests.size() )
                    return true;
            }
        }

        // content
        BasicVec<char> content_data( Size(), content_length + header.paddingLength );
        if( not read_from_socket( sd_current, content_data.ptr(), content_data.size() ) )
            return false;

        // record
        if ( header.type == FCGI_PARAMS ) {
            get_fcgi_param( fcgi_requests[ request_id ].inp, content_data.ptr(), content_data.size(), "REQUEST_URI" );
        } else if ( header.type == FCGI_STDIN ) {
            fcgi_requests[ request_id ].dat << String( NewString( content_data.ptr(), content_data.ptr() + content_data.size() ) );
        }

        // read next header
        if ( not read_from_socket( sd_current, (char *)&header, sizeof( FCGI_Header ) ) )
            return false;
    }
    return true;
}

int HttpServer::run( int port ) {
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
        return 1;
    }

    // bind the socket to the port number
    int rb = bind( sd, (struct sockaddr *)&sin, sizeof sin );
    if ( rb == -1 )
        return 2;

    // show that we are willing to listen
    SC( listen( sd, 5 ) );
    while ( true ) {
        // wait for a client to talk to us
        socklen_t addrlen = sizeof( sockaddr_in );
        sockaddr_in pin;
        int sd_current = SC( accept( sd, (struct sockaddr *)&pin, &addrlen ) );

        // read input data. We assume that the message is ended by a void STDIN
        handle_incoming_request( sd_current );

        // close socket
        close( sd_current );
    }

    close( sd );
    return 0;
}

void HttpServer::send_http_ok( String &out, const String &mime_type ) {
    out << "HTTP/1.0 200 OK\n";
    if ( mime_type.size() )
        out << "Content-Type: " << mime_type << "\n";
    out << "\n";
}

bool HttpServer::send_page( String &out, const String &addr, const String &dir ) {
    if ( addr == "/" )
        return send_page( out, "index.html", dir );

    String file = dir + '/' + addr;
    if ( file_exists( file ) ) {
        if ( file.ends_with( ".js" ) )
            send_http_ok( out, "text/javascript" );
        else if ( file.ends_with( ".html" ) )
            send_http_ok( out, "text/html" );
        else if ( file.ends_with( ".css" ) )
            send_http_ok( out, "text/css" );
        else if ( file.ends_with( ".png" ) )
            send_http_ok( out, "image/png" );
        else if ( file.ends_with( ".jpg" ) )
            send_http_ok( out, "image/jpg" );
        else
            send_http_ok( out, "text/plain" );

        File fout( file );
        ST size = fout.size();
        out.write( fout.c_str(), size );
        return true;
    }
    return false;
}

END_METIL_NAMESPACE;
