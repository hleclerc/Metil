#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "Metil/String.h"

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
    String s ( "Au commencement, Dieu créa les cieux et la terre" );
    PRINT( s.size() );
    return s.size() == 49;
}

BOOST_AUTO_TEST_SUITE()

    BOOST_AUTO_TEST_CASE( Test1 ) {
        BOOST_REQUIRE_EQUAL( add() , true );
    }

    BOOST_AUTO_TEST_CASE( Test2 ) {

        BOOST_REQUIRE_EQUAL( size() , true );
    }

BOOST_AUTO_TEST_SUITE_END()





