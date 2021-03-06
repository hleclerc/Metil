#include "StringHelp.h"
#include "../String.h"

#include <cstdlib>

BEG_METIL_LEVEL1_NAMESPACE;

bool equal( const char *a, const char *b ) {
    for( ; *a; ++a, ++b )
        if ( *a != *b )
            return false;
    return *b == 0;
}

int strcmp( const char *a, const char *b ) {
    for( ; *a; ++a, ++b ) {
        if ( *a < *b )
            return -1;
        if ( *a > *b )
            return +1;
    }
    return *b ? -1 : 0;
}

int strncmp( const char *a, const char *b, int n ) {
    for( int i = 0; i < n; ++a, ++b, ++i ) {
        if ( *a < *b )
            return -1;
        if ( *a > *b )
            return +1;
    }
    return 0;
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

char *strndup( const char *a, ST s ) {
    char *res = (char *)std::malloc( s + 1 );
    memcpy( res, a, s );
    res[ s ] = 0;
    return res;
}

ST find( const char *a, const char *b ) {
    for( int i = 0; a[ i ]; ++i ) {
        for( int j = 0; ; ++j ) {
            if ( b[ j ] == 0 )
                return i;
            if ( a[ i + j ] != b[ j ] )
                break;
        }
    }
    return -1;
}

ST find( const char *a, const char *b, ST len_a ) {
    for( int i = 0; i < len_a; ++i ) {
        for( int j = 0; ; ++j ) {
            if ( b[ j ] == 0 )
                return i;
            if ( i + j >= len_a )
                return -1;
            if ( a[ i + j ] != b[ j ] )
                break;
        }
    }
    return -1;
}

ST rfind( const char *a, const char *b ) {
    for( int i = strlen( a ) - strlen( b ); i >= 0; --i ) {
        for( int j = 0; ; ++j ) {
            if ( b[ j ] == 0 )
                return i;
            if ( a[ i + j ] != b[ j ] )
                break;
        }
    }
    return -1;
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
