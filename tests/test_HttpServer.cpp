#include <Metil/Hdf.h>
// #include <Metil/HttpServer.h>
using namespace Metil;

//struct MyHttpServer : public HttpServer {
//    virtual void request( String &out, const String &addr, const String &post ) {
//        PRINT( addr );
//    }
//};

int main() {
    Hdf hdf( "/home/leclerc/CorreliGpu/res/res.h5" );

    String val;
    hdf.read_tag( "f", "toto", val, false );
    PRINT( val );
//    MyHttpServer server;
//    server.run( 12346 );
}

