#include <Img.h>
using namespace Metil;
using namespace Level1;

int main() {
    //    PRINT( Val( 1 ) && 0 );
    //    PRINT( Val( 1 ) && 1 );
    //    PRINT( zero && bool( 1 ) );
    //    Val a("a"), b("b");
    //    PRINT( a * zero );
    //    PRINT( zero * a );
    //    PRINT( a * one );
    //    PRINT( one * a );
    //    PRINT( a * minus_one );
    //    PRINT( minus_one * a );
    //    PRINT( a * 0 );
    //    PRINT( two * two );
    //    PRINT( 2 * two );
    Img a( "/old/leclerc/Code/CorrelationCPU/pied_d_aube/IMG_6196.tiff" );
    PRINT( a.sizes() );
}
