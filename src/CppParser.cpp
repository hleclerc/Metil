#ifndef AVOID_GEN
#include "NbArgsMethods.h"
#include "CppParser.h"

#include <sstream>
#include <map>
#include <set>

BEG_METIL_LEVEL1_NAMESPACE;

CppParser::CppParser() : err( 0 ) {
    current_line = 0;
}

bool is_a_cvar( char c ) {
    return ( c >= 'A' and c <= 'Z' ) or ( c >= 'a' and c <= 'z' ) or ( c >= '0' and c <= '9'  ) or c == '_';
}

static void end_var( char *&c ) {
    while ( is_a_cvar( *c ) )
        ++c;
}

//static int nb_args( const CppParser::String &str ) {
//    #define DECL_MET( T, N ) if ( str == #N ) return NB_ARGS_METHOD_##T
//    #include "DeclMethods.h"
//    #undef DECL_MET
//    ERROR( "Weird method name %s", str.c_str() );
//    return 0;
//}


void CppParser::metil_type_bas_( char *&c ) { char *b = c; end_var( c ); bas.push_back_unique( String( b, c ) ); }
void CppParser::metil_type_ref_( char *&c ) { char *b = c; end_var( c ); ref.push_back_unique( String( b, c ) ); }
void CppParser::metil_type_cst_( char *&c ) { char *b = c; end_var( c ); cst.push_back_unique( String( b, c ) ); }

void CppParser::metil_gen_( char *&c ) { char *b = c; end_var( c ); gen.push_back_unique( DefStr( current_file, current_line, String( b, c ) ) ); }
void CppParser::metil_def_( char *&c ) { char *b = c; end_var( c ); def.push_back_unique( DefStr( current_file, current_line, String( b, c ) ) ); }


void CppParser::parse( char *c ) {
    for( ; *c; ++c ) {
        current_line += *c == '\n';
        // we do not parse "..."
        if ( *c == '"' ) {
            while ( *( ++c ) and *c != '"' );
        } else if ( c[ 0 ] == '\n' and c[ 1 ] == '#' and c[ 2 ] == ' ' ) {
            // std::sscanf( c + 2, "%i %s", current_line,  );
            c += 3;
            while ( *c == ' ' )
                ++c;
            current_line = 0;
            for( ; *c >= '0' and *c <= '9'; ++c )
                current_line = current_line * 10 + ( *c - '0' );
            while ( *c == ' ' )
                ++c;
            if ( *c == '"' ) {
                char *b = ++c;
                while ( *c != '"' and *c != '\n' )
                    ++c;
                current_file = String( b, c );
            }
            while ( *c != '\n' and *c )
                ++c;
        } else if ( not is_a_cvar( c[ 0 ] ) ) {
            // python src/parser_if.h.py > src/parser_if.h
            #include "parser_if.h"
        }
    }
}

void CppParser::write_decl( std::ostream &os ) {
    os << "// generated file. Do not edit\n";
    os << "#ifndef METIL_GEN_H\n";
    os << "#define METIL_GEN_H\n";
    os << "#ifndef AVOID_GEN\n";
    os << "\n";
    os << "#include \"Type.h\"\n";
    os << "\n";
    os << "BEG_METIL_LEVEL1_NAMESPACE;\n";
    os << "\n";
    // met
    os << "void reg_def();\n";
    os << "\n";
    // types
    for( int i = 0; i < bas.size(); ++i ) os << "extern Type " << bas[ i ] << ";\n";
    for( int i = 0; i < ref.size(); ++i ) os << "extern Type " << ref[ i ] << ";\n";
    for( int i = 0; i < cst.size(); ++i ) os << "extern Type " << cst[ i ] << ";\n";
    os << "\n";
    os << "END_METIL_LEVEL1_NAMESPACE;\n";
    os << "\n";
    os << "#endif // AVOID_GEN\n";
    os << "#endif // METIL_GEN_H\n";
}

void CppParser::write_defi_type( std::ostream &os ) {
    typedef std::map<String,BasicVec<String,3> > TM;
    TM types_by_cons_kind;
    int o = 15 /* length of "metil_type_bas_" */;
    for( int i = 0; i < bas.size(); ++i ) types_by_cons_kind[ bas[ i ].substr( o ) ][ 0 ] = bas[ i ];
    for( int i = 0; i < ref.size(); ++i ) types_by_cons_kind[ ref[ i ].substr( o ) ][ 1 ] = ref[ i ];
    for( int i = 0; i < cst.size(); ++i ) types_by_cons_kind[ cst[ i ].substr( o ) ][ 2 ] = cst[ i ];

    //
    os << "// Type definition\n";
    for( TM::const_iterator iter = types_by_cons_kind.begin(); iter != types_by_cons_kind.end(); ++iter ) {
        // constructor type (e.f. Array, VoidString...)
        String type_cons = iter->first.substr( 0, iter->first.find( '_' ) );

        String cons = "type_constructor_" + iter->first;
        os << "static TypeConstructor_" << type_cons << " " << cons << ";\n";
        for( int i = 0; i < iter->second.size(); ++i ) {
            if ( iter->second[ i ].size() ) {
                os << "Type " << iter->second[ i ] << "( &" << cons << ", \"" << iter->second[ i ].substr( o ) << '"';
                for( int j = 0; j < iter->second.size(); ++j )
                    os << ", " << ( iter->second[ j ].size() ? "&" + iter->second[ j ] : "0" );

                static const char *t[] = { "Bas", "Cst", "Ref" };
                os << ", Type::" << t[ i ] << " );\n";
            }
        }
    }
}

