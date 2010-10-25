/*!

\page LazyEvaluation Lazy evaluation

    From the user point of view, the library exposes simple interoperable objects which can be used in a standard OOP fashion. Internally,
        - almost every user object is a smart pointer (with reference counting), possibly on object that are stored in (one or several) distant machines or GPU boards;
        - the execution of some operations can be delayed to allow several kinds of parallelism (multithread, CPU/GPU, MPI, ...),
        - and as almost every objects can be symbolic (e.g. scalars can be numbers or unknown values), it is possible to make automatic formal manipulations (differentiation, ...) and to express things in terms of constraint programming (e.g. let x be the minimum of ... such as ...).

    As debugging is an important part of the development process, everything has been made to obtain very short compilation duration time (even if metil is an "active library" meaning that it plays roles during the compilation phases).

    \section parallel Multithreading and parallelism
    
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

        By default, this programm will execute in parallel on several threads if you have a multicore machine (even if it appears at a first sight to be a sequential program, at least with sequential I/O).

        But if you compile and execute with
\code
metil_comp -mpi -np 10 -gpu -o ex1 -ne ex1.cpp
\endcode

        the program will be executed on the 10 first machines specified in the lamboot command, using all the avalaible CPU and GPU cores.

        Technically, almost every potentially expensive operation is described in a graph and the actual execution is postponed in order to extract parallelism between sub-tasks. It follows the principles of lazy evaluation.

        METIL is not SPMD, it is not invocated on various processors acting synchronously on different data, it is invocated once and one code supervises many processes and processors... The user has only to write a sequential program, but can specify the object are to be stored and manipulated. In all the cases, synchronisation is fully automatic (and uses internally semaphores and MPI instructions).

        One has to mention that lazy evaluation does not create parallelism. If one want for example to create sub-structure for a domain decomposition method, one have to describe what is a sub-structure, and it will have to contain separate vectors.

    \section Constraints

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

            In the Metil platform, almost every object can become symbolic (matrices, ...). To obtain a value or to change the symbolic dependencies, one can use the subs operator (with source and target values or with lists of source and target values).

            This ability is used during all the field manipulation procedures.


*/
