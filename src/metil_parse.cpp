/**
Goal : parse a .cpp file and generate
  - a .h with extern Type type...
  - a .cpp with extern Type type...

Can be called using e.g.

metil_parse `find . -name "*.cpp"`
*/
#ifndef AVOID_GEN
#include "BasicVec.h"
#include "Dout.h"

#include <string>

#include <map>
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace Metil;
typedef std::string String;

/**
*/
struct Parser {
    Parser() : err( 0 ) {}

    void end_var( char *&c ) {
        while ( ( *c >= 'A' and *c <= 'Z' ) or ( *c >= 'a' and *c <= 'z' ) or ( *c >= '0' and *c <= '9'  ) or *c == '_' )
            ++c;
    }

    void metil_type_bas_( char *&c ) { char *b = c; end_var( c ); bas.push_back_unique( String( b, c ) ); }
    void metil_type_ref_( char *&c ) { char *b = c; end_var( c ); ref.push_back_unique( String( b, c ) ); }
    void metil_type_cst_( char *&c ) { char *b = c; end_var( c ); cst.push_back_unique( String( b, c ) ); }

    void metil_gen_( char *&c ) { char *b = c; end_var( c ); gen.push_back_unique( String( b, c ) ); }
    void metil_def_( char *&c ) { char *b = c; end_var( c ); def.push_back_unique( String( b, c ) ); }

    void parse( char *c ) {
        for( ; *c; ++c ) {
            // python src/parser_if.h.py > src/parser_if.h
            #include "parser_if.h"
        }
    }

    void write_decl( std::ostream &os ) {
        os << "// generated file. Do not edit\n";
        os << "#ifndef METIL_GEN_H\n";
        os << "#define METIL_GEN_H\n";
        os << "#ifndef AVOID_GEN\n";
        os << "\n";
        os << "#include \"Type.h\"\n";
        os << "\n";
        os << "BEG_METIL_LEVEL1_NAMESPACE;\n";
        os << "\n";
        for( unsigned i = 0; i < bas.size(); ++i ) os << "extern Type " << bas[ i ] << ";\n";
        for( unsigned i = 0; i < ref.size(); ++i ) os << "extern Type " << ref[ i ] << ";\n";
        for( unsigned i = 0; i < cst.size(); ++i ) os << "extern Type " << cst[ i ] << ";\n";
        os << "\n";
        os << "END_METIL_LEVEL1_NAMESPACE;\n";
        os << "\n";
        os << "#endif // AVOID_GEN\n";
        os << "#endif // METIL_GEN_H\n";
    }

    void write_defi( std::ostream &os, String h ) {
        os << "// generated file. Do not edit\n";
        os << "#ifndef AVOID_GEN\n";
        os << "\n";

        typedef std::map<String,BasicVec<String,3> > TM;
        TM types_by_cons_kind;
        for( unsigned i = 0; i < bas.size(); ++i ) types_by_cons_kind[ bas[ i ] ][ 0 ] = bas[ i ];
        for( unsigned i = 0; i < ref.size(); ++i ) types_by_cons_kind[ ref[ i ] ][ 1 ] = ref[ i ];
        for( unsigned i = 0; i < cst.size(); ++i ) types_by_cons_kind[ cst[ i ] ][ 2 ] = cst[ i ];

        // includes
        os << "#include \"" << h << "\"\n";
        os << "\n";
        int o = 15 /* length of "metil_type_bas_" */;
        for( TM::const_iterator iter = types_by_cons_kind.begin(); iter != types_by_cons_kind.end(); ++iter ) {
            // constructor type (e.f. Array, VoidString...)
            String type_cons = iter->first.substr( o );
            type_cons = type_cons.substr( 0, type_cons.find( '_' ) );
            os << "#include \"TypeConstructor_" << type_cons << ".h\"\n";
        }

        // type definitions
        os << "\n";
        os << "BEG_METIL_LEVEL1_NAMESPACE;\n";
        os << "\n";
        for( TM::const_iterator iter = types_by_cons_kind.begin(); iter != types_by_cons_kind.end(); ++iter ) {
            // constructor type (e.f. Array, VoidString...)
            String type_cons = iter->first.substr( o );
            type_cons = type_cons.substr( 0, type_cons.find( '_' ) );

            String cons = "type_constructor_" + iter->first.substr( o );
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
        os << "\n";
        os << "END_METIL_LEVEL1_NAMESPACE;\n";
        os << "\n";
        os << "#endif // AVOID_GEN\n";
    }

    BasicVec<String> bas;
    BasicVec<String> ref;
    BasicVec<String> cst;
    BasicVec<String> gen;
    BasicVec<String> def;
    bool err;
};

char *get_data( FILE *f ) {
    char *res = 0;
    size_t size = 0;
    while ( true ) {
        char tmp[ 4096 ];
        size_t r = fread( tmp, 1, sizeof tmp, f );
        res = (char *)std::realloc( res, size + r + 1 );
        if ( r == 0 ) {
            res[ size ] = 0;
            return res;
        }
        std::memcpy( res + size, tmp, r );
        size += r;
    }
}

int main( int argc, char **argv ) {
    String cmd = "g++ -E -DAVOID_GEN";
    String hn, cn;
    BasicVec<String> cpp_files;
    for( int num_arg = 1; num_arg < argc; ++num_arg ) {
        const char *arg = argv[ num_arg ];
        if ( arg[ 0 ] != '-' )
            cpp_files << argv[ num_arg ];
        else if ( arg[ 1 ] == 'h' and arg[ 2 ] == 0 )
            hn = argv[ ++num_arg ];
        else if ( arg[ 1 ] == 'c' and arg[ 2 ] == 0 )
            cn = argv[ ++num_arg ];
        else
            cmd += ' ' + String( argv[ num_arg ] );
    }
    // DOUT( hn );
    // DOUT( cn );

    // parse
    Parser parser;
    for( int num = 0; num < cpp_files.size(); ++num ) {
        // get result from g++ -E ...
        String exe = cmd + ' ' + cpp_files[ num ];
        DOUT( exe );

        FILE *f = popen( exe.c_str(), "r" );
        if ( not f )
            return 1;
        char *c = get_data( f );
        std::fclose( f );

        parser.parse( c );

        std::free( c );
    }

    // make .h
    std::ofstream hf( "src/metil_gen.h" );
    parser.write_decl( hf );

    // make .cpp
    std::ofstream cf( "src/metil_gen.cpp" );
    parser.write_defi( cf, "metil_gen.h" );

    return parser.err;
}
#endif // AVOID_GEN
