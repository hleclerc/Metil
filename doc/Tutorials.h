/*! 
\page Tutorials Tutorials

    @section TutorialCompilation Compilation
    
        Let's start with a file named "my_first_example.cpp"
        
        \code
#include <Vec.h> // because we need vectors
using namespace Metil; // Metil user objects are defined in this namespace
int main() { // the classical entry point in C++
    Vec v( 1, 2, 4 ); // let s be a vector, containing the numbers 1, 2 and 4
    PRINT( mean( v ) );
}
        \endcode

        To compile and execute this file, type

        \code
metil_comp my_first_example.cpp
        \endcode
        
        The dependancies and the flags are automatically managed according to the data in the header files. For more information about @p metil_comp click @subpage MetilComp "here".

    @section TutorialFirstStep A first step with "low-level" fields

        Let continue with an application of minimization and field manipulation:

        \code
#include <Geo.h> // includes the Geo, Vec, Val, ... classes
using namespace Metil;
int main() {
    Geo g = new_RegularGrid( // let g be a regular grid
        Axes::space( 2 ), // on X and Y (dim=2)
        0, // the lower left corner is on ( 0, 0 )
        1, // the upper right corner is on ( 1, 1 )
        10 // the grid is divided by 10x10 nodes
    );
    Val f = g.new_Field(); // let f be an unidimensionnal field, based on the discretization of g
    Vec e = integration(
        pow( Axes::X * sin( Axes::Y ) - f, 2 )
        // By default, the integration are done on the more restrictive definition spaces
    ); // $f$ \int_g ( X - sin( Y )  - f )^2 $f$
    minimize( e, f ); // minimize e according to f
    display( f ); // display the resulting field on the screen
    PRINT( e ); // display the residual
}
        \endcode

        You will obtain a projection of \f$ x^2 sin( y ) \f$ in a regular grid.


    @section TutorialFirstMpi MPI, GPU

        Let ex2.cpp be the following program:

        \code
#include <Mat.h>
int main() {
    for(int n=1;n<=50;++n) {
        Mat m( n, n, ( _0 == _1 ) + 0.1 );
        PRINT( cond( m ) );
    }
}
        \endcode

        Here come some explanations for the example : @p _0 is a function that returns the first argument (_0(x,y,...)->x). @p _1 is a function that return the second one (_1(x,y,...)->y), meaning that <tt>( _0 == _1 ) + 0.1</tt> is a function equal to ( x, y ) -> 1.1 when x==y and 0.1 when x!=y. Besides If you construct a matrix using <tt>Mat m( nb_rows, nb_cols, function );</tt>, the values in the matrix will be equal to <tt>function( row, column )</tt>

        By default, this programm will execute in parallel on several threads if you have a multicore machine (even if it appears at a first sight to be a sequential program, at least with sequential I/O).

        But if you compile and execute with

        \code
metil_comp -mpi -np 10 -gpu -o ex1 -ne ex1.cpp
        \endcode

        the program will be executed on the 10 first machines specified in the lamboot command, using all the avalaible CPU and GPU cores.

        \par Constraints

            By default the scheduling of operations is automatic. In most of the cases, the heuristics are far better than the one that the standard users can do manually (because for example it is almost impossible to guess the real availability and amount of free memory of the machines during the compile time). If it's not the case, it is possible to specify where the data has to be loaded and where the operations should be done. Example :

            \code
for(int n=1;n<=50;++n) {
    Mat m( n, n, ( _0 == _1 ) + 1e-6 );
    Val c = cond( m );
    c.execute_on( machines[0].cpu );
    PRINT( c );
}
            \endcode

    @section symc Symbolic computing

        In this example

        \code
#include "Val.h"
int main() {
    Val x("x"), y("y");
    y = solve( sin( y ) - x, y ); // y depends on x
    PRINT( y.subs( x, 0.5 ) );
    PRINT( y.diff( x ) );
}
        \endcode

        one can see that it is possible to differentiate y by x because the solutions of the equation still depend on a symbolic variable.

        In the Metil platform, almost every object (vectors, matrices, ...) can become symbolic. To obtain a value or to change the symbolic dependencies, one can use the subs operator (with source and target values or with lists of source and target values).

        This ability is used during all the field manipulation procedures.

    @section fes Finite element simulation

        In the following example, we will solve a contact problem between two deformable elastic solids. Mesh data are read from ideas Universal Format (@p unv).

        \code
#include "Elasticity.h"
int main() {
    // the NEW operator is a fast and "secure" substitute of the C++ new operator
    // g1 will keep a reference on this object, and it will destroy it when it will stop to be accessible
    Geo g1 = NEW( Mesh, "toto.unv" );
    Geo g2 = NEW( Mesh, "tata.unv" );
    // Problem is a class to store problem descritions, i.e. boundary conditions, constitutive laws, ...
    Problem b;
    b.add_sst( g1, NEW( Elasticity, 210e9, 0.33 ) ); // add a substructure (volume) in the problem
    b.add_sst( g2, NEW( Elasticity,  72e9, 0.33 ) );
    b.add_int( g1, g2, NEW( ContactCoulomb, 0.7 ) ); // add an interface
    b.add_cst( g1[ Axes::X == 0 ] ); // add a constraint
    // by default, the solver is a Newton-Raphson. To see what solvers are used, you can look into the log files.
    b.solve();
}
        \endcode



*/
