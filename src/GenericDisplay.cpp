#include "GenericDisplay.h"
#include "MathBasicVec.h"
#include "CudaMetil.h"
#include "MetilString.h"

#include <limits>

BEG_METIL_NAMESPACE;

GenericDisplay::GenericDisplay( int w, int h ) : w( w ), h( h ) {
    C_has_been_defined = 0;
}

GenericDisplay::~GenericDisplay() {
}

GenericDisplay &GenericDisplay::operator<<( DisplayItem *item ) {
    items << item;
    return *this;
}

void GenericDisplay::set_O( T Ox, T Oy, T Oz ) { trans.O[ 0 ] = Ox; trans.O[ 1 ] = Oy; trans.O[ 2 ] = Oz; trans_has_changed = true; }
void GenericDisplay::set_X( T Xx, T Xy, T Xz ) { trans.X[ 0 ] = Xx; trans.X[ 1 ] = Xy; trans.X[ 2 ] = Xz; trans_has_changed = true; }
void GenericDisplay::set_Y( T Yx, T Yy, T Yz ) { trans.Y[ 0 ] = Yx; trans.Y[ 1 ] = Yy; trans.Y[ 2 ] = Yz; trans_has_changed = true; }
void GenericDisplay::set_d( T d ) { trans.d = d; trans_has_changed = true; }
void GenericDisplay::set_a( T a ) { trans.a = a; trans_has_changed = true; }
void GenericDisplay::set_O( T3 O ) { set_O( O[ 0 ], O[ 1 ], O[ 2 ] ); }
void GenericDisplay::set_X( T3 X ) { set_X( X[ 0 ], X[ 1 ], X[ 2 ] ); }
void GenericDisplay::set_Y( T3 Y ) { set_Y( Y[ 0 ], Y[ 1 ], Y[ 2 ] ); }
void GenericDisplay::set_w( int w ) { this->w = w; }
void GenericDisplay::set_h( int h ) { this->h = h; }

GenericDisplay::T3 GenericDisplay::get_O() const { return trans.O; }
GenericDisplay::T3 GenericDisplay::get_X() const { return trans.X; }
GenericDisplay::T3 GenericDisplay::get_Y() const { return trans.Y; }
GenericDisplay::T  GenericDisplay::get_d() const { return trans.d; }
GenericDisplay::T  GenericDisplay::get_a() const { return trans.a; }
GenericDisplay::I  GenericDisplay::get_w() const { return w; }
GenericDisplay::I  GenericDisplay::get_h() const { return h; }

void GenericDisplay::zoom( T c, T x, T y ) {
    T mwh = min( w, h );
    x = ( x - w / 2 ) * trans.d / mwh;
    y = ( y - h / 2 ) * trans.d / mwh;
    T3 P = trans.O + x * trans.X + y * trans.Y;
    T3 Z = Metil::normalized( cross( trans.Y, trans.X ) );
    trans.O = P + ( trans.O - P ) / c;
    trans.d /= c;
    trans_has_changed = true;
}

void GenericDisplay::pan( T x, T y ) {
    trans.O -= x * trans.X + y * trans.Y;
    trans_has_changed = true;
}

void GenericDisplay::rotate( T3 V ) {
    if ( not C_has_been_defined ) {
        C_has_been_defined = true;
        C = trans.O;
    }
    trans.rotate_s( V, C );
    trans_has_changed = true;
}

void GenericDisplay::rotate( T x, T y, T z ) {
    rotate( T3( x, y, z ) );
}

void GenericDisplay::get_trans_data( String &res, const String &name ) {
    res << name << " = {\n";
    res << "  O : [ " << trans.O[ 0 ] << ", " << trans.O[ 1 ] << ", " << trans.O[ 2 ] << " ],\n";
    res << "  X : [ " << trans.X[ 0 ] << ", " << trans.X[ 1 ] << ", " << trans.X[ 2 ] << " ],\n";
    res << "  Y : [ " << trans.Y[ 0 ] << ", " << trans.Y[ 1 ] << ", " << trans.Y[ 2 ] << " ],\n";
    res << "  a : " << trans.a << ",\n";
    res << "  d : " << trans.d << "\n";
    res << "};\n";
}

void GenericDisplay::shrink( T v ) {
    for( int n = 0; n < items.size(); ++n )
        items[ n ]->shrink( v );
}

void GenericDisplay::get_min_max_real( T3 &mi, T3 &ma ) {
    mi = +std::numeric_limits<T>::max();
    ma = -std::numeric_limits<T>::max();
    for( int n = 0; n < items.size(); ++n )
        items[ n ]->update_min_max( mi, ma );
}

void GenericDisplay::get_min_max_view( T3 &mi, T3 &ma ) {
    mi = +std::numeric_limits<T>::max();
    ma = -std::numeric_limits<T>::max();
    DisplayTrans::Buf trans_buf = trans.make_buf( w, h );
    for( int n = 0; n < items.size(); ++n )
        items[ n ]->update_min_max( mi, ma, trans_buf );
}

void GenericDisplay::fit() {
    T3 mi, ma; get_min_max_real( mi, ma );
    set_O( T( 0.5 ) * ( mi + ma ) );
    set_d( 1.5 * max( ma[ 0 ] - mi[ 0 ], ma[ 1 ] - mi[ 1 ] ) );
}

END_METIL_NAMESPACE;
