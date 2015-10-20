#include "CompilationCppParser.h"
#include "StringHelp.h"
#include "../Tokenize.h"
#include "../System.h"

BEG_METIL_LEVEL1_NAMESPACE;

static void save_dep_vec( String &fd, const BasicVec<String> &vec ) {
    for( int i = 0; i < vec.size(); ++i )
        fd << vec[ i ].size() << vec[ i ];
    fd << "0\n";
}

static void load_dep_vec( const char *&c, BasicVec<String> &vec ) {
    if ( not c )
        return;
    while ( true ) {
        String r = String::read_sized( c );
        if ( not r )
            break;
        vec << r;
    }
    if ( *c )
        ++c;
}

bool CompilationCppParser::init_using_dep( CompilationEnvironment &ce, const String &cpp_file, const String &dep_file ) {
    SI64 date_cpp = last_modification_time_or_zero_of_file_named( cpp_file );
    SI64 date_dep = last_modification_time_or_zero_of_file_named( dep_file );
    if ( date_cpp > date_dep )
        return false;

    File fd( dep_file, "r" );
    const char *c = fd.c_str();

    // orig flags are conform ?
    BasicVec<String> loc_inc_paths;
    BasicVec<String> loc_def_procs;
    load_dep_vec( c, loc_inc_paths );
    load_dep_vec( c, loc_def_procs );
    if ( ce_inc_paths.size() != loc_inc_paths.size() or ce_def_procs.size() != loc_def_procs.size() )
        return false;
    if ( any( ce_inc_paths != loc_inc_paths ) or any( ce_def_procs != loc_def_procs ) )
        return false;


    // include file are older than dep file ?
    load_dep_vec( c, inc_files );
    for( ST i = 0; i < inc_files.size(); ++i ) {
        if ( last_modification_time_or_zero_of_file_named( inc_files[ i ] ) > date_dep ) {
            inc_files.resize( 0 );
            return false;
        }
    }

    // -> OK
    load_dep_vec( c, moc_files );
    load_dep_vec( c, src_files );

    load_dep_vec( c, lib_paths );
    load_dep_vec( c, lib_names );
    load_dep_vec( c, fra_names );
    load_dep_vec( c, inc_paths );
    load_dep_vec( c, cpp_flags );
    load_dep_vec( c, lnk_flags );
    load_dep_vec( c, gpu_flags );
    load_dep_vec( c, var_templ );
    load_dep_vec( c, cxx_name  );

    BasicVec<String> defs;
    load_dep_vec( c, defs );
    for( int i = 0; i < defs.size(); ++i )
        defines[ defs[ i ] ];

    // .h.py ?
    for( int i = 0; i < inc_files.size(); ++i ) {
        String inc_file = inc_files[ i ];
        if ( inc_file.ends_with( ".h" ) ) {
            String h_py = inc_file + ".py";
            if ( file_exists( h_py ) ) {
                if ( last_modification_time_or_zero_of_file_named( h_py ) >
                     last_modification_time_or_zero_of_file_named( inc_file ) )
                    make_h_py( h_py, inc_file );
            }
        }
    }

    return true;
}

CompilationCppParser::CompilationCppParser( CompilationEnvironment &ce, const String &cpp_file, const String &dep_file ) : dep_file( dep_file ) {
    ce.get_inc_paths( ce_inc_paths );
    ce.get_def_procs( ce_def_procs );
    if ( init_using_dep( ce, cpp_file, dep_file ) )
        return;

    //
    defines[ "METIL_COMP_DIRECTIVE" ];
    for( int i = 0; i < ce_def_procs.size(); ++i )
        defines[ ce_def_procs[ i ] ];

    //
    parse_src_file_rec( ce, cpp_file );
}

CompilationCppParser::~CompilationCppParser() {
    // save .dep
    File fd( dep_file, "w" );
    save_dep_vec( fd, ce_inc_paths );
    save_dep_vec( fd, ce_def_procs );

    save_dep_vec( fd, inc_files );
    save_dep_vec( fd, moc_files );
    save_dep_vec( fd, src_files );

    save_dep_vec( fd, lib_paths );
    save_dep_vec( fd, lib_names );
    save_dep_vec( fd, fra_names );
    save_dep_vec( fd, inc_paths );
    save_dep_vec( fd, cpp_flags );
    save_dep_vec( fd, lnk_flags );
    save_dep_vec( fd, gpu_flags );
    save_dep_vec( fd, var_templ );
    save_dep_vec( fd, cxx_name  );
}

