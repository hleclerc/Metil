#include "ImgItemGrid.h"
#include "CString.h"

/// need libtiff
#include <tiffio.h>

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name tiff
#endif


namespace Metil {

extern "C" void write_tif( const CString &filename, const ImgItemGrid *img ) {
    TIFF *tif = TIFFOpen( filename.data(), "w" );
    if ( not tif )
        throw "impossible to write " + filename + " using libtiff";

    const Type *type = img->type();
    int bits_per_sample = type->nb_bits_in_mantissa() > 8 ? 16 : 8;
    TIFFSetField( tif, TIFFTAG_IMAGEWIDTH     , img->size( 0 )      );
    TIFFSetField( tif, TIFFTAG_IMAGELENGTH    , img->size( 1 )      );
    TIFFSetField( tif, TIFFTAG_SAMPLESPERPIXEL, img->nb_planes()    );
    TIFFSetField( tif, TIFFTAG_BITSPERSAMPLE  , bits_per_sample     );
    TIFFSetField( tif, TIFFTAG_ORIENTATION    , ORIENTATION_TOPLEFT ); // set the origin of the image.
    TIFFSetField( tif, TIFFTAG_PLANARCONFIG   , PLANARCONFIG_CONTIG );
    TIFFSetField( tif, TIFFTAG_PHOTOMETRIC    , img->nb_planes() == 1 ? PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB );
    TIFFSetField( tif, TIFFTAG_ROWSPERSTRIP   , TIFFDefaultStripSize( tif, img->size( 0 ) * img->nb_planes() ) );

    if ( bits_per_sample == 16 ) {
        Unsigned16 *d = reinterpret_cast<Unsigned16 *>( img->data() );
        for( int row=0; row < img->size( 1 ); ++row, d += img->internal_width() )
            TIFFWriteScanline( tif, const_cast<Unsigned16 *>( d ), row, 0 );
    } else {
        Unsigned8 *d = reinterpret_cast<Unsigned8 *>( img->data() );
        for( int row=0; row < img->size( 1 ); ++row, d += img->internal_width() )
            TIFFWriteScanline( tif, const_cast<Unsigned8 *>( d ), row, 0 );
    }

    TIFFClose( tif );
}

    
///
//template<class T>
//class ImgItemTif : public ImgItemT<T,2> {
//public:
//    ImgItemTif( const CString &filename, TIFF *tif ) : _filename( filename ) {
//        TIFFGetField( tif, TIFFTAG_IMAGEWIDTH     , &this->_w );
//        TIFFGetField( tif, TIFFTAG_IMAGELENGTH    , &this->_h );
//        this->_n = 1;
//        TIFFGetField( tif, TIFFTAG_SAMPLESPERPIXEL, &this->_n );
//        TIFFClose( tif );
//    }
//
//    virtual ~ImgItemTif() {
//    }
//
//    void exec_node() const {
//        this->allocate();
//
//        //
//        TIFF *tif = TIFFOpen( _filename.data(), "r" );
//
//        T *d = this->_data;
//        for( int row=0; row < this->_h; ++row, d += this->_in_w )
//            TIFFReadScanline( tif, d, row, 0 );
//
//        //
//        TIFFClose( tif );
//    }
//
//    CString filename() const { return _filename; }
//
//private:
//    CString _filename;
//};
//
//extern "C" const ImgItem *new_ImgItemTif( const CString &filename ) {
//    TIFF *tif = TIFFOpen( filename.data(), "r" );
//    if ( not tif )
//        throw "impossible to read " + filename + " using libtiff";
//
//    uint16 bits_per_sample;
//    TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE , &bits_per_sample );
//
//    if ( bits_per_sample == 16 ) return new ImgItemTif<Unsigned16>( filename, tif );
//    if ( bits_per_sample ==  8 ) return new ImgItemTif<Unsigned8 >( filename, tif );
//    ASSERT( 0, "TODO: " + String( bits_per_sample ) + "-bits TIF images" );
//}
//
//// --------------------------------------------------------------------------------------------------------------------------------------------------------
/////
//template<class T>
//class ImgItemTifWriter : public LazyObject {
//public:
//    ImgItemTifWriter( const CString &filename, const ImgItem *img ) : _filename( filename ), img( static_cast<const ImgItemT<T,2> *>( img ) ), _done( false ) {
//        add_child( img );
//    }
//
//    virtual ~ImgItemTifWriter() {
//    }
//
//    virtual bool done() const { return _done; }
//
//    void exec_node() const {
//        _done = true;
//        TIFF *tif = TIFFOpen( _filename.data(), "w" );
//        if ( not tif )
//            throw "impossible to write " + _filename + " using libtiff";
//
//        TIFFSetField( tif, TIFFTAG_IMAGEWIDTH     , img->width    ()    );
//        TIFFSetField( tif, TIFFTAG_IMAGELENGTH    , img->height   ()    );
//        TIFFSetField( tif, TIFFTAG_SAMPLESPERPIXEL, img->nb_planes()    );
//        TIFFSetField( tif, TIFFTAG_BITSPERSAMPLE  , sizeof( T ) * 8     );
//        TIFFSetField( tif, TIFFTAG_ORIENTATION    , ORIENTATION_TOPLEFT ); // set the origin of the image.
//        TIFFSetField( tif, TIFFTAG_PLANARCONFIG   , PLANARCONFIG_CONTIG );
//        TIFFSetField( tif, TIFFTAG_PHOTOMETRIC    , PHOTOMETRIC_MINISBLACK/*PHOTOMETRIC_RGB*/ );
//        TIFFSetField( tif, TIFFTAG_ROWSPERSTRIP   , TIFFDefaultStripSize( tif, img->width() * img->nb_planes() ) );
//
//        const T *d = img->data();
//        for( int row=0; row < img->height(); ++row, d += img->internal_width() )
//            TIFFWriteScanline( tif, const_cast<T *>( d ), row, 0 );
//
//        TIFFClose( tif );
//    }
//
//protected:
//    CString _filename;
//    const ImgItemT<T,2> *img;
//    mutable bool _done;
//};
//
//extern "C" const LazyObject *new_ImgItemTifWriter( const CString &filename, const ImgItem *img ) {
//    return new ImgItemTifWriter<Unsigned16>( filename, img );
//}

} // namespace Metil



