#include <Img.h>
#include <Vec.h>
using namespace Metil;
using namespace Level1;

int main() {
    Img img( "/home/leclerc/Data/plateblanche/plateblanche001_0008.tif", MachineId::gpu( MachineId::cur(), 1 ) );
    PRINT( img.sizes() );
    PRINT( *img.machine_id() );
    // Img img( "/home/leclerc/Dic/Croix/toto000.tif" );
    // Vec v( T_FP64, 1, 7 );
    // Vec v( 1, 5 );
    // PRINT( v );
}
