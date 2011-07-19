#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "String.h"

BEG_METIL_NAMESPACE;

/**
  each time a Http or a Fcgi request is received, the function request is called
*/
class HttpServer {
public:
    HttpServer();
    virtual ~HttpServer();

    int run( int port );

    virtual void onready( int num_port ) {} ///< called when the socket is ready
    virtual void onclose() {} ///< after a transmission
    virtual void request( String &out, const String &addr, const String &post ) = 0;

    static void send_http_ok( String &out, const String &mime_type ); ///< out << "HTTP/1.0 200 OK\n"...
    static bool send_page( String &out, const String &addr, const String &dir ); ///< try to send page defined in adress addr from directory dir.

protected:
    bool handle_incoming_request( int sd_current );
};

END_METIL_NAMESPACE;

#endif // HTTPSERVER_H
