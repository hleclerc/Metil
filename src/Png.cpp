#include "StringHelp.h"
#include "Malloc.h"
#include "String.h"
#include "Png.h"

#include <zlib.h>

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name z
#endif


BEG_METIL_NAMESPACE;

// code for the crc stolen from libpng.org
static unsigned long crc_table[256];

static int crc_table_computed = 0;

static void make_crc_table() {
    for ( int n = 0; n < 256; ++n ) {
        unsigned long c = n;
        for ( int k = 0; k < 8; ++k ) {
            if ( c & 1 )
                c = 0xedb88320L ^ ( c >> 1 );
            else
                c = c >> 1;
        }
        crc_table[ n ] = c;
    }
    crc_table_computed = 1;
}

static unsigned long update_crc( unsigned long crc, unsigned char *buf, int len ) {
    unsigned long c = crc;
    if ( not crc_table_computed )
        make_crc_table();
    for ( int n = 0; n < len; n++ )
        c = crc_table[ ( c ^ buf[ n ] ) & 0xff ] ^ ( c >> 8 );
    return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
static unsigned crc( char *buf, int len ) {
  return update_crc( 0xffffffffL, (unsigned char *)buf, len ) ^ 0xffffffffL;
}

static char header[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

static void png_memcpy( char *&dst, const char *src, ST len ) {
    Level1::memcpy( dst, src, len );
    dst += len;
}

template<class T>
static void png_append( char *&dst, const T &src ) {
    const unsigned char *tmp = reinterpret_cast<const unsigned char *>( &src );
    for( int i = sizeof( T ) - 1; i >= 0; --i )
        *(dst++) = tmp[ i ];
}

Ps<char> make_png( unsigned *img, int w, int h ) {
    int ws = 1 + sizeof( unsigned ) * w;
    ST tmp_rese = ws * h;
    Bytef *tmp = (Bytef *)MALLOC( tmp_rese );

    // filter
    for( int y = 0; y < h; ++y ) {
        tmp[ ws * y + 0 ] = 0; // filter type
        Level1::memcpy( tmp + ws * y + 1, img + w * y, w * sizeof( unsigned ) ); // data
    }

    // compression
    ST dst_rese = ws * h;
    Bytef *dst = (Bytef *)malloc( dst_rese );
    uLongf dst_len = dst_rese;
    compress( dst, &dst_len, tmp, ws * h );

    // allocation
    Ps<char> res;
    res.rese  = sizeof( header );
    res.rese += 8 +      13 + 4;
    res.rese += 8 + dst_len + 4;
    res.rese += 8 +       0 + 4;
    res.data = (char *)MALLOC( res.rese );
    res.size = 1;

    // streaming
    char *ptr = res.data, *beg;

    // header
    png_memcpy( ptr, header, sizeof( header ) );

    // IHDR
    png_append( ptr, 13 ); // size
    beg = ptr;
    png_memcpy( ptr, "IHDR", 4 );
    png_append( ptr, w ); // width
    png_append( ptr, h ); // height
    png_append( ptr, SI8( 8 ) ); // bit_depth
    png_append( ptr, SI8( 6 ) ); // color_type = 6; // RGBA ( RGB -> 2 )
    png_append( ptr, SI8( 0 ) ); // compression_method = 0;
    png_append( ptr, SI8( 0 ) ); // filter_method = 0;
    png_append( ptr, SI8( 0 ) ); // interlace_method = 0;
    png_append( ptr, crc( beg, ptr - beg ) ); // crc

    // IDAT
    png_append( ptr, SI32( dst_len ) ); // size
    beg = ptr;
    png_memcpy( ptr, "IDAT", 4 );
    png_memcpy( ptr, (char *)dst, dst_len );
    png_append( ptr, crc( beg, ptr - beg ) ); // crc

    // IEND
    png_append( ptr, 0 ); // size
    beg = ptr;
    png_memcpy( ptr, "IEND", 4 );
    png_append( ptr, crc( beg, ptr - beg ) ); // crc

    // free
    FREE( tmp, tmp_rese );
    FREE( dst, dst_rese );

    res.size = ptr - res.data;
    return res;
}

END_METIL_NAMESPACE;
