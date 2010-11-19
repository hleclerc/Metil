#include <Vec.h>
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
    // PRINT( ST( minus_one ) );
    // PRINT( a );
    Vec a( Size(), 6, type_ptr<double>(), MachineId::gpu( MachineId::cpu( 0 ), 1 ) );
    //    for( int i = 0; i < a.size(); ++i )
    //        a[ i ] = i;
    // PRINT( a );
    // PRINT( a.sizes() );
}
