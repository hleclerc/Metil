#include <Metil/HttpServer.h>
using namespace Metil;

struct MyHttpServer : public HttpServer {
    virtual void request( String &out, const String &addr, const String &post ) {
        if ( addr == "/" or addr == "/img_server_00" ) {
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
    server.run( 10000 );
}

