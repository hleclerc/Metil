#include <Img.h>
using namespace Metil;

int main() {
    BasicVec<ST,3> XS( 340, 340, 512 );
    Img f( "/home/leclerc/Data/ESRF_3a/3a_14N_0001.raw", S<PI8>(), XS );

}
