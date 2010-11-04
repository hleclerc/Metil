#include <Mat.h>
using namespace Metil;
using namespace Level1;

int main() {
    // Array<Val> a( 2 );
    //    PRINT( Val(1.5) );
    Mat a( 5, 6, type_ptr<float>() );

    //    for( int r = 0; r < 5; ++r )
    //        for( int c = 0; c < 6; ++c )
    //            a( r, c ) = r + c;
    //    PRINTN( a );
    //    PRINT( a( 0, 0 ) );
    PRINT( a.size() );
    //    m( 1, 0 ) = 666;
    //    m( 1, 2 ) = 666;
    //    PRINT( m( 1, 0 ) );
    //    PRINT( m );
    // Vec a( 5, 6 );
    // Val a( 10 ), b( 24 );
    // PRINT( a( 0 ) );
    // PRINT( a( 1 ) );
}
