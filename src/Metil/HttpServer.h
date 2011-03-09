#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "String.h"

BEG_METIL_NAMESPACE

class HttpServer {
public:
    HttpServer();
    virtual ~HttpServer();
    int run( int port );

    virtual void request( String &out, const String &addr, const String &post ) = 0;

    /// out << "HTTP/1.0 200 OK\n"...
    static void send_http_ok( String &out, const String &mime_type );

    /// try to send page defined in adress addr from directory dir.
    static bool send_page( String &out, const String &addr, const String &dir );
};

END_METIL_NAMESPACE;

#endif // HTTPSERVER_H
