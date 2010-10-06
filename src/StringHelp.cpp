#include "StringHelp.h"

#include <cstdlib>

BEG_METIL_LEVEL1_NAMESPACE;

bool equal( const char *a, const char *b ) {
    for( ; *a; ++a, ++b )
        if ( *a != *b )
            return false;
    return *b == 0;
}

ST strlen( const char *a ) {
    ST res = 0;
    while ( a[ res ] )
        ++res;
    return res;
}

char *strdup( const char *a ) {
    ST s = strlen( a );
    char *res = (char *)std::malloc( s + 1 );
    memcpy( res, a, s );
    res[ s ] = 0;
    return res;
}

void memcpy( void *a, const void *b, ST size ) {
    char *dst = reinterpret_cast<char *>( a );
    const char *src = reinterpret_cast<const char *>( b );
    ST i = 0;
    for( ; i < size - 7; i += 8 )
        memcpy( dst + i, src + i, Number<8>() );
    for( ; i < size - 3; i += 4 )
        memcpy( dst + i, src + i, Number<4>() );
    for( ; i < size - 1; i += 2 )
        memcpy( dst + i, src + i, Number<2>() );
    for( ; i < size - 0; i += 1 )
        memcpy( dst + i, src + i, Number<1>() );
}

END_METIL_LEVEL1_NAMESPACE;
