#include "Level1/ArrayHeader.h"
#include "DynamicCppLib.h"
#include "System.h"
#include "Img.h"

BEG_METIL_NAMESPACE;

Img::Img() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Img::Img( const String &filename, const MachineId &machine ) {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
    load( filename, machine );
}

void Img::load( const String &filename, const MachineId &machine ) {
    if ( filename.ends_with( ".tif" ) or filename.ends_with( ".tiff" ) or
         filename.ends_with( ".TIF" ) or filename.ends_with( ".TIFF" ) )
        load_tiff( filename, machine );
    else
        load_qimg( filename, machine );
}

void Img::load_tiff( const String &filename, const MachineId &machine ) {
    static DynamicCppLib dl( directory_of( __FILE__ ) + "/TiffLoader.cpp" );
    typedef Level1::MO LoadTiff( const String &filename, const MachineId &machine );
    CM_2( reassign, *this, reinterpret_cast<LoadTiff *>( dl.get_sym( "load_tiff" ) )( filename, machine ) );
}

void Img::load_qimg( const String &filename, const MachineId &machine ) {
}

END_METIL_NAMESPACE;
