#ifndef AVOID_GEN
#include "NbArgsMethods.h"
#include "CppParser.h"

#include <sstream>
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


void CppParser::metil_type_bas_( char *&c ) { char *b = c; end_var( c ); if ( c - b > 15 ) bas.push_back_unique( String( b, c ) ); }
void CppParser::metil_type_ref_( char *&c ) { char *b = c; end_var( c ); if ( c - b > 15 ) ref.push_back_unique( String( b, c ) ); }
void CppParser::metil_type_cst_( char *&c ) { char *b = c; end_var( c ); if ( c - b > 15 ) cst.push_back_unique( String( b, c ) ); }

void CppParser::metil_gen_( char *&c ) { char *b = c; end_var( c ); if ( c - b > 10 ) gen.push_back_unique( DefStr( current_file, current_line, String( b, c ) ) ); }
void CppParser::metil_def_( char *&c ) { char *b = c; end_var( c ); if ( c - b > 10 ) def.push_back_unique( DefStr( current_file, current_line, String( b, c ) ) ); }


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
    for( int i = 0; i < bas.size(); ++i ) os << "extern Type " << bas[ i ].name << ";\n";
    for( int i = 0; i < ref.size(); ++i ) os << "extern Type " << ref[ i ].name << ";\n";
    for( int i = 0; i < cst.size(); ++i ) os << "extern Type " << cst[ i ].name << ";\n";
    os << "\n";
    os << "END_METIL_LEVEL1_NAMESPACE;\n";
    os << "\n";
    os << "#endif // AVOID_GEN\n";
    os << "#endif // METIL_GEN_H\n";
}

void CppParser::write_defi_type( std::ostream &os ) {
    typedef std::map<String,BasicVec<TypeStr,3> > TM;
    TM types_by_cons_kind;
    for( int i = 0; i < bas.size(); ++i ) types_by_cons_kind[ bas[ i ].subs ][ 0 ] = bas[ i ];
    for( int i = 0; i < ref.size(); ++i ) types_by_cons_kind[ ref[ i ].subs ][ 1 ] = ref[ i ];
    for( int i = 0; i < cst.size(); ++i ) types_by_cons_kind[ cst[ i ].subs ][ 2 ] = cst[ i ];

    //
    os << "// Type definition\n";
    for( TM::const_iterator iter = types_by_cons_kind.begin(); iter != types_by_cons_kind.end(); ++iter ) {
        // constructor type (e.f. Array, VoidString...)
        String type_cons = iter->first.substr( 0, iter->first.find( '_' ) );

        String cons = "type_constructor_" + iter->first;
        os << "static TypeConstructor_" << type_cons << " " << cons << ";\n";
        for( int i = 0; i < iter->second.size(); ++i ) {
            if ( iter->second[ i ].name.size() ) {
                os << "Type " << iter->second[ i ].name << "( &" << cons << ", \"" << iter->second[ i ].subs << '"';
                for( int j = 0; j < iter->second.size(); ++j )
                    os << ", " << ( iter->second[ j ].name.size() ? "&" + iter->second[ j ].name : "0" );

                static const char *t[] = { "Bas", "Cst", "Ref" };
                os << ", Type::" << t[ i ] << " );\n";
            }
        }
        os << "\n";
    }
}

void CppParser::write_defi_meth( std::ostream &os, const DefStr &def, bool gen, std::map<VTCond,String> &conds, std::map<String,String> &files ) {
    // condition
    VTCond vt_cond;
    def.cond( vt_cond.type, vt_cond.init );
    if ( conds.count( vt_cond ) == 0 ) {
        conds[ vt_cond ] = def.orig;
        os << "    static " << vt_cond.type << " cond_" << def.orig << ";\n";
        for( int j = 0; j < vt_cond.init.size(); ++j )
            os << "    cond_" << def.orig << vt_cond.init[ j ] << "\n";
        os << "\n";
    }

    if ( files.count( def.file ) == 0 ) {
        std::ostringstream ss; ss << "string_" << files.size();
        files[ def.file ] = ss.str();
        os << "    static const char *" << ss.str() << " = \"" << def.file << "\";\n";
        os << "\n";
    }

    // item
    os << "    static MethodFinder<MethodName_" << def.name << ">::Item item_" << def.orig << ";\n";
    os << "    item_" << def.orig << ".prev = MethodFinder<MethodName_" << def.name << ">::last;\n";
    os << "    item_" << def.orig << ".cond = &cond_" << conds[ vt_cond ] << ";\n";
    if ( gen ) {
        os << "    item_" << def.orig << ".meth = 0;\n";
        os << "    item_" << def.orig << ".gene = " << def.orig + ";\n";
    } else {
        os << "    item_" << def.orig << ".meth = " << def.orig + ";\n";
        os << "    item_" << def.orig << ".gene = 0;\n";
    }
    os << "    item_" << def.orig << ".file = " << files[ def.file ] << ";\n";
    os << "    item_" << def.orig << ".line = " << def.line << ";\n";
    os << "    item_" << def.orig << ".pert = " << def.pert() << ";\n";
    os << "    MethodFinder<MethodName_" << def.name << ">::last = &item_" << def.orig << ";\n";
    os << "\n";
}

void CppParser::write_defi_meth( std::ostream &os ) {
    // extern metil_def_... metil_gen_...
    os << "// method references\n";
    for( int i = 0; i < def.size(); ++i )
        os << "extern MethodName_" << def[ i ].name << "::TM " << def[ i ].orig << ";\n";
    for( int i = 0; i < gen.size(); ++i )
        os << "extern MethodMaker " << gen[ i ].orig << ";\n";
    os << "\n";
    os << "\n";

    // reg def
    os << "// reg_def\n";
    os << "void reg_def() {\n";
    std::map<VTCond,String> conds;
    std::map<String,String> files;
    for( int i = 0; i < def.size(); ++i )
        write_defi_meth( os, def[ i ], false, conds, files );
    for( int i = 0; i < gen.size(); ++i )
        write_defi_meth( os, gen[ i ], true , conds, files );
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
    for( int i = 0; i < bas.size(); ++i ) cons.insert( bas[ i ].cons );
    for( int i = 0; i < ref.size(); ++i ) cons.insert( ref[ i ].cons );
    for( int i = 0; i < cst.size(); ++i ) cons.insert( cst[ i ].cons );
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
