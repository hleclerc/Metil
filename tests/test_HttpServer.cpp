#include <Metil/HttpServer.h>
using namespace Metil;

struct MyHttpServer : public HttpServer {
    virtual void request( String &out, const String &addr, const String &post ) {
        PRINT( addr );
    }
};

int main() {
    MyHttpServer server;
    server.run( 12345 );
}

