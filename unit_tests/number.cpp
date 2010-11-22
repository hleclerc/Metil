#include "UnitTest.h"
#include "String.h"

using namespace Metil;

//String python_expr( const String &expr ) {
//    FILE *p = popen( ( "python -c '" +  expr + "'" ).c_str(), "r" );
//    String res;
//    while ( not feof( p ) ) {
//        char c;
//        fread( &c, 1, 1, p );
//        if ( c == '\n' )
//            break;
//        res << c;
//    }
//    return res;
//}

int main() {
    //    UNIT_TEST_CMP_STRING( zero + 10, 10 );
    //    UNIT_TEST_CMP_STRING( 20 + zero, 20 );
    //    UNIT_TEST_CMP_STRING( zero - 10, -10 );
    //    UNIT_TEST_CMP_STRING( 20 - zero, 20 );

    //    UNIT_TEST_CMP_STRING( one + 10, 11 );
    //    UNIT_TEST_CMP_STRING( 20 + one, 21 );
    //    UNIT_TEST_CMP_STRING( one - 10, -9 );
    //    UNIT_TEST_CMP_STRING( 20 - one, 19 );

    //    UNIT_TEST_CMP_STRING( minus_one + 10, 9 );
    //    UNIT_TEST_CMP_STRING( 20 + minus_one, 19 );
    //    UNIT_TEST_CMP_STRING( minus_one - 10, -11 );
    //    UNIT_TEST_CMP_STRING( 20 - minus_one, 21 );

    //    UNIT_TEST_CMP_STRING( zero * 10, 0 );
    //    UNIT_TEST_CMP_STRING( 20 * zero, 0 );
    //    UNIT_TEST_CMP_STRING( one  * 10, 10 );
    //    UNIT_TEST_CMP_STRING( 20 * one, 20  );
    //    UNIT_TEST_CMP_STRING( minus_one * 10, -10 );
    //    UNIT_TEST_CMP_STRING( 20 * minus_one, -20 );

    //    UNIT_TEST_CMP_STRING( zero / 10, 0 );
    //    UNIT_TEST_CMP_STRING( one  / 10, 1/10 );
    //    UNIT_TEST_CMP_STRING( 20 / one, 20 );
    //    UNIT_TEST_CMP_STRING( minus_one / 10, -1/10 );
    //    UNIT_TEST_CMP_STRING( 20 / minus_one, -20 );

    //    UNIT_TEST_CMP_STRING( 10 >= zero, 1 );
    //    UNIT_TEST_CMP_STRING( zero >= 10, 0 );

    //    UNIT_TEST_CMP_STRING( zero + pi, pi );
    //    UNIT_TEST_CMP_STRING( pi + zero, pi );
    //    UNIT_TEST_CMP_STRING( zero - pi, -pi );
    //    UNIT_TEST_CMP_STRING( pi - zero, pi );
    //    UNIT_TEST_CMP_STRING( zero * pi, 0 );
    //    UNIT_TEST_CMP_STRING( pi * zero, 0 );
    //    UNIT_TEST_CMP_STRING( zero / pi, 0 );
    //    UNIT_TEST_CMP_STRING( pi / zero, nan );

    //    UNIT_TEST_CMP_STRING( one + pi, 1+pi );
    //    UNIT_TEST_CMP_STRING( pi + one, 1+pi );
    //    UNIT_TEST_CMP_STRING( one - pi, 1-pi );
    //    UNIT_TEST_CMP_STRING( pi - one, pi-1 );
    //    UNIT_TEST_CMP_STRING( one * pi, pi );
    //    UNIT_TEST_CMP_STRING( pi * one, pi );
    //    UNIT_TEST_CMP_STRING( one / pi, 1/pi );
    //    UNIT_TEST_CMP_STRING( pi / one, pi );

    //    UNIT_TEST_CMP_STRING( minus_one + pi, pi-1 );
    //    UNIT_TEST_CMP_STRING( pi + minus_one, pi-1 );
    //    UNIT_TEST_CMP_STRING( minus_one - pi, -1-pi );
    //    UNIT_TEST_CMP_STRING( pi - minus_one, pi+1 );
    //    UNIT_TEST_CMP_STRING( minus_one * pi, -pi );
    //    UNIT_TEST_CMP_STRING( pi * minus_one, -pi );
    //    UNIT_TEST_CMP_STRING( minus_one / pi, -1/pi );
    //    UNIT_TEST_CMP_STRING( pi / minus_one, -pi );

    //    UNIT_TEST_CMP_STRING( 0 + pi, pi );
    //    UNIT_TEST_CMP_STRING( 1 + pi, 1+pi );
    //    UNIT_TEST_CMP_STRING( 1 * pi, pi );
    //    UNIT_TEST_CMP_STRING( 2 * pi, 2*pi );

    //    // rat
    //    UNIT_TEST_CMP_STRING( Val(10) / 7 + Val(10) / 5, 24/7 );
    //    UNIT_TEST_CMP_STRING( - Val(10) / 7, -10/7 );
    //    UNIT_TEST_CMP_STRING( inv( Val(10) / 7 ), 7/10 );
    //    UNIT_TEST_CMP_STRING( inv( 1 / Val(10) ), 10 );
    //    UNIT_TEST_CMP_STRING( Val(10) / 7 >= 0, 1 );
    //    UNIT_TEST_CMP_STRING( Val(10) / 7 <= 0, 0 );
    //    UNIT_TEST_CMP_STRING( - Val(10) / 7 >= 0, 0 );
    //    UNIT_TEST_CMP_STRING( - Val(10) / 7 <= 0, 1 );

    //    // trigo
    //    UNIT_TEST_CMP_STRING( sin( 0 ), 0 );
    //    UNIT_TEST_CMP_STRING( sin( pi ), 0 );
    //    UNIT_TEST_CMP_STRING( sin( pi / 2 ), 1 );
    //    UNIT_TEST_CMP_STRING( sin( -pi ), 0 );
    //    UNIT_TEST_CMP_STRING( sin( 2 * pi ), 0 );

    //    UNIT_TEST_CMP_STRING( cos( 0  ), 1 );
    //    UNIT_TEST_CMP_STRING( cos( pi ), -1 );
    //    UNIT_TEST_CMP_STRING( cos( pi / 2 ), 0 );
    //    UNIT_TEST_CMP_STRING( cos( -pi ), -1 );
    //    UNIT_TEST_CMP_STRING( cos( 2 * pi ), 1 );

    //    UNIT_TEST_CMP_STRING( tan( pi ), 0 );
    //    UNIT_TEST_CMP_STRING( tan( -pi ), 0 );
    //    UNIT_TEST_CMP_STRING( tan( 2 * pi ), 0 );

    //    UNIT_TEST_CMP_STRING( acos( 0 ), pi/2 );
    //    UNIT_TEST_CMP_STRING( acos( 1 ), 0 );

    //    UNIT_TEST_CMP_STRING( acos( 1 ), 0 );

    return 0;
}
