#include "Level1/ArrayHeader.h"
#include "DynamicCppLib.h"
#include "System.h"
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

Img::Img( const String &filename, const MachineId *machine ) {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
    load( filename, machine );
}

void Img::load( const String &filename, const MachineId *machine ) {
    if ( filename.ends_with( ".tif" ) or filename.ends_with( ".tiff" ) or
         filename.ends_with( ".TIF" ) or filename.ends_with( ".TIFF" ) )
        load_tiff( filename, machine );
    else
        load_qimg( filename, machine );
}

void Img::load_tiff( const String &filename, const MachineId *machine ) {
    CM_1( del, *this );
    static DynamicCppLib dl( directory_of( __FILE__ ) + "/TiffLoader.cpp" );
    typedef void LoadTiff( Level1::MO &res, const String &filename, const MachineId *machine );
    reinterpret_cast<LoadTiff *>( dl.get_sym( "load_tiff" ) )( *this, filename, machine );
}

void Img::load_qimg( const String &filename, const MachineId *machine ) {
    CM_1( del, *this );
    static DynamicCppLib dl( directory_of( __FILE__ ) + "/QimgLoader.cpp" );
    typedef void LoadQimg( Level1::MO &res, const String &filename, const MachineId *machine );
    reinterpret_cast<LoadQimg *>( dl.get_sym( "load_qimg" ) )( *this, filename, machine );
}

Val Img::w() const { return size( 0 ); }
Val Img::h() const { return size( 1 ); }

END_METIL_NAMESPACE;
