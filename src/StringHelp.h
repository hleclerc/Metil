#ifndef STRINGHELP_H
#define STRINGHELP_H

#include "TypeConfig.h"
#include "Number.h"

BEG_METIL_LEVEL1_NAMESPACE;

bool equal( const char *a, const char *b );
ST strlen( const char *a );
char *strdup( const char *a );
char *strndup( const char *a, ST s );
ST find( const char *a, const char *b );
ST find( const char *a, const char *b, ST len_a );

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
