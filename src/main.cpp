#include "String.h"

using namespace Metil;
using namespace Level1;

int main() {
    // String a, b;
    // a.type->add[ b.type->number ]( a, b );
    // a.type->del( a );
    // DefStr d( "metil_def_add__when__a__isa__VoidString__and__b__isa__VoidString" );
    // DOUT( d.cond() );
    String a;
    a << "a" << "b\n";

    cout << a;
}
