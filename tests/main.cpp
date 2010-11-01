#include <Mat.h>
using namespace Metil;
using namespace Level1;

void f( Mat &m ) {
    m( 1, 0 ) = 666;
    m( 1, 2 ) = 666;
    PRINT( m( 1, 0 ) );
    PRINT( m );
}

int main() {
    // Array<Val> a( 2 );
    Mat a( 5, 6 );
    f( a );
    // Vec a( 5, 6 );
    // Val a( 10 ), b( 24 );
    // PRINT( a( 0 ) );
    // PRINT( a( 1 ) );
}