static void skip_spaces_but_not_cr( const char *&c ) {
    while ( *c == ' ' or *c == '\t' )
        ++c;
}

static String get_include_filename( const char *b, bool &syst ) {
    // skip spaces
    skip_spaces_but_not_cr( b );
    //
    syst = ( *b == '<' );
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
        // #if...
        if ( c[ 0 ] == '#' and c[ 1 ] == 'i' and c[ 2 ] == 'f' ) {
            skip_lines_until_endif_or_else( c += 3 );
            continue;
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

static const char *rstrip( const char *c ) {
    while ( is_a_space( *c ) )
        --c;
    return c + 1;
}

static String get_pragma_arg( const char *&c ) {
    skip_spaces_but_not_cr( c );
    const char *b = c;
    go_to_next_line( c );
    return String( NewString( b, rstrip( c ) ) );
}

static void go_after_next_double_quote( const char *&c ) {
    for( ; *c; ++c ) {
        if ( *c == '\\' )
            ++c;
        else if ( *c == '"' ) {
            ++c;
            break;
        }
    }
}

void CompilationCppParser::make_h_py( const String &h_py, const String &inc_file ) {
    String cmd;
    cmd << "export PYTHONPATH=\".";
    for( int i = 0; i < ce_inc_paths.size(); ++i ) {
        int pl = ce_inc_paths[ i ].find( "LMT" );
        if ( pl >= 0 ) {
            cmd << ":" << ce_inc_paths[ i ].beg_upto( pl );
            //
            int pi = ce_inc_paths[ i ].find( "/include" );
            if ( pi >= 0 )
                cmd << ":" << ce_inc_paths[ i ].beg_upto( pi );
        }
    }
    cmd << ":$PYTHONPATH\"; python " << h_py << " > " << inc_file;
    exec_cmd( cmd, true );
}

void CompilationCppParser::parse_src_file_rec( CompilationEnvironment &ce, const String &filename ) {
    if ( is_a_directory( filename ) )
        return;
    String current_dir = directory_of( filename ) + "/";
    File file( filename, "r" );
    for ( const char *c = file.c_str(); *c; ) {
        // string ?
        if ( c[ 0 ] == '"' ) {
            go_after_next_double_quote( ++c );
            continue;
        }
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
        // QOBJECT ?
        if ( c[ 0 ] == 'Q' ) {
            if ( strncmp( c + 1, "_OBJECT", 7 ) == 0 ) {
                c += 8;
                if ( not filename.begins_by( "/usr/" ) ) // hum !!
                    moc_files.push_back_unique( filename );
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
                    bool syst;
                    String bas_name = get_include_filename( c += 9, syst );
                    String inc_file =  ce.find_src( bas_name, current_dir, inc_paths, not syst );
                    if ( not inc_file )
                        inc_file = ce.find_src( bas_name, current_dir, ce_inc_paths, not syst );

                    // formulation.
                    if ( not inc_file ) {
                        int form_ind = bas_name.find( "formulation." );
                        if ( form_ind >= 0 and bas_name != "formulation.h" ) {
                            String h_py = bas_name + ".py";
                            if ( not file_exists( h_py ) ) {
                                int beg_form = form_ind + 12;
                                int end_form = bas_name.find( ".", beg_form );
                                String form = bas_name.beg_upto( end_form ).end_from( beg_form );

                                int beg_elem = end_form + 1;
                                int end_elem = bas_name.find( ".", beg_elem );
                                String elem = bas_name.beg_upto( end_elem ).end_from( beg_elem );
                                BasicVec<String> elem_list = tokenize( elem, ',' );

                                int beg_parm = end_elem + 1;
                                int end_parm = bas_name.find( ".", beg_parm );
                                String parm = bas_name.beg_upto( end_parm ).end_from( beg_parm );
                                BasicVec<String> parm_list = tokenize( parm, ',' );
                                BasicVec<String> der_vars;
                                BasicVec<String> dim;
                                for( int np = 0; np < parm_list.size(); ++np ) {
                                    if ( parm_list[ np ].begins_by( "name_der_vars=" ) )
                                        der_vars << parm_list[ np ].end_from( 14 );
                                    else if ( parm_list[ np ].begins_by( "dim=" ) )
                                        dim << parm_list[ np ].end_from( 4 );
                                }

                                File f( h_py, "w" );
                                // f << "import sys, os\n";
                                // f << "sys.path.append( os.getcwd() + '/LMT' )\n";
                                // f << "sys.path.append( os.getcwd() + '/LMTpp' )\n";
                                f << "import formal_lf\n";
                                f << "formal_lf.write_pb(\n";
                                f << "    name = '" << form << "',\n";
                                f << "    formulations = ['" << form << "'],\n";
                                f << "    elements = [";
                                for( int i = 0; i < elem_list.size(); ++i )
                                    f << ( i ? ",'" : "'" ) << elem_list[ i ] << "'";
                                f << "],\n";
                                f << "    incpaths = ['.'";
                                for( int i = 0; i < ce_inc_paths.size(); ++i )
                                    if ( ce_inc_paths[ i ].find( "LMT" ) >= 0 )
                                        f << ",'" << ce_inc_paths[ i ].beg_upto( ce_inc_paths[ i ].find( "/include" ) ) << "/formulations'";
                                f << "],\n";
                                f << "    name_der_vars=[";
                                for( int nd = 0; nd < der_vars.size(); ++nd )
                                    f << ( nd ? "," : "" ) << '"' << der_vars[ nd ] << '"';
                                f << "],\n";
                                if ( dim.size() )
                                    f << "    dim='" << dim[ 0 ] << "',\n";
                                f << ")\n";
                                // f << "    options = { 'behavior_simplification' : 'plane stress', 'behavior_law' : s },
                                // f << "    # name_der_vars = [ "frac_E2", "frac_G12", "nu12" ] #
                            }
                        }
                    }

                    // .h.py ?
                    if ( bas_name.ends_with( ".h" ) ) {
                        if ( String h_py = ce.find_src( bas_name + ".py", current_dir ) ) {
                            inc_file = h_py.beg_upto( h_py.size() - 3 );
                            if ( last_modification_time_or_zero_of_file_named( h_py ) >
                                 last_modification_time_or_zero_of_file_named( inc_file ) )
                                make_h_py( h_py, inc_file );
                        }
                    }

                    // parse rec
                    if ( inc_file ) {
                        inc_file = canonicalize_filename( inc_file );
                        inc_files << inc_file;

                        //
                        if ( not already_parsed.contains( inc_file ) ) {
                            already_parsed << inc_file;
                            parse_src_file_rec( ce, inc_file );
                        }
                    }
                    continue;
                }
            }
            if ( c[ 1 ] == 'p' and c[ 2 ] == 'r' and c[ 3 ] == 'a' and c[ 4 ] == 'g' and c[ 5 ] == 'm' and c[ 6 ] == 'a' and c[ 7 ] == ' ' ) {
                c += 8;
                if ( strncmp( c, "src_file ", 9 ) == 0 ) {
                    String o = get_pragma_arg( c += 9 );
                    String s = ce.find_src( o, current_dir );
                    if ( s.size() )
                        src_files << s;
                    else
                        cerrn << "Impossible to find src '" << o << "'";
                    continue;
                }
                if ( strncmp( c, "lib_path ", 9 ) == 0 ) {
                    lib_paths << ce.find_src( get_pragma_arg( c += 9 ), current_dir );
                    continue;
                }
                if ( strncmp( c, "lib_name ", 9 ) == 0 ) {
                    lib_names << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "fra_name ", 9 ) == 0 ) {
                    fra_names << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "inc_path ", 9 ) == 0 ) {
                    String path = ce.find_src( get_pragma_arg( c += 9 ), current_dir );
                    if ( not ( path.ends_with( '/' ) or path.ends_with( '\\' ) ) )
                        path += '/';
                    inc_paths << path;
                    continue;
                }
                if ( strncmp( c, "cpp_flag ", 9 ) == 0 ) {
                    cpp_flags << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "lnk_flag ", 9 ) == 0 ) {
                    lnk_flags << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "gpu_flag ", 9 ) == 0 ) {
                    gpu_flags << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "template ", 9 ) == 0 ) {
                    var_templ << get_pragma_arg( c += 9 );
                    continue;
                }
                if ( strncmp( c, "cxx_name ", 9 ) == 0 ) {
                    cxx_name << get_pragma_arg( c += 9 );
                    continue;
                }
            }
        }

        //
        ++c;
    }
}

END_METIL_LEVEL1_NAMESPACE;
