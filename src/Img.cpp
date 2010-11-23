#include "Level1/LazyObjectData.h"
#include "Level1/ArrayHeader.h"
#include "Img.h"

BEG_METIL_NAMESPACE;

Img::Img() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Img::Img( ST w, ST h, Level1::Type *base_type ) {
    type = base_type;
    ST size[ 2 ] = { w, h };
    CM_2( allocate_array, *this, Level1::REF_Vec( Number<2>(), size ) );
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
    CM_1( del, *this );
    typedef Level1::Owcp<1,Level1::LazyObjectData> L;
    type = &Level1::metil_type_bas_TiffLoader;
    data = NEW( L, type, filename );
}

void Img::load_qimg( const String &filename ) {
    CM_1( del, *this );
    TODO;
    //    static DynamicCppLib dl( directory_of( __FILE__ ) + "/QimgLoader.cpp" );
    //    typedef void LoadQimg( Level1::MO &res, const String &filename );
    //    reinterpret_cast<LoadQimg *>( dl.get_sym( "load_qimg" ) )( *this, filename );
}

Val Img::w() const { return size( 0 ); }
Val Img::h() const { return size( 1 ); }

END_METIL_NAMESPACE;
