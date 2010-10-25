#include "UnitTest.h" /// pour la macro UNIT_TEST( )

#include "String.h"

using namespace Metil;

bool String_0() {
        
    String s ("Errare ");
    String s2("humanum ");
    String s4 = s + s2 + "est.";
    return s4 == "Errare humanum est.";
}

bool String_1() {
        
    String s ("Au commencement, Dieu créa les cieux et la terre");
    s[43] = 's';
    PRINT( s );
    return s == "Au commencement, Dieu créa les cieux et la serre";
}

bool String_2() {
        
    String s ("Au commencement, Dieu créa les cieux et la terre");
    return s.size() == 49;
}

int main() {

    UNIT_TEST_WITH_LABEL( "operator+", String_0() );
    UNIT_TEST_WITH_LABEL( "operator[]", String_1() );
    UNIT_TEST_WITH_LABEL( "size", String_2() );
    return 0;
}



