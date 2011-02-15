#include "TypeConstructor_TiffLoader.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_exec_node__when__a__isa__TiffLoader__pert__1( MethodWriter &mw ) {
    mw.add_include( "String.h" );
    mw.add_include( "Level1/StringHelp.h" );
    mw.add_include( "tiffio.h" );

    mw.add_preliminary( "#ifdef METIL_COMP_DIRECTIVE\n" );
    mw.add_preliminary( "#pragma lib_name tiff\n" );
    mw.add_preliminary( "#endif // METIL_COMP_DIRECTIVE\n" );

    // open
    static_cast<TypeConstructor_TiffLoader *>( mw.type[ 0 ]->constructor )->write_header( mw, "l", mw.arg[ 0 ].data );
    mw.n << "String &filename = static_cast<String &>( l->ch( 0 ) );";
    mw.n << "TIFF *tif = TIFFOpen( filename.c_str(), \"r\" );";
    mw.n << "if ( not tif )";
    mw.n << "    throw \"impossible to read \" + filename + \" using libtiff\";";

    // size, bps
    mw.n << "PI32 w = 0, h = 0, bps = 8;";
    mw.n << "TIFFGetField( tif, TIFFTAG_IMAGEWIDTH     , &w   );";
    mw.n << "TIFFGetField( tif, TIFFTAG_IMAGELENGTH    , &h   );";
    mw.n << "TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE  , &bps );";

    mw.n << "ST size[ 2 ];";
    mw.n << "size[ 0 ] = w;";
    mw.n << "size[ 1 ] = h;";
    mw.n << "DOUT( w );";

    // type
    mw.n << "l->op_mp.type = bps == 16 ? &Level1::metil_type_bas_Array_8Int_p_16_2_m_m_m_m_CptUse : &Level1::metil_type_bas_Array_7Int_p_8_2_m_m_m_m_CptUse;";

    // new Array
    mw.n << "char *data = (char *)CM_2( allocate_2, l->op_mp, Level1::REF_Vec( Number<2>(), size ) );";

    mw.n << "ST line_size = size[ 0 ] * bps / 8;";
    mw.n << "tdata_t buf = _TIFFmalloc( TIFFScanlineSize( tif ) );";
    mw.n << "for( PI32 y = 0; y < h; ++y ) {";
    mw.n << "    TIFFReadScanline( tif, buf, y );";
    mw.n << "    Level1::memcpy( data + line_size * y, buf, line_size );";
    mw.n << "}";
    mw.n << "_TIFFfree( buf );";

    mw.n << "TIFFClose( tif );";
    mw.ret() << "0;";
}

int TypeConstructor_TiffLoader::Owcp_size() const {
    return 1;
}

END_METIL_LEVEL1_NAMESPACE;
