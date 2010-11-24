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
    // Vec v( S<double>(), 1, 2 );
    // Img a( "/home/leclerc/Data/grad.tif" ); // plateblanche/plateblanche001_0121.tif
    // PRINT( a.sizes() );
    Vec a( 1, 2 );
    PRINT( a );
    //PRINT( "54" );

    // MachineId::cur()->gpu( 0 )
    // PRINT( a.sizes() );

    //    File f( "res.m", "w" );
    //    f << "m = [";
    //    for( int x = 0; x < 500; ++x )
    //        f << " " << a( x, 0 );
    //    f << "];";
    // PRINT( a.size_in_mem() );
}
