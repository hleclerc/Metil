#include "HttpSessionServer.h"

BEG_METIL_NAMESPACE;

void HttpSessionServer::Session::request( String &out, const String &addr, const String &post ) {
    send_http_ok( out, "text/plain" );
    // read lines
    String post_ = post;
    while ( post_ ) {
        String line = post_.read_line();
        exec_cmd( out, line, post_ );
    }
}

void HttpSessionServer::Session::exec_cmd( String &out, const String &cmd, const String &post ) {
    ERROR( "exec_cmd must be redefined to use default method request." );
}

HttpSessionServer::HttpSessionServer( const String &page_dir ) : page_dir( page_dir ) {
}

void HttpSessionServer::request( String &out, const String &addr, const String &post ) {
    // static page
    if ( send_page( out, addr, page_dir ) )
        return;

    // new session
    if ( addr.begins_by( "/new_session?type=" ) ) {
        // type check
        String type = addr.end_from( 18 );
        if ( not factories.count( type ) ) {
            cerrn << "Error : no session of type " << type;
            return;
        }
        // response
        send_http_ok( out, "text/plain" );
        // find new session id
        while ( true ) {
            int i = rand();
            if ( not sessions.count( i ) ) {
                sessions[ i ] = factories[ type ]->create( type, post );
                out << i;
                return;
            }
        }
    }

    // command
    if ( addr.begins_by( "/cmd?session_id=" ) ) {
        // get session
        String session_id = addr.end_from( 16 );
        if ( not sessions.count( session_id ) ) {
            cerrn << "Session not active.";
            return;
        }

        // send commands
        Session *session = sessions[ session_id ].ptr();
        session->request( out, addr, post );
    }
}

void HttpSessionServer::add_factory( const String &name, Factory *factory ) {
    factories[ name ] = factory;
}


END_METIL_NAMESPACE;
