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

#ifndef METIL_COMPILATIONCPPPARSER_H
#define METIL_COMPILATIONCPPPARSER_H

#include "CompilationEnvironment.h"
#include <map>

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CompilationCppParser.cpp
#endif

namespace Metil {

/**
    @author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class CompilationCppParser {
public:
    CompilationCppParser( const CompilationEnvironment &ce, const String &filename );
    
    BasicVec<String> header_files;
    BasicVec<String> hdotpy_files;
    BasicVec<String> extcpp_files;
    BasicVec<String> extlib_names;
    BasicVec<String> cpp_paths;
    BasicVec<String> cpp_flags;
    BasicVec<String> lnk_flags;
    BasicVec<String> gpu_flags;
    BasicVec<String> lib_paths;
    BasicVec<String> files_to_moc;
    bool need_compilation_environment;
    
private:
    struct Define {
        BasicVec<String> args;
        String val;
    };
    
    void parse_src_file_rec( const CompilationEnvironment &ce, String filename );
    
    static String filename_from_directive( const char *b );
    
    std::map<String,Define> defines;
};

}
#endif // METIL_COMPILATIONCPPPARSER_H
