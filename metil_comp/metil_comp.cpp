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

#include "CompilationGraph.h"
#include "System.h"
#include "AutoPtr.h"
#include <memory>
#include <stdlib.h>


using namespace Metil;

void usage( const char *pn, const char *msg = NULL ) {
    if ( msg )
        cerrn << msg;
    cerrn << pn << " [options] cpp_file";
    cerrn << "  -h or --help : usage";
    cerrn << "  -o file : name of the output file";
    cerrn << "  -mex : create a Matlab mexglx file";
    cerrn << "  -dylib : create a dynamic library";
    cerrn << "  -ne : do not launch the executable";
    cerrn << "  -nc : do not compile (launch the executable if -ne is not present)";
    cerrn << "  -Iincludedir : append an include dir to environnement";
    cerrn << "  --exec-using prg : execute using prg. Example : --exec-using valgrind or --exec-using gdb to use valgrind or gdb";
    cerrn << "  --valgrind : execute using valgrind";
    cerrn << "  --device-emulation : device emulation for cuda";
    cerrn << "  --maxrregcount n : device emulation for cuda";
    cerrn << "possible pragma in .h/.cpp/.cu files:";
    cerrn << "  src_file additionnal cpp / cu files";
    cerrn << "  cpp_path additionnal include path";
    cerrn << "  lnk_flag additionnal flags explicitly passed to the linker";
    cerrn << "  gpu_flag additionnal flags explicitly passed to nvcc";
    cerrn << "  lib_path additionnal library (.so/.a) path, like e.g. /usr/local/lib";
    cerrn << "  lib_name additionnal library name (.so/.a), like e.g. pthread";
}

bool is_a_CPPFLAG( const String &arg ) {
    return
        arg.starts_with("-O") or
        arg.starts_with("-g") or
        arg.starts_with("-march") or
        arg.starts_with("-f") or
        arg.starts_with( "-W" ) or
        arg.starts_with( "-D" );
}

int main( int argc, char **argv ) {
    try {
        CompilationEnvironment ce;
        BasicVec<String> cpp_files;
        BasicVec<String> exec_args;
        String out_file, exec_using;
        bool execution   = true;
        bool compilation = true;
        bool want_mex    = false;
        bool want_dylib  = false;

        //
        for(int i=1;i<argc;++i) {
            String arg = argv[ i ];
            if ( arg == "-h" or arg == "--help" ) {
                usage( argv[ 0 ] );
                return 0;
            } else if ( arg == "--valgrind" ) {
                exec_using = "valgrind";
            } else if ( arg == "--exec-using" ) {
                if ( ++i >= argc ) {
                    usage( argv[ 0 ], "--exec-using must be followed by a program name" );
                    return 4;
                }
                exec_using = argv[ i ];
            } else if ( arg == "--cxx" ) {
                if ( ++i >= argc ) {
                    usage( argv[ 0 ], "--cxx must be followed by the name of the cxx compiler" );
                    return 4;
                }
                ce.set_CXX( argv[ i ] );
            } else if ( is_a_CPPFLAG( arg ) ) {
                ce.add_to_CPPFLAGS( arg );
            } else if ( arg == "--device-emulation" ) {
                ce.want_device_emulation();
            } else if ( arg == "--maxrregcount" ) {
                ce.maxrregcount = atoi( argv[ ++i ] );
            } else if ( arg == "-mex" ) {
                want_mex   = true;
                want_dylib = true;
                execution  = false;
            } else if ( arg == "-dylib" ) {
                want_dylib = true;
                execution  = false;
            } else if ( arg == "-ne" ) {
                execution = false;
            } else if ( arg == "-nc" ) {
                compilation = false;
            } else if ( arg[0] == '-' and arg[1]== 'I' ) {
                ce.add_include_dir( arg.lstrip( 2 ) );
            } else if ( arg[0] == '-' and arg[1]== 'o' ) {
                if ( i + 1 >= argc ) {
                    usage( argv[ 0 ], "-o must be followed by something (the output file)." );
                    return 3;
                }
                out_file = argv[ ++i ];
            } else { // -> program name (assuming a .cpp file)
                ce.set_comp_dir( directory_of( arg ) );
                cpp_files.push_back( arg );
                for( ++i; i < argc; ++i )
                    exec_args << argv[ i ];
            }
        }


        // filenames
        if ( not cpp_files.size() ) {
            usage( argv[ 0 ], "you have to specify something to compile." );
            return 1;
        }
        String out_file_if_not_specified = ce.exe_file_for( cpp_files[ 0 ] );
        if ( not out_file.size() ) {
            if ( want_mex )
                out_file = ce.mexglx_file_for( cpp_files[ 0 ] );
            else if ( want_dylib )
                out_file = ce.lib_file_for( cpp_files[ 0 ], true );
            else
                out_file = out_file_if_not_specified;
        }

        // compilation
        AutoPtr<CompilationGraphProgram> cg;
        if ( compilation ) {
            String dep_file = out_file_if_not_specified + ".dep";

            // try to load CompilationGraphProgram
            CompilationGraph *tmp_cg = CompilationGraph::load( dep_file );
            if ( dynamic_cast<CompilationGraphProgram *>( tmp_cg ) )
                cg = static_cast<CompilationGraphProgram *>( tmp_cg );
            else
                delete tmp_cg;

            // else make the graph
            if ( not cg ) {
                cg = new CompilationGraphProgram( ce, out_file, want_dylib );
                for(int i=0;i<cpp_files.size();++i)
                    cg->add_src_file( cpp_files[ i ] );
                cg->save( dep_file );
            }

            // do it
            if ( int res_make = cg->make() )
                return res_make;
        }

        // execute
        if ( execution ) {
            String base_dylib = ce.lib_file_for( cpp_files[ 0 ], true );
            setenv( "METIL_BASE_DYLIB", base_dylib.data(), true );

            // add dirs to LD_LIBRARY_PATH
            const char *l = getenv( "LD_LIBRARY_PATH" );
            String LD_LIB = l ? l : "";
            for( int i = 0; i < cg->ce.library_dirs.size(); ++i ) {
                if ( LD_LIB.size() )
                    LD_LIB += ":";
                LD_LIB += cg->ce.library_dirs[ i ];
            }
            setenv( "LD_LIBRARY_PATH", LD_LIB.data(), true );

            //
            setenv( "METIL_COMP_DIR", ce.get_comp_dir(), true );
            setenv( "METIL_CXX_CMD" , ce.get_cxx_cmd (), true );


            if ( out_file.size() and out_file[0] != '/' and out_file[0] != '\\' )
                out_file = "./" + out_file;
            String cmd = out_file;
            if ( exec_using.size() )
                cmd = exec_using + " " + out_file;
            for(int i=0;i<exec_args.size();++i)
                cmd += ' ' + exec_args[ i ];
            return exec_cmd( cmd );
        }
    } catch ( const CompilationError &e ) { PRINT( e.msg ); return 1; }
    return 0;
}

