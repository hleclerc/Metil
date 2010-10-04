#include "String.h"

BEG_METIL_LEVEL1_NAMESPACE;

void MO::write_str( String &os ) const {
    // type->write_str( *this, os );
    CM_2( self_append, os, *this );
}

void MO::write_dot( String &/*os*/, bool /*want_parents*/ ) const {
    TODO;
}

void MO::write_tex( String &/*os*/ ) const {
    TODO;
}

void MO::display_dot( const String &/*base_filename*/, bool /*want_parents */) const {
    TODO;
}

void MO::display_tex( const String &/*base_filename*/ ) const {
    TODO;
}

void MO::display_dot( bool /*want_parents*/ ) const {
    TODO;
}

void MO::display_tex() const {
    TODO;
}

END_METIL_LEVEL1_NAMESPACE
