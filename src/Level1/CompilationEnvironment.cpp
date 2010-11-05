#include "CompilationCppParser.h"
#include "System.h"

BEG_METIL_LEVEL1_NAMESPACE;

CompilationEnvironment::CompilationEnvironment() {
    // inc_paths
    if ( String metil_src = get_env( "METIL_SRC_DIR" ) )
        add_inc_path( metil_src );
    #ifdef INSTALL_DIR
    add_inc_path( INSTALL_DIR );
    #endif

    // defautl values
    CXX  = "g++";
    LD   = "g++";
    NVCC = "/usr/local/cuda/bin/nvcc";
    _comp_dir = absolute_filename( "compilations" ) + "/";

    device_emulation = 0;
    maxrregcount     = 0;

}

String CompilationEnvironment::find_src( const String &filename, const String &current_dir ) const {
    // absolute path ?
    if ( filename[ 0 ] == '/' or filename[ 0 ] == '\\' )
        return ( file_exists( filename ) ? filename : String() );

    // try with current_dir
    String trial = current_dir + filename;
    if ( file_exists( trial ) )
        return trial;

    // try with inc_paths
    for( int i = 0; i < inc_paths.size(); ++i ) {
        trial = inc_paths[ i ] + filename;
        if ( file_exists( trial ) )
            return trial;
    }

    // not found :(
    return String();
}

String CompilationEnvironment::comp_dir() const {
    mkdir( _comp_dir, false );
    return _comp_dir;
}

void CompilationEnvironment::add_inc_path( const String &d ) {
    String a = absolute_filename( d );
    if ( a.size() ) {
        if ( not a.ends_with( "/" ) )
            a += '/';
        inc_paths.push_back_unique( a );
    }
}


String CompilationEnvironment::obj_suffix( bool dyn ) {
    return dyn ? ".so" : ".o";
}


String CompilationEnvironment::obj_for( const String &cpp, bool dyn ) {
    return comp_dir() + filename_without_dir_of( cpp ) + obj_suffix( dyn );
}


String CompilationEnvironment::make_obj_cmd( const String &obj, const String &cpp, bool dyn ) {
    CompilationCppParser cpp_parser( *this, cpp );

    // .h -> .cpp ?
    for( int i = 0; i < cpp_parser.inc_files.size(); ++i ) {
        String h = cpp_parser.inc_files[ i ];
        if ( h.ends_with( ".h" ) ) {
            String ext_cpp = h.beg_upto( h.size() - 2 ) + ".cpp";
            if ( ext_cpp and file_exists( ext_cpp ) )
                make_obj( obj_for( ext_cpp, false ), ext_cpp, false );
        }
    }

    // src_file
    for( int i = 0; i < cpp_parser.src_files.size(); ++i ) {
        String ext_cpp = cpp_parser.src_files[ i ];
        make_obj( obj_for( ext_cpp, false ), ext_cpp, false );
    }

    // flags
    PRINT( cpp_parser.lib_names );
    for( int i = 0; i < cpp_parser.lib_names.size(); ++i )
        lib_names << cpp_parser.lib_names[ i ];
    for( int i = 0; i < cpp_parser.lib_paths.size(); ++i )
        lib_paths << cpp_parser.lib_paths[ i ];
    for( int i = 0; i < cpp_parser.cpp_paths.size(); ++i )
        inc_paths << cpp_parser.cpp_paths[ i ];

    //    BasicVec<String> lnk_flags; ///<
    //    BasicVec<String> gpu_flags; ///<


    // dates
    if ( last_modification_time_or_zero_of_file_named( obj ) > last_modification_time_or_zero_of_file_named( cpp ) )
        return String();

    // cmd
    String cmd = CXX;
    if ( CPPFLAGS )
        cmd << ' ' << CPPFLAGS;
    if ( dyn )
        cmd << " -fpic";
    for( int i = 0; i < inc_paths.size(); ++i )
        cmd << " -I" << inc_paths[ i ];
    cmd << " -c -o " << obj << ' ' << cpp;
    return cmd;
}

String CompilationEnvironment::make_lnk_cmd( const String &exe, bool lib, bool dyn ) {
    String cmd = LD;
    if ( LDFLAGS )
        cmd << ' ' << LDFLAGS;
    if ( lib )
        cmd << ( dyn ? " -shared" : " -static" );
    for( int i = 0; i < lib_paths.size(); ++i )
        cmd << " -L" << lib_paths[ i ];
    for( int i = 0; i < lib_names.size(); ++i )
        cmd << " -l" << lib_names[ i ];
    cmd << " -o " << exe;
    for( int i = 0; i < obj_files.size(); ++i )
        cmd << ' ' << obj_files[ i ];
    return cmd;
}

String CompilationEnvironment::make_exe_cmd( const String &exe ) {
    return make_lnk_cmd( exe, false, false );
}


int CompilationEnvironment::make_obj( const String &obj, const String &cpp, bool dyn ) {
    if ( obj_files.contains( obj ) )
        return 0;
    obj_files << obj;
    return exec_cmd( make_obj_cmd( obj, cpp, dyn ) );
}

int CompilationEnvironment::make_exe( const String &exe, const String &cpp ) {
    String obj = obj_for( cpp, false );
    if ( int res = make_obj( obj, cpp, false ) )
        return res;
    return exec_cmd( make_exe_cmd( exe ) );
}

END_METIL_LEVEL1_NAMESPACE;
