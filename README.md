`metil_comp` is a small program to automate compilation, linking and execution of cpp files.

To compile, link and execute `file.cpp`, simply type `metil_comp file.cpp`. `metil_comp` will automatically look for the needed files:
    - if `file.cpp` includes `some_file.h` and there's a file named `some_file.cpp` in the same directory, `metil_comp` will add `some_file.o` and `some_file.cpp` to the dependencies
    - if in the `*.h` or in the `*.cpp` files, there's a line with `#pragma lib_name a_lib_name`, `metil_comp` will add `a_lib_name` to the list of the library to be used by the linker.
    - and so on...

If e.g. `#pragma cpp_flag`, `#pragma lnk_flag`, ... are not convenient, standards compile and link flags can be passed normally in the command line. Example: `metil_comp -O3 -g3 my_file.cpp` will globally send `-O3` and `-g3` to the compiler and the linker.

If you want to execute the code under gdb / valgrind supervision 
- `metil_comp --gdb ex1.cpp` -> simply launch the executable using gdb
- `metil_comp --valgrind ex1.cpp` -> basic usage of valgrind
- `metil_comp --exec-using "valgrind --leak-check=full"` ex1.cpp

Help:
```
metil_comp [options] cpp_file
  -h or --help : usage
  -o file : name of the output file
  -jn : launch compilation using n threads
  -mex : create a Matlab mexglx file
  -make filename : generate a Makefile and do not launch
  -dylib : create a dynamic library
  -ne : do not launch the executable
  -nc : do not compile (launch the executable if -ne is not present)
  -pg : instrumentation of the code for gprof (http://www.cs.utah.edu/dept/old/texinfo/as/gprof_toc.html)
  -exec toto : execute 'toto' after compilation
  -Iincludedir : append an include dir to environnement
  -DMACRO : #define MACRO
  -DMACRO=val : #define MACRO val
  -gn : set debug level to n
  -On : set optimisation level to n
  -On : set optimisation level to n
  -no-env : do not use METIL_... environment variables for compilation
  --cxx cxx : specify compiler
  --ld ld : specify linker
  --sep-libs : use of .so intermediate files (use .a instead)
  --no-sep-libs : avoid use of .so intermediate files (use .a instead), to obtain an independant executable
  --comp-dir dir : specify path of directory used to store tmp files (.o, ...)
  --exec-using prg : execute using prg. Example : --exec-using time to use time
  --valgrind : execute using valgrind
  --gdb : execute using gbb (user has to write run in the gdb prompt...)
  --device-emulation : device emulation for cuda
  --maxrregcount n : device emulation for cuda
  --static : do not make dynamic objects
  --dynamic: make dynamic objects
  --use-dylib orig.cpp: use dylib generated from orig.cpp
possible pragma in .h/.cpp/.cu files:
  inc_path additionnal include path
  lnk_flag additionnal flags explicitly passed to the linker
  cxx_name specify compiler, like e.g. icpc -gxx-name=g++-4.4
  cpp_flag additionnal flags explicitly passed to the compiler
  gpu_flag additionnal flags explicitly passed to nvcc
  src_file additionnal cpp / cu files
  lib_path additionnal library (.so/.a) path, like e.g. /usr/local/lib
  lib_name additionnal library name (.so/.a), like e.g. pthread
  fra_name additionnal framework name. Means -l on most of the systems, except for Mac Os.
  template var value_0 value_1 ... permits to generate several versions of a .cpp with var substituted by value_0, then value_1, ...
In most of the cases, pragma are included as
#ifdef METIL_COMP_DIRECTIVE
#pragma ...
#endif // METIL_COMP_DIRECTIVE
```
