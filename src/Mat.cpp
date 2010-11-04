#include "Level1/TypeConstructor.h"
#include "Level1/ArrayHeader.h"
#include "Mat.h"

BEG_METIL_NAMESPACE;

Mat::Mat() {
    type = &Level1::metil_type_ref_Array_4NULL_2_0_0_0_0;
}

Mat::Mat( ST r, ST c, Level1::Type *base_type ) {
    ST size[ 2 ] = { c, r };
    Level1::MO *d = Level1::init_dyn_array( *this, size, Number<2>(), base_type );
    if ( not base_type ) {
        for( int i = 0; i < r * c; ++i )
            new( d + i ) Val;
    }
}

END_METIL_NAMESPACE;
