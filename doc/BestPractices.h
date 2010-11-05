/*! \page BestPractices Best practices

    \section BestPracticesSyntax Recommended syntax

        Following syntax is recommended:
            - Objects and methods should be named straighforwardly (using <tt>_</tt> to separate "words" in variables and upper case in classes).
            - Class names are written in uppercase (Ex: <tt>MetilObjectFinder</tt>), variables and methods are written in lowercase (ex; <tt>my_variables</tt>)
            - Bracket and parenthesis should be as in this exemple: <tt>my_function< param >( a, b[ 10, 5 ] )</tt>
            - Declaration should be in header (.h) files and implementation in cpp (.cpp) files
            - @p const should be used as much as possible, members should be protected as much as possible and accessed (if required) throught methods.
            - Metil object should be declared in the @p Metil namespace. Level1 functions should be declared in separate namespace or as static in classes.
            - Operator overiding should be compliant with standard notations (ex : + means plus and not shift, etc...).

        Functions done for specific and local use should be declared @p static.


    \section BestPracticesglobal_doc Global documentation
        This file is part of the global documentation, everytime a strategy is implemented, it should be described extensively and associated to examples.

    \section BestPracticesinline_doc Inline documentation

        The inline documentation is to be compliant with Doxygen.
            - Each file should begin with a short comment giving its logical coherence (what is the role of the pieces of code gathered in the same file).
            - Each class declaration should be associated with a short description of the role of the class.
            - Each method should be explained (aims/input/outputs).

        For example in a header file:
        \code 
// Algebraic projector defined by a basis of its image and its kernel
// The image is defined as the subspace orthogonal to a matrix
// if P is the projector on image=ker(C^T) parallel to kernel=im(G) 
// P = I - G (C^T G)C^T
class Projector {
public:
    Projector( Mat image, Mat kernel );
    
    void project( const Vec &in, Vec &out ) const;
    
protected: // attributes and protected or private members are at the end of the declaration
    Mat image, kernel; // refences to bases of subspaces
    Mat core; // matrix which has to be inverted (invertibility is associated to the supplementarity of subspaces)
};
        \endcode
        the associated cpp file contains:
        \code
Projector Projector::Projector( Mat image, Mat kernel ) : kernel( kernal ), image( image ) {
    core = transpose( image ) * kernel;
    core.factorize();
}

void Projector::product( const Vec &in, Vec &out ) { 
    out -= kernel * core.solve( transpose( image ) * in );
}
        \endcode

        \section BestPracticesAssertions Assertions
        
            Unit tests are meant to verify (when they are activated) small pieces of code, for instance previous method can be enriched by the following piece of code:
            
        \code
void Projector::product( const Vec &in, Vec &out ) { 
    out -= kernel * core.solve( transpose( image ) * in );
    ASSERT( norm( transpose( image ) * out ) < epsilon, "C^T P in != 0" ) ; \\ Checks that C^T P in = 0
}
        \endcode

        For more info on assertions, see \ref DebuggingRuntime "Debugging during the runtime".

    \section BestPracticesUnitTests Unit tests

        Everytime a feature is working (for instance import of a data-setting, export of a result, complex computation, ...), an example should be added to the tests database (in the git repository) which is run every night. The setting should be associated to a reference result to which the execution should be compared to.

        For example
        \code
#include <KrylovSolvers.h>
#include <UnitTest.h>
bool test_Krylov() {
    Mat K( Import( "mat_filename" ) );
    Vec F( Import( "rhs_filename") );
    Vec R( Import( "ref_filename") );
    
    Vec S;
    ConjugateGradient CG( K, F );
    CG.set_precision( 1e-6 );
    CG.set_preconditioner( Preconditioners::... );
    CG.solve( S );
    
    return norm_2( S - R ) < 1e-5;
}
int main() {
    UNIT_TEST( test_Krylov() );
}
        \endcode

        The results of comparisons are logged so that regressions are detected.

        For more information on unit tests, see @subpage UnitTesting "this page on unit testing".
*/
