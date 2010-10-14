#include "MetilServer.h"
#include "CudaMetil.h"
#include "System.h"

using namespace Metil;

int main() {
    cudaSetDevice( 1 );
    set_env( "PYTHONPATH", cur_dir() );

    MetilServer server( cur_dir() + "/pages" );
    for( int port = 12340; port < 12500; ++port )
        if ( server.run( port ) )
            return 0;
}
