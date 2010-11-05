#ifndef STRINGHELP_H
#define STRINGHELP_H

#include "TypeConfig.h"
#include "Number.h"

BEG_METIL_LEVEL1_NAMESPACE;

//
bool equal( const char *a, const char *b );
ST strlen( const char *a );
int strcmp( const char *a, const char *b );
int strncmp( const char *a, const char *b, int n );
char *strdup( const char *a );
char *strndup( const char *a, ST s );
ST find( const char *a, const char *b );
ST find( const char *a, const char *b, ST len_a );
ST rfind( const char *a, const char *b );

// char property
inline bool is_a_number( char a ) { return a >= '0' and a <= '9'; }
inline bool is_a_lower_letter ( char a ) { return a >= 'a' and a <= 'z'; }
inline bool is_an_upper_letter( char a ) { return a >= 'A' and a <= 'Z'; }
inline bool is_a_letter( char a ) { return is_a_lower_letter ( a ) or is_an_upper_letter( a ) or a == '_'; }
inline bool is_a_space ( char a ) { return a == ' ' or a == '\t' or a == '\n' or a == '\r'; }
inline bool is_a_letter_or_a_number( char a ) { return is_a_letter( a ) or is_a_number( a ); }

// memcpy
void memcpy( void *a, const void *b, ST size );

template<int n>
inline void memcpy( void *a, const void *b, Number<n> ) {
    for( int i = 0; i < n; ++i )
        reinterpret_cast<char *>( a )[ i ] = reinterpret_cast<const char *>( b )[ i ];
}

inline void memcpy( void *a, const void *b, Number<1> ) {
    *reinterpret_cast<SI8 *>( a ) = *reinterpret_cast<const SI8 *>( b );
}

inline void memcpy( void *a, const void *b, Number<2> ) {
    *reinterpret_cast<SI16 *>( a ) = *reinterpret_cast<const SI16 *>( b );
}

inline void memcpy( void *a, const void *b, Number<4> ) {
    *reinterpret_cast<SI32 *>( a ) = *reinterpret_cast<const SI32 *>( b );
}

inline  void memcpy( void *a, const void *b, Number<8> ) {
    *reinterpret_cast<SI64 *>( a ) = *reinterpret_cast<const SI64 *>( b );
}

END_METIL_LEVEL1_NAMESPACE;

#endif // STRINGHELP_H
