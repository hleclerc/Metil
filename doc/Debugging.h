/*!

\page Debugging Debugging

    @section DebuggingGeneric Generic flags
    
        The flag <tt>-DDEBUG</tt> will add supplementary tests (correct indices for vectors).
    
        Do not forget to use @p gdb and / or @p valgrind, using the <tt>-g3</tt> flag for the compilation of the @p cpp files.
    
    @section DebuggingMemory Memory leaks, problem with desallocation, ...
    
        By default, Metil uses an home made allocator (nearly 20 times faster than the standard malloc or usual test cases). If you want to check memory leak, you have several compilation flags to use:
        - use <tt>-DDEBUG_ALLOC_LEVEL_0</tt> to check for the global amount of allocated memory at a given time (useful also to get the used memory of the program). If allocated memory do not finish at 0, display a warning message.
        - use <tt>-DDEBUG_ALLOC_LEVEL_1</tt> to check correct desallocation of object (checking desallocation size), with information about where the objects have been allocated, ... It displays a warning message at the end in the cas of memory leaks.
        - use <tt>-DUSE_STD_ALLOC</tt> to use the standard allocator (checked by valgrind).

    
    @section DebuggingRuntime Runtime tests

        Some examples with runtime assertions:
@code
ASSERT( condition, "message" ); // if condition != false, display message, with the line and abort
ASSERT_ARG( condition, "message %s %i", str, int ); // if condition != false,
// display message in a printf fashion along with the line and abort.
ASSERT_IF_DEBUG( condition ); // run the assertion only if -DDEBUG flag is present
TODO; // abort with TODO message with the file and line where the TODO has been placed
@endcode

        In each the cases, @p abort is called, meaning that you can see where the program has stopped @ref MetilCompDebugging "using gdb or valgrind".
        
    @section DebuggingKdevelop Debugging and kdevelop
    
        You can use kdevelop to debugg your executable ( see @ref DebuggingKdevelopPage ).
*/
