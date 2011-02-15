#include "Level1/TypeConstructor.h"
#include "Level1/LazyObjectData.h"
#include "Level1/ArrayHeader.h"
#include "Level1/Ad.h"
#include "Img.h"
#include "Png.h"

BEG_METIL_NAMESPACE;

Img::Img() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Img::Img( ST w, ST h, Level1::Type *item_type ) {
    ST size[ 2 ] = { w, h };
    type = item_type;
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

void Img::load( const String &filename, Level1::Type *item_type, const Vec &XS ) {
    type = item_type;
    void *ptr = CM_2( allocate_array, *this, XS );
    File f( filename, "r" );
    f.read( ptr, item_type->constructor->static_size_in_bytes() * product( XS ) );
}


void Img::load_tiff( const String &filename ) {
    CM_1( del, *this );
    typedef Level1::Owcp<1,Level1::LazyObjectData> L;
    type = &Level1::metil_type_bas_TiffLoader;
    data = NEW( L, type, filename );
}

void Img::load_qimg( const String &filename ) {
    TODO;
}

Val Img::w() const { return size( 0 ); }
Val Img::h() const { return size( 1 ); }
Val Img::d() const { return size( 1 ); }

void Img::convert_to_gpu_tex() {
    Level1::Ad o( *this );
    Level1::MO f( 0, &Level1::metil_type_cst_ConvertToGpuTex );
    Level1::MO r = CM_2( select_C, f, *this );
    type = r.type;
    data = r.data;
}

END_METIL_NAMESPACE;
