/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "Metil/Level1/CompilationEnvironment.h"
#include "Metil/System.h"

#include <stdio.h>

using namespace Metil;

void usage( const char *pn, const char *msg = NULL ) {
    if ( msg )
        cerrn << msg;
    cerrn << pn << " [options] cpp_file";
    cerrn << "  -h or --help : usage";
    cerrn << "  -o file : name of the output file";
    cerrn << "  -jn : launch compilation using n threads";
    cerrn << "  -mex : create a Matlab mexglx file";
    cerrn << "  -make filename : generate a Makefile and do not launch";
    cerrn << "  -dylib : create a dynamic library";
    cerrn << "  -ne : do not launch the executable";
    cerrn << "  -nc : do not compile (launch the executable if -ne is not present)";
    cerrn << "  -pg : instrumentation of the code for gprof (http://www.cs.utah.edu/dept/old/texinfo/as/gprof_toc.html)";
    cerrn << "  -exec toto : execute 'toto' after compilation";
    cerrn << "  -Iincludedir : append an include dir to environnement";
    cerrn << "  -DMACRO : #define MACRO";
    cerrn << "  -DMACRO=val : #define MACRO val";
    cerrn << "  -gn : set debug level to n";
    cerrn << "  -On : set optimisation level to n";
    cerrn << "  -On : set optimisation level to n";
    cerrn << "  -no-env : do not use METIL_... environment variables for compilation";
    cerrn << "  --cxx cxx : specify compiler";
    cerrn << "  --sep-libs : use of .so intermediate files (use .a instead)";
    cerrn << "  --no-sep-libs : avoid use of .so intermediate files (use .a instead), to obtain an independant executable";
    cerrn << "  --comp-dir dir : specify path of directory used to store tmp files (.o, ...)";
    cerrn << "  --exec-using prg : execute using prg. Example : --exec-using time to use time";
    cerrn << "  --valgrind : execute using valgrind";
    cerrn << "  --gdb : execute using gbb (user has to write run in the gdb prompt...)";
    cerrn << "  --device-emulation : device emulation for cuda";
    cerrn << "  --maxrregcount n : device emulation for cuda";
    cerrn << "  --static : do not make dynamic objects";
    cerrn << "possible pragma in .h/.cpp/.cu files:";
    cerrn << "  inc_path additionnal include path";
    cerrn << "  lnk_flag additionnal flags explicitly passed to the linker";
    cerrn << "  cpp_flag additionnal flags explicitly passed to the compiler";
    cerrn << "  gpu_flag additionnal flags explicitly passed to nvcc";
    cerrn << "  src_file additionnal cpp / cu files";
    cerrn << "  lib_path additionnal library (.so/.a) path, like e.g. /usr/local/lib";
    cerrn << "  lib_name additionnal library name (.so/.a), like e.g. pthread";
    cerrn << "  fra_name additionnal framework name. Means -l on most of the systems, except for Mac Os.";
    cerrn << "  template var value_0 value_1 ... permits to generate several versions of a .cpp with var substituted by value_0, then value_1, ...";
    cerrn << "In most of the cases, pragma are included as";
    cerrn << "#ifdef METIL_COMP_DIRECTIVE";
    cerrn << "#pragma ...";
    cerrn << "#endif // METIL_COMP_DIRECTIVE";
}


bool is_a_CPPFLAG( const String &arg ) {
    return
        arg == "m32" or
        arg.begins_by( "-O" ) or
        arg.begins_by( "-g" ) or
        arg.begins_by( "-march") or
        arg.begins_by( "-m" ) or
        arg.begins_by( "-f" ) or
        arg.begins_by( "-W" ) or
        arg.begins_by( "-L" ) or
        arg.begins_by( "-D" );
}


