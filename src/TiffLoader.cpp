#include "Level1/ArrayHeader.h"
#include "Level1/StringHelp.h"
#include "MachineId.h"
#include "BasicVec.h"
#include "String.h"

#include <tiffio.h>

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name tiff
#endif

BEG_METIL_NAMESPACE;

extern "C" void load_tiff( Level1::MO &res, const String &filename, const MachineId *machine ) {
    TIFF *tif = TIFFOpen( filename.c_str(), "r" );
    if ( not tif )
        throw "impossible to read " + filename + " using libtiff";

    //
    PI32 w = 0, h = 0, bps = 8;
    TIFFGetField( tif, TIFFTAG_IMAGEWIDTH     , &w   );
    TIFFGetField( tif, TIFFTAG_IMAGELENGTH    , &h   );
    TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE  , &bps );

    ST size[ 2 ];
    size[ 0 ] = w;
    size[ 1 ] = h;

    // new Array
    res.type = bps == 16 ? &Level1::metil_type_bas_Array_4PI16_2_m_m_m_m_CptUse : &Level1::metil_type_bas_Array_3PI8_2_m_m_m_m_CptUse;
    char *data = (char *)CM_2( allocate, res, Level1::REF_Vec( Number<2>(), size ) );

    ST line_size = size[ 0 ] * bps / 8;
    tdata_t buf = _TIFFmalloc( TIFFScanlineSize( tif ) );
    for( PI32 y = 0; y < h; ++y ) {
        TIFFReadScanline( tif, buf, y );
        Level1::memcpy( data + line_size * y, buf, line_size ); //, cudaMemcpyHostToDevice
    }
    _TIFFfree( buf );

    TIFFClose( tif );
}

END_METIL_NAMESPACE;
