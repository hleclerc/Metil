/**
Goal : parse a .cpp file and generate
  - a .h with extern Type type...
  - a .cpp with extern Type type...

Can be called using e.g.

metil_parse `find . -name "*.cpp"`
*/
#ifndef AVOID_GEN
#include "CppParser.h"

#include <string>

#include <cstdio>
#include <cstring>
#include <fstream>

using namespace Metil;
using namespace Level1;
typedef std::string String;


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
    bool want_h = 1;
    bool want_c = 1;
    for( int num_arg = 1; num_arg < argc; ++num_arg ) {
        const char *arg = argv[ num_arg ];
        if ( arg[ 0 ] != '-' )
            cpp_files << argv[ num_arg ];
        else if ( arg[ 1 ] == 'h' and arg[ 2 ] == 0 )
            hn = argv[ ++num_arg ];
        else if ( arg[ 1 ] == 'c' and arg[ 2 ] == 0 )
            cn = argv[ ++num_arg ];
        else if ( strcmp( arg, "--no-h" ) == 0 )
            want_h = 0;
        else if ( strcmp( arg, "--no-c" ) == 0 )
            want_c = 0;
        else
            cmd += ' ' + String( argv[ num_arg ] );
    }

    // parse
    CppParser parser;
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
    if ( want_h ) {
        std::ofstream hf( "src/metil_gen.h" );
        parser.write_decl( hf );
    }

    // make .cpp
    if ( want_c ) {
        std::ofstream cf( "src/metil_gen.cpp" );
        parser.write_defi( cf, "metil_gen.h" );
    }

    return parser.err;
}
#endif // AVOID_GEN
