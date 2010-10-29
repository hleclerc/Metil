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

#include "CompilationCppParser.h"
#include "CompilationGraph.h"
#include "File.h"
#include "System.h"

namespace Metil {

CompilationCppParser::CompilationCppParser( CompilationEnvironment &ce, const String &filename ) {
    defines[ "METIL_COMP_DIRECTIVE" ];
    need_compilation_environment = false;
    //
    parse_src_file_rec( ce, filename );
}

String CompilationCppParser::filename_from_directive( const char *b ) {
    // skip spaces
    while ( *b and ( *b == ' ' or *b == '\t' ) ) ++b;
    //
    const char *e = NULL;
    if ( *b == '<' )
        for( e = ++b; *e and *e != '>'; ++e );
    else if ( *b == '"' )
        for( e = ++b; *e and *e != '"'; ++e );
    else
        for( e = b; *e and *e != ' '; ++e );
    //
    return String( b, e );
}

void skip_spaces( const char *&line_c ) {
    while ( *line_c == ' ' or *line_c == '\t' )
        ++line_c;
}

void skip_lines_until_endif_or_else( Stream &is ) {
    String line;
    while ( true ) {
        is.get_line( line );
        if ( not is )
            return;
        // skip spaces
        const char *line_c = line.data();
        skip_spaces( line_c );
        // 
        if ( String::strncmp( line_c, "#endif", 6 ) == 0 )
            return;
        else if ( String::strncmp( line_c, "#else", 5 ) == 0 )
            return;
        else if ( String::strncmp( line_c, "#ifndef ", 8 ) == 0 )
            skip_lines_until_endif_or_else( is );
        else if ( String::strncmp( line_c, "#ifdef ", 7 ) == 0 )
            skip_lines_until_endif_or_else( is );
        else if ( String::strncmp( line_c, "#if ", 4 ) == 0 )
            skip_lines_until_endif_or_else( is );
    }
}

String get_next_word( const char *&line_c ) {
    skip_spaces( line_c );
    const char *b = line_c;
    while ( *line_c and *line_c != ' ' and *line_c != '(' and *line_c != '\n' and *line_c != '\t' ) ++line_c;
    return String( b, line_c );
}

String rl_strip( const char *b, const char *e ) {
    while ( *b == ' ' )
        ++b;
    if ( e < b )
        return "";
    while ( e >= b and *(e-1) == ' ' )
        --e;
    return String( b, e );
}

void CompilationCppParser::parse_src_file_rec( CompilationEnvironment &ce, String filename ) {
    filename = absolute_filename( filename );
    String current_dir = directory_of( filename );

    if ( filename.ends_with(".h") ) {
        // corresponding .cpp ?
        String cpp_filename = filename.rstrip(1) + "cpp";
        if ( file_exists( cpp_filename ) )
            extcpp_files << cpp_filename;
        // corresponding .cu ?
        String cu_filename = filename.rstrip(1) + "cu";
        if ( file_exists( cu_filename ) )
            extcpp_files << cu_filename;
    }
    
    // sweep lines
    File is( filename.data() );
    String line;
    while ( true ) {
        is.get_line( line );
        if ( not is )
            return;
        // skip spaces
        const char *line_c = line.data();
        skip_spaces( line_c );
        // look for a #...
        if ( *line_c == '#' ) {
            if ( String::strncmp( line_c, "#include", 8 ) == 0 ) {
                String header_file_rel = filename_from_directive( line_c + 8  );
                String hdotpy_file_rel = header_file_rel + ".py";
                String hdotpy_file_abs = ce.find_src( hdotpy_file_rel, current_dir );
                if ( hdotpy_file_abs.size() ) { // .h.py
                    hdotpy_files << hdotpy_file_abs;
                    parse_src_file_rec( ce, hdotpy_file_abs.rstrip( 3 ) );
                } else { // only .h
                    String header_file_abs = ce.find_src( header_file_rel, current_dir );
                    if ( header_file_abs.size() ) {
                        header_files << header_file_abs;
                        parse_src_file_rec( ce, header_file_abs );
                    }
                }
            } else if ( String::strncmp( line_c, "#pragma src_file", 16 ) == 0 ) {
                String extcpp_file = ce.find_src( filename_from_directive( get_next_word( line_c += 16 ) ), current_dir );
                if ( extcpp_file.size() )
                    extcpp_files << extcpp_file;
            } else if ( String::strncmp( line_c, "#pragma cpp_path", 16 ) == 0 ) {
                cpp_paths << get_next_word( line_c += 16 );
                ce.add_include_dir( cpp_paths.back() );
            } else if ( String::strncmp( line_c, "#pragma cpp_flag", 16 ) == 0 ) {
                cpp_flags << get_next_word( line_c += 16 );
            } else if ( String::strncmp( line_c, "#pragma lnk_flag", 16 ) == 0 ) {
                lnk_flags << get_next_word( line_c += 16 );
            } else if ( String::strncmp( line_c, "#pragma gpu_flag", 16 ) == 0 ) {
                gpu_flags << get_next_word( line_c += 16 );
            } else if ( String::strncmp( line_c, "#pragma lib_path", 16 ) == 0 ) {
                lib_paths << get_next_word( line_c += 16 );
            } else if ( String::strncmp( line_c, "#pragma lib_name", 16 ) == 0 ) {
                String extlib_name = get_next_word( line_c += 16 );
                if ( extlib_name.size() )
                    extlib_names << extlib_name;
            } else if ( String::strncmp( line_c, "#pragma need_compilation_environment", 36 ) == 0 ) {
                need_compilation_environment = true;
            } else if ( String::strncmp( line_c, "#ifndef ", 8 ) == 0 ) {
                if ( defines.count( get_next_word( line_c += 8 ) ) )
                    skip_lines_until_endif_or_else( is );
            } else if ( String::strncmp( line_c, "#ifdef ", 7 ) == 0 ) {
                if ( defines.count( get_next_word( line_c += 7 ) ) == 0 )
                    skip_lines_until_endif_or_else( is );
            } else if ( String::strncmp( line_c, "#if ", 4 ) == 0 ) {
                skip_lines_until_endif_or_else( is );
            } else if ( String::strncmp( line_c, "#define ", 8 ) == 0 ) {
                Define &d = defines[ get_next_word( line_c += 8 ) ];
                //
                if ( *line_c == '(' ) {
                    for ( const char *e = ++line_c; ; ++e ) {
                        if ( *e == 0 ) {
                            line_c = e;
                            break;
                        } else if ( *e == ')' ) {
                            d.args << rl_strip( line_c, e );
                            line_c = e + 1;
                            break;
                        } else if ( *e == ',' ) {
                            d.args << rl_strip( line_c, e );
                            line_c = e + 1;
                        }
                    }
                }
                //
                d.val = line_c;
            }
        } else if ( String::strncmp( line_c, "Q_OBJECT", 8 ) == 0 ) {
            if ( not filename.starts_with( "/usr/include/qt4" ) ) // TODO : better filter !!
                files_to_moc.push_back_unique( filename );
        }
        //
    }
}




}
