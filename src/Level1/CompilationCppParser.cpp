#include "CompilationCppParser.h"
#include "Level1/StringHelp.h"
#include "System.h"

BEG_METIL_LEVEL1_NAMESPACE;

CompilationCppParser::CompilationCppParser( CompilationEnvironment &ce, const String &cpp_file ) {
    defines[ "METIL_COMP_DIRECTIVE" ];
    need_compilation_environment = false;
    //
    parse_src_file_rec( ce, cpp_file );
}

static void skip_spaces_but_not_cr( const char *&c ) {
    while ( *c == ' ' or *c == '\t' )
        ++c;
}

static String get_include_filename( const char *b ) {
    // skip spaces
    skip_spaces_but_not_cr( b );
    //
    const char *e = NULL;
    if ( *b == '<' )
        for( e = ++b; *e and *e != '>'; ++e );
    else if ( *b == '"' )
        for( e = ++b; *e and *e != '"'; ++e );
    else
        for( e = b; *e and *e != ' '; ++e );
    //
    return String( NewString( b, e ) );
}

static void go_to_next_line( const char *&c ) {
    for( ; *c; ++c )
        if ( *c == '\n' )
            return;
}

static void go_to_next_mul_slash( const char *&c ) {
    for( ; *c; ++c )
        if ( c[ 0 ] == '*' and c[ 1 ] == '/' )
            return;
}

static void skip_lines_until_endif_or_else( const char *&c ) {
    for( ; *c; ) {
        // comment ?
        if ( c[ 0 ] == '/' ) {
            if ( c[ 1 ] == '/' ) {
                go_to_next_line( c += 2 );
                continue;
            }
            if ( c[ 1 ] == '*' ) {
                go_to_next_mul_slash( c += 2 );
                continue;
            }
        }
        // #endif, #else, #elif
        if ( c[ 0 ] == '#' and c[ 1 ] == 'e' ) {
            if ( c[ 2 ] == 'n' and c[ 3 ] == 'd' and c[ 4 ] == 'i' and c[ 5 ] == 'f' ) {
                c += 6;
                return;
            }
            if ( c[ 2 ] == 'l' ) {
                if ( c[ 3 ] == 's' and c[ 4 ] == 'e' ) {
                    c += 5;
                    return;
                }
                if ( c[ 3 ] == 'i' and c[ 4 ] == 'f' ) {
                    return;
                }
            }
        }
        ++c;
    }
}

static String get_next_word( const char *&c ) {
    skip_spaces_but_not_cr( c );
    const char *b = c;
    while ( is_a_letter_or_a_number( *c ) )
        ++c;
    return String( NewString( b, c ) );
}

void CompilationCppParser::parse_src_file_rec( CompilationEnvironment &ce, const String &filename ) {
    String current_dir = directory_of( filename ) + "/";
    File file( filename, "r" );
    for ( const char *c = file.c_str(); *c; ) {
        // comment ?
        if ( c[ 0 ] == '/' ) {
            if ( c[ 1 ] == '/' ) {
                go_to_next_line( c += 2 );
                continue;
            }
            if ( c[ 1 ] == '*' ) {
                go_to_next_mul_slash( c += 2 );
                continue;
            }
        }
        //
        if ( c[ 0 ] == '#' ) {
            if ( c[ 1 ] == 'd' and c[ 2 ] == 'e' and c[ 3 ] == 'f' and c[ 4 ] == 'i' and c[ 5 ] == 'n' and c[ 6 ] == 'e' and c[ 7 ] == ' ' ) {
                defines[ get_next_word( c += 8 ) ];
                continue;
            }
            if ( c[ 1 ] == 'i' ) {
                if ( c[ 2 ] == 'f' ) {
                    if ( c[ 3 ] == 'd' and c[ 4 ] == 'e' and c[ 5 ] == 'f' and c[ 6 ] == ' ' ) {
                        if ( not defines.count( get_next_word( c += 7 ) ) )
                            skip_lines_until_endif_or_else( c );
                        continue;
                    }
                    if ( c[ 3 ] == 'n' and c[ 4 ] == 'd' and c[ 5 ] == 'e' and c[ 6 ] == 'f' and c[ 7 ] == ' ' ) {
                        if ( defines.count( get_next_word( c += 8 ) ) )
                            skip_lines_until_endif_or_else( c );
                        continue;
                    }
                }
                if ( c[ 2 ] == 'n' and c[ 3 ] == 'c' and c[ 4 ] == 'l' and c[ 5 ] == 'u' and c[ 6 ] == 'd' and c[ 7 ] == 'e' and c[ 8 ] == ' ' ) {
                    String inc_file = ce.find_src( get_include_filename( c += 9 ), current_dir );
                    if ( inc_file ) {
                        inc_files << inc_file;
                        parse_src_file_rec( ce, inc_file );
                    }
                    continue;
                }
            }
            if ( c[ 1 ] == 'p' and c[ 2 ] == 'r' and c[ 3 ] == 'a' and c[ 4 ] == 'g' and c[ 5 ] == 'm' and c[ 6 ] == 'a' and c[ 7 ] == ' ' ) {
                c += 7;
                if ( equal( c, "src_file" ) ) {
                    src_files << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "lib_path" ) ) {
                    lib_paths << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "lib_name" ) ) {
                    lib_names << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "cpp_path" ) ) {
                    cpp_paths << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "cpp_flag" ) ) {
                    cpp_flags << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "lnk_flag" ) ) {
                    lnk_flags << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "gpu_flag" ) ) {
                    gpu_flags << get_next_word( c += 8 );
                    continue;
                }
                if ( equal( c, "need_compilation_environment" ) ) {
                    c += 28;
                    need_compilation_environment = true;
                    continue;
                }
            }
        }

        //
        ++c;
    }
}

END_METIL_LEVEL1_NAMESPACE;
