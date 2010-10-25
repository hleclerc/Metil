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

//#include <iostream>
//#include <fstream>

#include "CompilationEnvironment.h"
#include "System.h"
#include "InstallDir.h"
#include "BasicVecMath.h"

namespace Metil {

CompilationEnvironment::CompilationEnvironment() {
    CXX = "g++";
    LD = "g++";
    CPPFLAGS = "-Wall";
    NVCC = "/usr/local/cuda/bin/nvcc";
    
    device_emulation = 0;
    maxrregcount = 0;
    // set_comp_dir( "." );
    #ifdef INSTALL_DIR
        add_include_dir( INSTALL_DIR );
    #endif
}

void CompilationEnvironment::add_include_dir( const String &d ) {
    String a = absolute_filename( d );
    if ( a.size() ) {
        if ( a[ a.size() - 1 ] != '/' and a[ a.size() - 1 ] != '\\' )
            a += '/';
        include_dirs.push_back_unique( a );
    }
}

void CompilationEnvironment::add_library_dir( const String &d ) {
    String a = absolute_filename( d );
    if ( a.size() ) {
        if ( a[ a.size() - 1 ] != '/' and a[ a.size() - 1 ] != '\\' )
            a += '/';
        library_dirs.push_back_unique( a );
    }
}

String CompilationEnvironment::find_src( const String &filename, const String &current_dir ) const {
    // absolute path ?
    if ( filename[ 0 ] == '/' or filename[ 0 ] == '\\' )
        return ( file_exists( filename ) ? filename : "" );
    
    // try with current_dir
    String trial = current_dir + filename;
    if ( file_exists( trial ) )
        return trial;
        
    // try with include_dirs
    for(int i=0;i<include_dirs.size();++i) {
        if ( include_dirs[ i ][ include_dirs[ i ].size() - 1 ] != '/' )
            throw "Dir from ce.get_include_dirs() should end by a / : " + include_dirs[ i ];
        trial = include_dirs[ i ] + filename;
        if ( file_exists( trial ) )
            return trial;
    }
    
    // not found :(
    return "";
}


void CompilationEnvironment::set_comp_dir( String dir ) {
    dir = absolute_filename( dir );
    if ( not dir.ends_with( '/' ) )
        dir += '/';
        
    // try /path_of_filename/compilations
    comp_dir_ = dir + "compilations";
    if ( create_directory( comp_dir_, false ) ) { // else, try /tmp/compilations/path_of_filename/
        comp_dir_ = "/tmp";
        BasicVec<String> tok = tokenize( "compilations/" + dir, '/' );
        for(int i=0;i<tok.size();++i) {
            if ( not tok[ i ].size() )
                continue;
            comp_dir_ += "/" + tok[ i ];
            if ( create_directory( comp_dir_, false ) )
                throw "pb to create directory '" + comp_dir_ + "'.";
        }
    }
    comp_dir_ += '/';
    
    create_directory( comp_dir_ + "base", false );
}

String CompilationEnvironment::get_comp_dir() const {
    if ( not comp_dir_.size() )
        throw "please call set_comp_dir before comp_dir";
    return comp_dir_;
}

void CompilationEnvironment::set_CXX( const String &cxx ) {
    CXX = cxx;
}

String CompilationEnvironment::to_filename_compatible_string( const String &str ) {
    String res( String::Size(), str.size() );
    for(int i=0;i<str.size();++i) {
        switch ( str[ i ] ) {
          case ' ':
            res[ i ] = '_';
            break;
          default:
            res[ i ] = str[ i ];
        }
    }
    return res;
}

String CompilationEnvironment::obj_params_digest() const {
    return get_os_type() + "_" + get_cpu_type() + "_" + CXX + '_' + CPPFLAGS;
}

String CompilationEnvironment::exe_params_digest() const {
    return get_os_type() + "_" + get_cpu_type() + "_" + CXX + '_' + CPPFLAGS + "_" + LD + '_' + LDFLAGS;
}

String CompilationEnvironment::lib_params_digest() const {
    return get_os_type() + "_" + get_cpu_type() + "_" + CXX + '_' + CPPFLAGS + "_" + LD + '_' + LDFLAGS;
}

String CompilationEnvironment::moc_params_digest() const {
    return "QT4";
}


String CompilationEnvironment::obj_suffix( bool dynamic ) const {
    return "." + to_filename_compatible_string( obj_params_digest() ) + ( dynamic ? ".os" : ".o" );
}

String CompilationEnvironment::exe_suffix() const {
    return "." + to_filename_compatible_string( exe_params_digest() ) + ".exe";
}

String CompilationEnvironment::lib_suffix( bool dynamic ) const {
    return "." + to_filename_compatible_string( lib_params_digest() ) + ( dynamic ? ".so" : ".a" );
}

String CompilationEnvironment::moc_suffix() const {
    return "." + to_filename_compatible_string( moc_params_digest() ) + ".moc.cpp";
}

String CompilationEnvironment::cpp_suffix() const {
    return ".cpp";
    // return "." + to_filename_compatible_string( obj_params_digest() + lib_params_digest() ) + ".cpp";
}


String CompilationEnvironment::obj_file_for( const String &cpp_file, bool dynamic ) const {
    return get_comp_dir() + filename_without_dir_of( cpp_file ) + obj_suffix( dynamic );
}

String CompilationEnvironment::lib_file_for( const String &cpp_file, bool dynamic ) const {
    return get_comp_dir() + filename_without_dir_of( cpp_file ) + lib_suffix( dynamic );
}

String CompilationEnvironment::exe_file_for( const String &cpp_file ) const {
    return get_comp_dir() + filename_without_dir_of( cpp_file ) + exe_suffix();
}

String CompilationEnvironment::mexglx_file_for( const String &cpp_file ) const {
    const char *suffix = ".mexglx";
    if ( cpp_file.ends_with( ".cpp" ) ) return cpp_file.rstrip( 4 ) + suffix;
    if ( cpp_file.ends_with( ".cxx" ) ) return cpp_file.rstrip( 4 ) + suffix;
    if ( cpp_file.ends_with( ".cc"  ) ) return cpp_file.rstrip( 3 ) + suffix;
    return cpp_file + suffix;
}

String CompilationEnvironment::moc_file_for( const String &cpp_file ) const {
    return get_comp_dir() + filename_without_dir_of( cpp_file ) + moc_suffix();
}

String CompilationEnvironment::cpp_file_for( const String &basename ) const {
    return get_comp_dir() + filename_without_dir_of( basename ) + cpp_suffix();
}

int CompilationEnvironment::exec_cmd( const String &cmd ) const {
    coutn << cmd;
    return Metil::exec_cmd( cmd );
}

String CompilationEnvironment::cmd_cpp_comp( const String &obj, const String &cpp, bool dynamic ) const {
    String cmd = CXX;
    if ( CPPFLAGS.size() )
        cmd += " " + CPPFLAGS;
    if ( dynamic )
        cmd += " -fpic";
    cmd += " -c -o " + obj;
    for(int i=0;i<include_dirs.size();++i)
        cmd += " -I" + include_dirs[ i ];
    for(int i=0;i<cpp_flags.size();++i)
        cmd += " " + cpp_flags[ i ];
    return cmd + " " + cpp;
}

String CompilationEnvironment::cmd_cu_comp( const String &obj, const String &cu, bool dynamic ) const {
    String cmd = NVCC;
    //if ( CPPFLAGS.size() )
    //    cmd += " " + CPPFLAGS;
    //if ( dynamic )
    //    cmd += " -fpic";
    if ( maxrregcount )
        cmd += " --maxrregcount=" + String( maxrregcount );
    if ( device_emulation )
        cmd += " --device-emulation -g";
    else
        cmd += " -w -g -O3 --gpu-architecture=compute_13";
    cmd += " -c -o " + obj;
    if ( dynamic )
        cmd += " -Xcompiler -fPIC";
    for(int i=0;i<gpu_flags.size();++i)
        cmd += " " + gpu_flags[ i ];
    for(int i=0;i<include_dirs.size();++i)
        cmd += " -I" + include_dirs[ i ];
    #ifdef INSTALL_DIR
        cmd += " -I" INSTALL_DIR;
    #endif
    return cmd + " " + cu;
}

String CompilationEnvironment::cmd_exe_or_lib_link( const String &prg, const BasicVec<String> &obj, bool want_lib, bool want_shared ) const {
    String cmd = LD;
    if ( LDFLAGS.size() )
        cmd += " " + LDFLAGS;
    if ( want_lib )
        cmd += ( want_shared ? " -shared" : " -static" );
    for(int i=0;i<library_dirs.size();++i)
        cmd += " -L" + library_dirs[ i ];
    for(int i=0;i<lib_names.size();++i)
        cmd += " -l" + lib_names[ i ];
    for(int i=0;i<lnk_flags.size();++i)
        cmd += " " + lnk_flags[ i ];
    cmd += " -o " + prg;
    for(int i=0;i<obj.size();++i)
        cmd += " " + obj[ i ];
    return cmd;
}

String CompilationEnvironment::cmd_exe_link( const String &prg, const BasicVec<String> &obj ) const {
    return cmd_exe_or_lib_link( prg, obj, false, false );
}

String CompilationEnvironment::cmd_lib_link( const String &prg, const BasicVec<String> &obj, bool dynamic ) const {
    return cmd_exe_or_lib_link( prg, obj, true, dynamic );
}

    
BasicVec<String> CompilationEnvironment::get_include_dirs() const {
    return include_dirs;
}

void CompilationEnvironment::add_to_CPPFLAGS( const String &s ) {
    if ( CPPFLAGS.size() )
        CPPFLAGS += " ";
    CPPFLAGS += s;
}

void CompilationEnvironment::add_library( const String &lib_name ) {
    lib_names.push_back_unique( lib_name );
}

String CompilationEnvironment::make_ExternCompilationEnvironment_file( const String &main_dylib_file ) const {
    String res = cpp_file_for( "ExternCompilationEnvironment" );

    StringStream<String> fout;
    StreamWithEndlBeforeDestroyMaker f( fout );

    f << "#include <CompilationEnvironment.h>";
    f << "namespace Metil {";
    f << "struct MainCompilationEnvironmentMaker {";
    f << "    MainCompilationEnvironmentMaker() {";
    for(int i=0;i<include_dirs.size();++i)
        f << "        ce.include_dirs << \"" << include_dirs[ i ] << "\";";
    for(int i=0;i<lib_names.size();++i)
        f << "        ce.lib_names << \"" << lib_names[ i ] << "\";";
    f << "        ce.comp_dir_ = \"" << comp_dir_ << "\";";
    f << "        ce.CXX = \"" << CXX << "\";";
    f << "        ce.LD = \"" << LD << "\";";
    f << "        ce.CPPFLAGS = \"" << CPPFLAGS << "\";";
    f << "        ce.LDFLAGS = \"" << LDFLAGS << "\";";
    if ( main_dylib_file.size() )
        f << "        ce.lib_names << \"" << main_dylib_file << "\";";
    f << "    }";
    f << "    CompilationEnvironment ce;";
    f << "};";
    f << "CompilationEnvironment &compilation_environment() {";
    f << "    static MainCompilationEnvironmentMaker res;";
    f << "    return res.ce;";
    f << "}";
    f << "} // namespace Metil";

    if ( File( res ).get_left() != fout.str ) {
        File f( res, "w" );
        f << fout.str;
    }

    return res;
}

} // namespace Metil
