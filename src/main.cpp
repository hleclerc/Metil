#include "String.h"

using namespace Metil;

int main() {
    //    File f( "tmp", "w" );
    //    f << "a" << "b\n";
    String t = "1234";
    String u = t + "56";
    String v = u + "78";
    PRINT( v.c_str() );
}
