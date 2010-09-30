#include "String.h"

using namespace Metil;
using namespace Level1;

namespace Metil {
    namespace Level1 {
        MO metil_def_add__VoidString_VoidString( MO a, MO b ) {
            DOUT( __LINE__ );
            return MO();
        }
    }
}

int main() {
    String a, b;
    //    // a.type->del( a );
    a.type->add[ b.type->number ]( a, b );
}
