#include <Metil/HttpServer.h>
using namespace Metil;

struct MyHttpServer : public HttpServer {
    virtual void request( String &out, const String &addr, const String &post ) {
        if ( addr == "/" ) {
            out << "HTTP/1.0 200 OK\n";
            out << "Content-Type : text/HTML\n";
            out << "\n";

            File f( "tests/test_HttpServer.html" );
            out << f.c_str();
        } else if ( addr == "/test" ) {

        }
        PRINT( addr );
        PRINT( post );
    }
};

int main() {
    MyHttpServer server;
    server.run( 12345 );
}

