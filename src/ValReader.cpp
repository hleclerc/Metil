#include "StringHelp.h"
#include "ValReader.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

//static bool is_a_number( char t ) { return t >= '0' and t <= '9'; }
//static bool is_a_letter( char t ) { return t == '_' or ( t >= 'a' and t <= 'z' ) or ( t >= 'A' and t <= 'Z' ); }
// static bool is_a_letter_or_a_number( char t ) { return is_a_letter( t ) or is_a_number( t ); }

ValReader::ValReader( String str, BasicVec<String> &symbols ) : symbols( symbols ) {
    const char *s = str.c_str();
    if ( not s )
        return;

    // - ...
    if ( *s == '-' ) {
        ValReader v( s + 1, symbols );
        res = - v.res;
        return;
    }

    // number
    if ( is_a_number( *s ) ) {
        PRINT( str );
        PRINT( s );
        PRINT( *s - '0' );
        res = *s - '0';
        while ( is_a_number( *(++s) ) )
            res = 10 * res + ( *s - '0' );

        if ( *s == '.' ) { // -> floating point
            Val d = 1;
            while ( is_a_number( *(++s) ) ) {
                res = 10 * res + ( *s - '0' );
                d *= 10;
            }
            res /= d;
        }

        if ( *s == 'e' ) { // -> e...
            ValReader expo( s + 1, symbols );
            res *= pow_by_positive_integer( 10, expo.res );
        }
    }

    //
    if ( is_a_letter( *s ) ) {
        //const char *t = s;
        //while ( is_a_letter_or_a_number( *(++s) ) );
        TODO; // res = Level1::NEW_Symbol( NewString( t, s ) );
    }
}

END_METIL_LEVEL1_NAMESPACE;
