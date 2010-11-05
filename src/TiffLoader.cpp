#include "Level1/ArrayHeader.h"
#include "Level1/StringHelp.h"
#include "BasicVec.h"
#include "String.h"

#include <tiffio.h>

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name tiff
#endif

BEG_METIL_NAMESPACE;

extern "C" Level1::MO load_tiff( const String &filename ) {
    TIFF *tif = TIFFOpen( filename.c_str(), "r" );
    if ( not tif )
        throw "impossible to read " + filename + " using libtiff";

    // int bits_per_sample = type->nb_bits_in_mantissa() > 8 ? 16 : 8;
    PI32 w, h, bps;
    TIFFGetField( tif, TIFFTAG_IMAGEWIDTH     , &w );
    TIFFGetField( tif, TIFFTAG_IMAGELENGTH    , &h );
    TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE  , &bps );

    ST size[ 2 ];
    size[ 0 ] = w;
    size[ 1 ] = h;

    // new Array
    // cudaMalloc( &data, sizeof( float ) * size[ 0 ] * size[ 1 ] );
    Level1::MO res;
    PI8 *data = reinterpret_cast<PI8 *>( init_dyn_array( res, size, Number<2>(), bps == 16 ? type_ptr<PI16>() : type_ptr<PI8>() ) );

    ST line_size = size[ 0 ] * bps / 8;
    tdata_t buf = _TIFFmalloc( TIFFScanlineSize( tif ) );
    for( PI32 y = 0; y < h; ++y ) {
        TIFFReadScanline( tif, buf, y );
        Level1::memcpy( data + line_size * y, buf, line_size ); //, cudaMemcpyHostToDevice
    }
    _TIFFfree( buf );

    TIFFClose( tif );

    return res;
}

END_METIL_NAMESPACE;
