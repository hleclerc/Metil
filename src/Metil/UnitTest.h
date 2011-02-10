#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>

#define UNIT_TEST_WITH_LABEL( name_proc, proc ) \
    try { std::cout << "\n" << __FILE__ << ":" << __LINE__ << ": __UNIT_TESTING_REPORT__ @@ " << name_proc << " @@ " << std::flush; bool res = ( proc );  std::cerr << std::flush; std::cout << ( res ? " >=>=>=> OK" : " >=>=>=> FAIL" ) << std::endl; } catch ( Abort ) { std::cout << " >=>=>=> FAIL" << std::endl; }

#define UNIT_TEST( proc ) \
    UNIT_TEST_WITH_LABEL( #proc, proc )

#define UNIT_TEST_CMP_STRING( EXPR, VAL ) UNIT_TEST_WITH_LABEL( std::string( #EXPR ) + " = " + #VAL, String( EXPR ) == #VAL )

#define UNIT_TEST_CMP_STRING_WITH_TEXT( TEXT, EXPR, VAL ) UNIT_TEST_WITH_LABEL( TEXT, String( EXPR ) == #VAL )

/// hum...
#define ERROR_UNIT_TEST( a , b ) std::abs( (a) - (b) ) / ( ((a) == 0) + ((b) == 0) + std::abs( a ) + std::abs( b ) )


#endif // UNITTEST_H
