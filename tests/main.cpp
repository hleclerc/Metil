#include <Img.h>
using namespace Metil;

int main() {
    Vec XS( 340, 340, 512 );
    Img f( "/home/leclerc/Data/ESRF_3a/3a_14N_0001.raw", S<PI8>(), XS );

    //BasicVec<Img> img;

    PRINT( f.sizes() );
}
