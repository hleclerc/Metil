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

void to_base_64( String &os, const void *data_, ST size ) {
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

END_METIL_NAMESPACE;
