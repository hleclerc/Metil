#include "DynamicCppLib.h"
#include "System.h"
#include "Img.h"

BEG_METIL_NAMESPACE;

Img::Img() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Img::Img( const String &filename ) {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
    load( filename );
}

void Img::load( const String &filename ) {
    if ( filename.ends_with( ".tif" ) or filename.ends_with( ".tiff" ) or
         filename.ends_with( ".TIF" ) or filename.ends_with( ".TIFF" ) )
        load_tiff( filename );
    else
        load_qimg( filename );
}

void Img::load_tiff( const String &filename ) {
    static DynamicCppLib dl( directory_of( __FILE__ ) + "/TiffLoader.cpp" );
    typedef Level1::MO LoadTiff( const String &filename );
    CM_2( reassign, *this, reinterpret_cast<LoadTiff *>( dl.get_sym( "load_tiff" ) )( filename ) );
}

void Img::load_qimg( const String &filename ) {
}

END_METIL_NAMESPACE;