void CppParser::write_defi_meth( std::ostream &os ) {
    // extern metil_def_...
    os << "// method references\n";
    for( int i = 0; i < def.size(); ++i )
        os << "extern MethodName_" << def[ i ].name << "::TM " << def[ i ].orig << ";";
    os << "\n";
    os << "\n";

    // reg def
    os << "// reg_def\n";
    os << "void reg_def() {\n";
    std::map<String,String> conds;
    std::map<String,String> files;
    for( int i = 0; i < def.size(); ++i ) {
        if ( i ) os << "\n";

        // condition
        String t_cond = def[ i ].cond();
        if ( conds.count( t_cond ) == 0 ) {
            conds[ t_cond ] = def[ i ].orig;
            os << "    static " << t_cond << " cond_" << def[ i ].orig << ";\n";
            os << "\n";
        }

        if ( files.count( def[ i ].file ) == 0 ) {
            std::ostringstream ss; ss << "string_" << files.size();
            files[ def[ i ].file ] = ss.str();
            os << "    static const char *" << ss.str() << " = \"" << def[ i ].file << "\";\n";
            os << "\n";
        }

        // item
        os << "    static MethodFinder<MethodName_" << def[ i ].name << ">::Item item_" << def[ i ].orig << ";\n";
        os << "    item_" << def[ i ].orig << ".prev = MethodFinder<MethodName_" << def[ i ].name << ">::last;\n";
        os << "    item_" << def[ i ].orig << ".cond = &cond_" << conds[ t_cond ] << ";\n";
        os << "    item_" << def[ i ].orig << ".meth = " << def[ i ].orig + ";\n";
        os << "    item_" << def[ i ].orig << ".file = " << files[ def[ i ].file ] << ";\n";
        os << "    item_" << def[ i ].orig << ".line = " << def[ i ].line << ";\n";
        os << "    item_" << def[ i ].orig << ".pert = " << def[ i ].pert() << ";\n";
        os << "    MethodFinder<MethodName_" << def[ i ].name << ">::last = &item_" << def[ i ].orig << ";\n";
    }
    os << "}\n";
}

void CppParser::write_defi( std::ostream &os, String h ) {
    os << "// generated file. Do not edit\n";
    os << "#ifndef AVOID_GEN\n";
    os << "\n";
    os << "#include \"" << h << "\"\n";
    os << "#include \"MethodFinder.h\"\n";
    os << "\n";

    // include TypeConstructor_xx.h
    std::set<String> cons;
    int o = 15 /* length of "metil_type_bas_" */;
    for( int i = 0; i < bas.size(); ++i ) cons.insert( bas[ i ].substr( o ) );
    for( int i = 0; i < ref.size(); ++i ) cons.insert( ref[ i ].substr( o ) );
    for( int i = 0; i < cst.size(); ++i ) cons.insert( cst[ i ].substr( o ) );
    for( unsigned i = 0; i < def.size(); ++i ) {
        BasicVec<String> tc = def[ i ].type_constructors();
        for( int j = 0; j < tc.size(); ++j )
            cons.insert( tc[ j ] );
    }
    for( unsigned i = 0; i < gen.size(); ++i ) {
        BasicVec<String> tc = gen[ i ].type_constructors();
        for( int j = 0; j < tc.size(); ++j )
            cons.insert( tc[ j ] );
    }

    for( std::set<String>::const_iterator iter = cons.begin(); iter != cons.end(); ++iter )
        os << "#include \"TypeConstructor_" << *iter << ".h\"\n";

    //
    os << "\n";
    os << "BEG_METIL_LEVEL1_NAMESPACE;\n";
    os << "\n";
    write_defi_type( os << "\n" );
    write_defi_meth( os << "\n" );
    os << "\n";
    os << "END_METIL_LEVEL1_NAMESPACE;\n";
    os << "\n";
    os << "#endif // AVOID_GEN\n";
}

END_METIL_LEVEL1_NAMESPACE;
#endif // AVOID_GEN
