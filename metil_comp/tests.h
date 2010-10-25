#include <iostream>

#include <File.h>


#define UNIT_TEST( proc ) \
    { std::cout << "\n__UNIT_TESTING_REPORT__  " << #proc; int res = proc; std::cout << " >=>=>=> " << ( res ? "FAIL\n" : "OK\n" ); }

#define ERROR_UNIT_TEST( a , b ) std::abs( (a) - (b) ) / ( ((a) == 0) + ((b) == 0) + std::abs( a ) + std::abs( b ) )
