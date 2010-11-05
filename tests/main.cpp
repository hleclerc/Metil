#include <Level1/CompilationCppParser.h>
using namespace Metil;
using namespace Level1;

#ifdef TOTO
pouet
#endif

int main() {
    //    Val a( "a" ), b( "b" );
    //    Val s = a + b;
    //    PRINT( s );
    //    s.display_dot();
    // PRINT( a + b );
    // PRINT( a + 2 );
    // Img img( "/home/leclerc/Data/plateblanche/plateblanche001_0008.tif" );
    // PRINT( img.sizes() );
    CompilationEnvironment ce;
    ce.make_exe( "out", "/home/leclerc/Metil/examples/Hello_world.cpp" );
}