int main( int argc, char **argv ) {
    bool no_env = false;
    for( int i = 1; i < argc and not no_env; ++i )
        if ( String( argv[ i ] ) == "-no-env" )
            no_env = true;

    Level1::CompilationEnvironment &ce = Level1::CompilationEnvironment::get_main_compilation_environment( no_env );

    String cpp_file, out_file, exec_using, comp_dir, make_file, exec_file;
    BasicVec<String> exec_args;
    bool execution     = true;
    bool compilation   = true;
    bool want_dyn      = true;
    bool want_mex      = false;
    bool want_lib      = false;
    bool want_sep_libs = false;
    bool want_gprof    = false;
    bool valgrind_pipe = false;

    //
    for( int i = 1; i < argc; ++i ) {
        String arg = argv[ i ];
        if ( arg == "-h" or arg == "--help" ) {
            usage( argv[ 0 ] );
            return 0;
        } else if ( arg == "--valgrind" ) {
            exec_using = "valgrind";
            valgrind_pipe = true;
        } else if ( arg == "--gdb" ) {
            exec_using = "gdb --args";
        } else if ( arg == "--exec-using" ) {
            if ( ++i >= argc ) {
                usage( argv[ 0 ], "--exec-using must be followed by a program name" );
                return 4;
            }
            exec_using = argv[ i ];
        } else if ( arg == "-make" ) {
            if ( ++i >= argc ) {
                usage( argv[ 0 ], "-make must be followed by the name of resulting Makefile" );
                return 10;
            }
            make_file = argv[ i ];
        } else if ( arg == "--no-sep-libs" ) {
            want_sep_libs = false;
        } else if ( arg == "--sep-libs" ) {
            want_sep_libs = true;
        } else if ( arg == "-pg" ) {
            // want_gprof = false;
            ce.add_CPPFLAG( "-pg" );
            ce.add_LDFLAG ( "-pg" );
        } else if ( arg == "-exec" ) {
            if ( ++i >= argc ) {
                usage( argv[ 0 ], "-exec must be followed by the name of resulting file" );
                return 10;
            }
            exec_file = argv[ i ];
        } else if ( arg == "--cxx" ) {
            if ( ++i >= argc ) {
                usage( argv[ 0 ], "--cxx must be followed by the name of the cxx compiler" );
                return 5;
            }
            ce.set_CXX( argv[ i ] );
        } else if ( arg == "--comp-dir" ) {
            if ( ++i >= argc ) {
                usage( argv[ 0 ], "--comp-dir must be followed by a path" );
                return 6;
            }
            comp_dir = argv[ i ];
        } else if ( arg == "--device-emulation" ) {
            ce.set_device_emulation( 1 );
        } else if ( arg == "--maxrregcount" ) {
            ce.set_maxrregcount( atoi( argv[ ++i ] ) );
        } else if ( arg.begins_by( "-j" ) ) {
            ce.set_nb_threads( atoi( argv[ i ] + 2 ) );
        } else if ( arg.begins_by( "-g" ) ) {
            ce.set_dbg_level( atoi( argv[ i ] + 2 ) );
        } else if ( arg.begins_by( "-O" ) ) {
            ce.set_opt_level( atoi( argv[ i ] + 2 ) );
        } else if ( arg.begins_by( "-D" ) ) {
            ce.add_def_proc( argv[ i ] + 2 );
        } else if ( arg.begins_by( "-L" ) ) {
            ce.add_lib_path( argv[ i ] + 2 );
        } else if ( arg.begins_by( "-l" ) ) {
            ce.add_lib_name( argv[ i ] + 2 );
        } else if ( arg == "-m32" ) {
            ce.add_CPPFLAG ( "-m32" );
        } else if ( arg == "-no-env" ) {
            // already managed
        } else if ( arg.begins_by( "--static" ) ) {
            want_dyn = false;
        } else if ( arg == "-mex" ) {
            want_mex  = true;
            want_lib  = true;
            want_dyn  = true;
            execution = false;
            want_sep_libs = false;
        } else if ( arg == "-dylib" ) {
            want_lib  = true;
            want_dyn  = true;
            execution  = false;
        } else if ( arg == "-ne" ) {
            execution = false;
        } else if ( arg == "-nc" ) {
            compilation = false;
        } else if ( arg[0] == '-' and arg[1]== 'I' ) {
            ce.add_inc_path( arg.end_from( 2 ) );
        } else if ( arg[0] == '-' and arg[1]== 'o' ) {
            if ( i + 1 >= argc ) {
                usage( argv[ 0 ], "-o must be followed by something (the output file)." );
                return 7;
            }
            out_file = argv[ ++i ];
        } else if ( is_a_CPPFLAG( arg ) ) {
            ce.add_CPPFLAG( arg );
        } else { // -> program name (assuming a .cpp file) and arguments
            if ( not comp_dir )
                if ( String dir = directory_of( arg ) )
                    comp_dir = dir + "/compilations";
            cpp_file = arg;
            for( ++i; i < argc; ++i )
                exec_args << argv[ i ];
        }
    }

    if ( comp_dir )
        ce.set_comp_dir( comp_dir );

    // filenames
    if ( not cpp_file ) {
        usage( argv[ 0 ], "you have to specify something to compile." );
        return 8;
    }

    if ( not out_file ) {
        if ( want_mex )
            out_file = ce.mex_for( cpp_file );
        else if ( want_lib )
            out_file = ce.lib_for( cpp_file, want_dyn );
        else
            out_file = ce.exe_for( cpp_file );
    }

    // want a Makefile ?
    if ( make_file ) {
        Ptr<Level1::CompilationTree> ct = ce.make_compilation_tree( out_file, cpp_file, want_lib, want_dyn, false );
        File fm( make_file, "w" );
        fm << "all: " << ct->dst << "\n\n";
        fm << ce.comp_dir() + "dummy:\n\tmkdir -p " << ce.comp_dir() << "; touch " << ce.comp_dir() << "dummy\n\n";
        ct->save_Makefile( fm, ce.comp_dir() + "dummy" );
        return 0;
    }

    // compilation
    if ( compilation )
        if ( int res_make = ce.make_app( out_file, cpp_file, want_lib, want_dyn, want_sep_libs ) )
            return res_make;

    //    if ( export_file ) {
    //        File res( export_file, "w" );
    //        ce.save_env_var_in_string( res );
    //    }

    // env var (including LD_LIBRARY_PATH)
    ce.save_env_var();
    if ( exec_file )
        exec_cmd( exec_file );

    // execute
    if ( execution ) {
        // exec
        out_file = absolute_filename( out_file );
        String cmd = out_file;
        if ( exec_using.size() )
            cmd = exec_using + ' ' + out_file;
        for(int i = 0; i < exec_args.size(); ++i )
            cmd << ' ' << exec_args[ i ];
        if ( valgrind_pipe )
            cmd += " 2>&1| sed -e 's/^==[0-9]*==\\(.*\\)(\\(.*\\))/\\2:\\1/' 1>&2";
        return exec_cmd( cmd );
    }

    return 0;
}

