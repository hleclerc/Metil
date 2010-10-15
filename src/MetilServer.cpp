#include "MetilSession.h"
#include "MetilServer.h"
#include "StringHelp.h"
#include "BasicVec.h"
#include "Tokenize.h"
#include "System.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

#ifdef METIL_COMP_DIRECTIVE
#pragma cpp_path /usr/include/python2.6/
#pragma lib_name python2.6
#endif // METIL_COMP_DIRECTIVE
extern "C" {
    #include <Python.h>
}

BEG_METIL_NAMESPACE;

static int sig_installed = 0;
static BasicVec<int> sockets_to_close;

void sig_func( int sig ) {
    if ( sig == SIGSEGV )
        fprintf( stderr, "SIGSEGV !" );
    for( int i = sockets_to_close.size() - 1; i >= 0; --i )
        close( sockets_to_close[ i ] );
    abort();
}

int socket_check( int v, const char *file, int line ) {
    if ( v == -1 ) {
        fprintf( stderr, "in %s, %i, ", file, line );
        perror( file );
        exit( 1 );
    }
    return v;
}

#define SC( f ) socket_check( f, __FILE__, __LINE__ )


MetilServer::MetilServer( const String &base_dir ) : base_dir( base_dir ) {
}

MetilServer::~MetilServer() {
    for( std::map<int,MetilSession *>::iterator iter = sessions.begin(); iter != sessions.end(); ++iter )
        delete iter->second;
}

static String read_word( const char *&msg ) {
    while ( Level1::is_a_space( *msg ) )
        ++msg;
    const char *beg = msg;
    while ( not Level1::is_a_space( *msg ) )
        ++msg;
    return NewString( beg, msg );
}

bool MetilServer::run( int port ) {
    // signals to close the socket
    if ( not sig_installed ) {
        signal( SIGINT , sig_func );
        signal( SIGSEGV, sig_func );
        sig_installed = true;
    }

    // get an internet domain socket
    int sd = SC( socket( PF_INET, SOCK_STREAM, 0 ) );
    sockets_to_close << sd;

    // complete the socket structure
    sockaddr_in sin;
    memset( &sin, 0, sizeof sin );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port = htons( port );

    // bind the socket to the port number
    int rb = bind( sd, (struct sockaddr *)&sin, sizeof sin );
    if ( rb == -1 )
        return false;

    PRINT( port );

    // show that we are willing to listen
    SC( listen( sd, 100 ) );

    // exec_cmd( "chromium-browser --app=http://localhost:" + String( port ) + " &" );
    Metil::exec_cmd( "firefox -jsconsole http://localhost:" + Metil::String( port ) + " &" );

    //
    Py_Initialize();
    PyRun_SimpleString("from StringIO import StringIO\n"
                       "import sys\n" );


    while ( true ) {
        // wait for a client to talk to us
        socklen_t addrlen = sizeof( sockaddr_in );
        sockaddr_in pin;
        int sd_current = SC( accept( sd, (struct sockaddr *)&pin, &addrlen ) );
        sockets_to_close << sd_current;

        // what the client wants from us
        String msg;
        while ( true ) {
            char tmp[ 4096 ];
            ssize_t r = recv( sd_current, tmp, sizeof tmp, 0 );
            msg << String( NewString( tmp, tmp + r ) );
            if ( r <= ssize_t( sizeof( tmp  ) ) )
                break;
        }
        // PRINT( msg );

        // GET / POST ? -> addr
        String addr, type;
        const char *msg_ = msg.c_str();
        if ( strncmp( msg_, "GET ", 4 ) == 0 ) {
            type = "GET";
            addr = read_word( msg_ += 4 );
        } else if ( strncmp( msg_, "POST ", 5 ) == 0 ) {
            type = "POST";
            addr = read_word( msg_ += 4 );
        }

        // data
        String data;
        for ( ; ; ++msg_ ) {
            if ( msg_[ 0 ] == '\n' and msg_[ 1 ] == '\n' ) {
                data = NewString( msg_ + 2 );
                break;
            }
            if ( msg_[ 0 ] == '\r' and msg_[ 1 ] == '\n' and msg_[ 2 ] == '\r' and msg_[ 3 ] == '\n' ) {
                data = NewString( msg_ + 4 );
                break;
            }
        }

        // get_page
        get_page( addr, data, sd_current );

        // end of socket
        sockets_to_close.remove_first( sd_current );
        close( sd_current );
        if ( addr == "/exit.html" )
            break;
    }

    Py_Finalize();
    sockets_to_close.remove_first( sd );
    close( sd );

    return true;
}
void disp_js( String &txt, String &out ) {
    for( const char *c = out.c_str(); *c; ++c ) {
        if ( *c == '\n' )
            txt << "\\n";
        else if ( *c == '\'' )
            txt << "\\'";
        else if ( *c != '\r' )
            txt << *c;
    }
}

