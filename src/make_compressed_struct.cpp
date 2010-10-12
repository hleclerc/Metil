#include "StructCompactor.h"
#include "BasicMesh.h"
using namespace Metil;

int main() {
    BasicMesh m;
    StructCompactor s( m );
    s.make_files( "src" );
}
