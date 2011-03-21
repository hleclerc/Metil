#include <Metil/HashSet.h>
#include <Metil/String.h>
using namespace Metil;

struct H { int operator()( int a ) const { return a; } };
struct E { bool operator()( int a, int b ) const { return a == b; } };

int main() {
    HashSet<int,H,E,512> h;
    h.set_item( 10 );
    h.set_item( 20 );

    PRINT( h.get_item(  5 ) );
    PRINT( h.get_item( 10 ) );
}