static void append_content_type( String &os, const String &addr ) {
    if ( addr.ends_with( ".html" ) )
        os << "Content-Type: text/html\r\n";
    else if ( addr.ends_with( ".js" ) )
        os << "Content-Type: text/javascript\r\n";
    else if ( addr.ends_with( ".css" ) )
        os << "Content-Type: text/css";
    else
        os << "Content-Type: text/plain\r\n";
}

bool MetilServer::get_page( String addr, String data, int sd_current ) {
    if ( addr == '/' )
        return get_page( "/index.html", data, sd_current );

    if ( addr == "/exec.py" ) {
        const char header[] =
                "HTTP/1.0 200 Ok\r\n"
                "Content-Type: text/javascript\r\n"
                "\r\n";
        send( sd_current, header, sizeof( header ) - 1, 0 );


        // prepare python environment
        PyObject *pName = PyString_FromString("__main__");
        PyObject *pModule = pName ? PyImport_Import( pName ) : 0;
        PyObject *pSocketId = PyInt_FromLong( sd_current );
        if( pModule )
            PyObject_SetAttrString( pModule, "socket_id", pSocketId );

        PyRun_SimpleString(
            "sys.stdout = StringIO()\n"
            "sys.stderr = StringIO()\n"
        );

        // execution
        PyRun_SimpleString( data.c_str() );
        if ( PyErr_Occurred() )
            PyErr_Print();

        // get stdout / stderr / js_out
        PyRun_SimpleString(
            "__stdout__ = sys.stdout.getvalue()\n"
            "__stderr__ = sys.stderr.getvalue()\n"
        );

        // get result
        PyObject *pOut = pModule ? PyObject_GetAttrString( pModule, "__stdout__" ) : 0;
        PyObject *pErr = pModule ? PyObject_GetAttrString( pModule, "__stderr__" ) : 0;
        String out = NewString( pOut ? PyString_AsString( pOut ) : "" );
        String err = NewString( pErr ? PyString_AsString( pErr ) : "" );
        Py_DECREF( pErr );
        Py_DECREF( pOut );

        // returned javascript program
        String txt;
        txt << "c.out = '";
        disp_js( txt, out );
        txt << "';\r\n";
        txt << "c.err = '";
        disp_js( txt, err );
        txt << "';\r\n";
        send( sd_current, txt.c_str(), ST( txt.size() ), 0 );

        Py_DECREF( pSocketId );
        Py_DECREF( pModule );
        Py_DECREF( pName );
        return true;
    }

    // by default, send html / js / ... pages
    String content;
    File page( base_dir + addr, "r" );
    if ( page ) {
        content << "HTTP/1.0 200 Ok\r\n";
        append_content_type( content, addr );
        content << "\r\n";
        content << page.c_str();
    } else {
        PRINT( base_dir + addr );
        content << "HTTP/1.0 404 Not Found\r\n";
        content << "\r\n";
    }
    send( sd_current, content.c_str(), (ST)content.size(), 0 );
    return true;
}

END_METIL_NAMESPACE;

