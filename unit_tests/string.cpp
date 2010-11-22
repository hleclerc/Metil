#include "UnitTest.h" /// pour la macro UNIT_TEST( )
#include "String.h"

using namespace Metil;

bool add() {
    String s ( "Errare " );
    String s2( "humanum " );
    String s4 = s + s2 + "est.";
    return s4 == "Errare humanum est.";
}

//bool String_1() {
//    String s ("Au commencement, Dieu créa les cieux et la terre");
//    s[43] = 's';
//    PRINT( s );
//    return s == "Au commencement, Dieu créa les cieux et la serre";
//}

bool size() {
    String s ("Au commencement, Dieu créa les cieux et la terre");
    PRINT( s.size() );
    return s.size() == 49;
}

int main() {
    UNIT_TEST( add() );
    UNIT_TEST( size() );
    // UNIT_TEST_WITH_LABEL( "operator[]", String_1() );
    return 0;
}



