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

#ifndef METIL_COMPILATIONENVIRONMENT_H
#define METIL_COMPILATIONENVIRONMENT_H

#include "CompilationError.h"
#include "BasicVec.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CompilationEnvironment.cpp
#endif

namespace Metil {

class CompilationEnvironment {
public:
    CompilationEnvironment();
    void add_include_dir( const String &d );
    void add_library_dir( const String &d );
    void want_device_emulation() { device_emulation = 1; }

    void set_comp_dir( String dir );
    String get_comp_dir() const; /// return directory for compilation

    String obj_file_for( const String &cpp_file, bool dynamic = false ) const;
    String lib_file_for( const String &cpp_file, bool dynamic = false ) const;
    String exe_file_for( const String &cpp_file ) const;
    String moc_file_for( const String &cpp_file ) const;
    String cpp_file_for( const String &basename ) const;
    String mexglx_file_for( const String &cpp_file ) const;

    String obj_suffix( bool dynamic = false ) const; // .x86.o ...
    String lib_suffix( bool dynamic = false ) const; // .x86.o ...
    String exe_suffix() const; // ...x86.exe ...
    String moc_suffix() const; // ...x86.moc ...
    String cpp_suffix() const; // ...x86.cpp ...

    String obj_params_digest() const; //
    String exe_params_digest() const; //
    String lib_params_digest() const; //
    String moc_params_digest() const; //

    void set_CXX( const String &cxx ); //

    BasicVec<String> get_include_dirs() const;

    String find_src( const String &filename, const String &current_dir ) const; // use include_dirs...

    void add_library( const String &lib_name );

    String cmd_cu_comp ( const String &obj, const String &cu , bool dynamic = false ) const;
    String cmd_cpp_comp( const String &obj, const String &cpp, bool dynamic = false ) const;
    String cmd_exe_link( const String &prg, const BasicVec<String> &obj ) const;
    String cmd_lib_link( const String &prg, const BasicVec<String> &obj, bool dynamic = false ) const;

    String make_ExternCompilationEnvironment_file( const String &main_dylib_file ) const;

    int exec_cmd( const String &cmd ) const;

    String get_cxx_cmd() const;

    void add_to_CPPFLAGS( const String &s );
    int maxrregcount;
    BasicVec<String> cpp_flags;
    BasicVec<String> lnk_flags;
    BasicVec<String> gpu_flags;

// private:
    String cmd_exe_or_lib_link( const String &prg, const BasicVec<String> &obj, bool want_lib, bool want_shared ) const;
    static String to_filename_compatible_string( const String &str );

    friend struct MainCompilationEnvironmentMaker;

    BasicVec<String> include_dirs;
    BasicVec<String> library_dirs;
    BasicVec<String> lib_names;
    String comp_dir_;
    String CXX;
    String LD;
    String CPPFLAGS;
    String LDFLAGS;
    String NVCC;
    bool device_emulation;
};

}

#endif // METIL_COMPILATIONENVIRONMENT_H
