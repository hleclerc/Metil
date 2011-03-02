#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "String.h"

BEG_METIL_NAMESPACE;

class HttpServer {
public:
    HttpServer();
    virtual ~HttpServer();
    bool run( int port );

    virtual void request( String &out, const String &addr, const String &post ) = 0;

private:
};

END_METIL_NAMESPACE;

#endif // HTTPSERVER_H
