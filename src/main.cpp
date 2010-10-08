#include "String.h"
#include "Tokenize.h"

using namespace Metil;

int main() {
    String t = NewString( "Level::" );
    PRINT( t.replace( "::", "__" ) );
}
