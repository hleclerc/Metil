#include <Metil/HttpSessionServer.h>
using namespace Metil;

struct MySessionType : HttpSessionServer::Session {
    struct Factory : HttpSessionServer::Factory {
        virtual Session *create( const String &type, const String &post ) const { return NEW( MySessionType ); }
    };

    virtual void exec_cmd( String &out, const String &cmd , const String &post ) {
        PRINT( cmd );
    }

};


int main() {
    HttpSessionServer server;
    server.add_factory( "test", NEW( MySessionType::Factory ) );

    system( "python tests/test_HttpSessionServer.py &" );
    server.run( 10000 );
}


