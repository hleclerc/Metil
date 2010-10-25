/*! \page GenericConsiderations Generic considerations

    @section GenericPrinciples Principles 
    
        Metil is a set of libraries (@p so) and C++ source files (@p h @p cpp).

        It contains modules for:
            - @subpage LinearAlgebra (vectors, matrices, direct or iterative solvers, ...),
            - @subpage FieldManipulation (unstructured meshes, n-dimensionnal images, level-sets, ...),
            - @subpage Visualization (OpenGL, PDF, paraview I/O, ...),
            - Tools to describe and solve @subpage ProblemDefinition "mechanical, physical or mathematical problems" (Newton-Raphson, Domain Decomposition, spatio-temporal analysis, ...)
            - @subpage SymbolicComputing (integration, roots, optimized code generation, ...),
            - @subpage LazyEvaluation "automatic parallelisation and memory management" (helpers for MPI, qmultithreads, ...),
            - @subpage CodeGeneration to adress "foreign" platforms or hardwares (GPU, ..),
            - @subpage MetilComp "C++ compilation", strings, I/O streams (files, pipes, sockets, ...)
            - Image manipulation (I/O, optimized filters, ...), ...

        From the user point of view, the library exposes simple interoperable objects which can be used in a standard OOP fashion.

        As debugging is an important part of the development process, everything has been made to obtain very short compilation duration time (even if metil is an "active library" meaning that it plays an important role during the compilation phases).
        
        Internally,
            - almost every user object is a smart pointer (with reference counting), possibly on objects that are stored in (one or several) distant machines or GPU boards;
            - the execution of some operations can be delayed to allow several kinds of parallelism (multithread, CPU/GPU, MPI, ...) and memory management algorithms (out-of-core, cache management...),
            - and as almost every objects can become symbolic (e.g. scalars can be numbers or unknown values), it is possible to make automatic formal manipulations (differentiation, ...) and to express things in terms of constraint programming (e.g. let x be the minimum of ... such as ...).

    @section copyright Copyright and License

        The main objects are released under the LGPLv2 licence. Click @subpage Licenses "this link" for more information.

    @section Objective Objective

        The objective of Metil is to provide a framework for easy coding in C++ of high level computational methods (primaly dedicated to mechanical modeling and simulations).
        
        Basic requirement to program high level methods for intensive computing are :
            - stable paradigms and interfaces,
            - easy access (assuming C++ syntax and basic OOP concepts are known), 
            - ease of debugging,
            - tutorials and demonstrations,
            - code reusability,
            - prevention of regressions,
            - good compromise between genericity and optimality (specialization),
            - high level objects with rich interface,
            - perenity ensurements (unit tests + base de test),
            - possibility to demonstrate the method on adapted industrial problems,
            - fine adaptation to hardware.

    @section basic_organisation Basic organisation
    
        The Metil project is available in a @ref GettingTheSources "git repository".
        
        Basically the project tree contains sources, extra documentations and use-cases. The sources include the whole documentation (in a doxygen format), @subpage UnitTesting "unit-tests", @subpage Tutorials and @subpage Examples. Unit-tests are meant to validate small pieces of code and they can be included inside the production code as they can be activated on demand (during for example the nightly verifications) :
\code 
// if P is a projector onto Ker( C )
y = P * x ; // the production normal code
UNIT_TEST( norm( C * y ) < 1e-6 ); // check
\endcode

        The use-cases gather examples of what the code is currently able to do, they also contain reference solutions so that regression can be easily detected. Indeed every night the use-cases are executed (with activated unit-tests) and their outputs are compared to the references.

    @section principle Principle of use
    
        The entry point is a necessarily a C++ file, which refers to metil's files thanks to @p #include statements.

        Compilation is assisted through a small program named @subpage MetilComp "metil_comp" which basically detects dependencies, compiles convenient files (if needed), links the whole thing and execute the program (under the supervision of a debugger like gdb or valgrind, if needed). This organization implies that if the C++ data setting is modified, recompilation is required but since in most of the cases, few files need recompiling, time is not an issue. One advantage of starting from this kind of entry point (compared e.g. to a XML file) is to permit to run complex simulations (including loops over different data setting, use of if statements). It avoids the learning of a (poorly embedded in most of the cases) script language (which is now a feature classically added on top of FE software).

    @section code_generation Code generation
 
        Increasing @em productivity is the very first goal of Metil.
        
        It means that each time a transformation can be managed by the computer, we try to alleviate the work of the user. But... it would not be a good solution if it slowed down the compilation.
 
        Actually, in most of the cases, automatic transformation of high-level descriptions leads to better results compared to what mainstream developper would do, du to "optimized code generation".


        As side effects, the consequences are:
            - Code can be ported to various platforms. For instance behaviors can be described using state and dissipation potentials, and computations ran on the platform or Abaqus UMAT can be created.
            - Code can be (almost) automatically ported to various hardwares, including GPUs.
            - Code can use complicated but powerfull COU instructions (SSE2, ...).
            
        Code generation is used for example for @subpage FieldManipulation "field manipulations", image filtering, ...
        
        See @subpage CodeGeneration "this link" for more information about this subject.


*/
