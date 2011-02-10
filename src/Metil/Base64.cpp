#include "BasicSplittedVec.h"
#include "Base64.h"

BEG_METIL_NAMESPACE;

static const char *base_64_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void encode_block_3( unsigned char *dst, const unsigned char *in ) {
    dst[0] = base_64_str[ in[ 0 ] >> 2 ];
    dst[1] = base_64_str[ ( ( in[ 0 ] & 0x03 ) << 4 ) | ( ( in[ 1 ] & 0xf0 ) >> 4 ) ];
    dst[2] = base_64_str[ ( ( in[ 1 ] & 0x0f ) << 2 ) | ( ( in[ 2 ] & 0xc0 ) >> 6 ) ];
    dst[3] = base_64_str[ in[ 2 ] & 0x3f ];
}

static void encode_block_2( unsigned char *dst, const unsigned char *in ) {
    dst[0] = base_64_str[ in[ 0 ] >> 2 ];
    dst[1] = base_64_str[ ( ( in[ 0 ] & 0x03 ) << 4 ) | ( ( in[ 1 ] & 0xf0 ) >> 4) ];
    dst[2] = base_64_str[ ( ( in[ 1 ] & 0x0f ) << 2 ) ];
    dst[3] = '=';
}

static void encode_block_1( unsigned char *dst, const unsigned char *in ) {
    dst[0] = base_64_str[ in[0] >> 2 ];
    dst[1] = base_64_str[ ( ( in[0] & 0x03 ) << 4) ];
    dst[2] = '=';
    dst[3] = '=';
}

void base_64_encode( String &os, const void *data_, ST size ) {
    const unsigned char *data = reinterpret_cast<const unsigned char *>( data_ );
    BasicSplittedVec<unsigned char,1024> tmp;
    ST i = 0;
    for( ; i < size - 2; i += 3 )
        encode_block_3( tmp.get_room( 4 ), data + i );
    for( ; i < size - 1; i += 2 )
        encode_block_2( tmp.get_room( 4 ), data + i );
    for( ; i < size - 0; i += 1 )
        encode_block_1( tmp.get_room( 4 ), data + i );
    for( BasicSplittedVec<unsigned char,1024>::Item *item = &tmp.first; item; item = item->next )
        os.write( item->ptr(), item->size() );
}

void decode_block( const unsigned char *in, unsigned char *out ) {
    out[ 0 ] = in[0] << 2 | in[1] >> 4;
    out[ 1 ] = in[1] << 4 | in[2] >> 2;
    out[ 2 ] = ((in[2] << 6) & 0xc0) | in[3];
}

/*
 Generated with
    static const char *base_64_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    BasicVec<int> v( Size(), 256, 0 );
    int i = 0;
    for( char *b = base_64_str; *b; ++b, ++i )
        v[ *b ] = i;
    for( int i = 0; i < v.size(); ++i )
        cout << ( i % 16 ? " " : "\n" ) << v[ i ] << ",";
*/
static const unsigned char cd_64[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0,
    0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void base_64_decode( String &os, const void *data_, ST size ) {
    const unsigned char *data = reinterpret_cast<const unsigned char *>( data_ );
    NewString n( size * 3 / 4 );
    unsigned char *n_ptr = (unsigned char *)n.ptr();
    for( ST i = 0; i < size; n_ptr += 3 ) {
        unsigned char in[ 4 ];
        for( int o = 0; o < 4; ++o, ++i )
            in[ o ] = cd_64[ data[ i ] ];
        decode_block( in, n_ptr );
    }
    os = n;
}

END_METIL_NAMESPACE;
