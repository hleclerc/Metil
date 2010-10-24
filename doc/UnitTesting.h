/*!

\page UnitTesting Unit testing

@ref UnitTestingResults "Link to the results of the preceding build" (test version).

@section UnitTestingHowTo How to define tests

    Unit testing in Metil is fundamental because if a change from the test repository (<tt>gitosis:met_test</tt>) causes at least one of the unit tests to fail, the corresponding patches won't be sent to the production repository (<tt>gitosis:met</tt>).

    The units tests are located in the directory @p unit_tests. It contains independant @p cpp files which use the @p UNIT_TEST macro as in:
    
    @code
#include <UnitTest.h>
#include <String.h>

using namespace Metil;

bool test_String_addition() {
    String s1("Errare ");
    String s2("humanum ");
    return s1 + s2 + "est." == "Errare humanum est.";
}

int main() {
    UNIT_TEST( test_String_addition() );
}
    @endcode

    Each night, @em all the @p cpp files in the directory @p unit_tests of the repository @p met_test are compiled and executed. A report is then generated and if and only if @em all the unit tests are OK, the patches from the repository @p met_test are sent to the main repository.

@section UnitTestingResults Results of the preceding build (test version)

@htmlinclude unit_tests/report.html

*/
