/*!

\page MetilComp Compilation utilities (@p metil_comp)


@section MetilCompPrinciples Principles

    @p metil_comp is a small program to automate compilation, linking and execution of cpp files.

    To compile, link and execute @p file.cpp, simply type

\code
metil_comp file.cpp
\endcode

    @p metil_comp will automatically look for needed files:
        - if @p file.cpp includes @p some_file.h and there's a file named @p some_file.cpp in the same directory, @p metil_comp will add @p some_file.o and @p some_file.cpp to the dependencies
        - if in the @p *.h or in the @p *.cpp files, there's a line with @code #pragma lib_name a_lib_name @endcode, @metil_comp will add the library a_lib_name to the linker flags.

    Standards compile and link flags are passed normally in the command line. Example :
@code
metil_comp -O3 -g3 my_file.cpp
@endcode

@section MetilCompDebugging Debugging

    If you want to execute the code under gdb / valgrind supervision 
\code
metil_comp --gdb ex1.cpp # simply launch the executable using gdb
metil_comp --valgrind ex1.cpp # basic usage of valgrind
metil_comp --exec-using "valgrind --leak-check=full" ex1.cpp
\endcode

@section MetilCompAdvancedUsages Advanced usages

    List of useful flags:
        - @p -mpi : execute using mpi (using machines specified during the @p lamboot command)
        - @p -ne : do not launch the executable.
        - @p -nc : do not compile (launch the executable if @p -ne is not present)
        - @p -o @p file specify the name of the result (the executable or the library or ...).
        - @p -mex : create a Matlab mexglx file
        - @p -dylib : create a dynamic library (.so, .dll, ...), i.e. do not create an executable
        - @p -Iincludedir : append an include dir to the environnement
        - @p --exec-using prg : execute using prg. Example : --exec-using valgrind or --exec-using gdb to use valgrind or gdb
        - @p --valgrind : execute using valgrind
        - @p --gdb : execute using gdb
        - @p --device-emulation : device emulation for cuda
        - @p --maxrregcount n : device emulation for cuda
    
    Possible pragma in .h/.cpp/.cu files:";
        - @p src_file additionnal cpp / cu files"
        - @p cpp_path additionnal include path"
        - @p lnk_flag additionnal flags explicitly passed to the linker
        - @p gpu_flag additionnal flags explicitly passed to nvcc
        - @p lib_path additionnal library (.so/.a) path, like e.g. /usr/local/lib
        - @p lib_name additionnal library name (.so/.a), like e.g. pthread

*/
