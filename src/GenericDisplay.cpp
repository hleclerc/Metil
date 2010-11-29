#include "GenericDisplay.h"
#include "MathBasicVec.h"
#include "CudaMetil.h"
#include "String.h"

#include <limits>

BEG_METIL_NAMESPACE;

GenericDisplay::GenericDisplay( int w, int h ) : w( w ), h( h ) {
    trans_gpu = 0;
    C_has_been_defined = 0;
}

GenericDisplay::~GenericDisplay() {
    //for( ST i = items.size() - 1; i >= 0; --i )
    //    DEL( items[ i ] );
}

GenericDisplay &GenericDisplay::operator<<( DisplayItem *item ) {
    items << item;
    return *this;
}

void GenericDisplay::set_O( T Ox, T Oy, T Oz ) { trans_cpu.O[ 0 ] = Ox; trans_cpu.O[ 1 ] = Oy; trans_cpu.O[ 2 ] = Oz; trans_has_changed = true; }
void GenericDisplay::set_X( T Xx, T Xy, T Xz ) { trans_cpu.X[ 0 ] = Xx; trans_cpu.X[ 1 ] = Xy; trans_cpu.X[ 2 ] = Xz; trans_has_changed = true; }
void GenericDisplay::set_Y( T Yx, T Yy, T Yz ) { trans_cpu.Y[ 0 ] = Yx; trans_cpu.Y[ 1 ] = Yy; trans_cpu.Y[ 2 ] = Yz; trans_has_changed = true; }
void GenericDisplay::set_d( T d ) { trans_cpu.d = d; trans_has_changed = true; }
void GenericDisplay::set_a( T a ) { trans_cpu.a = a; trans_has_changed = true; }
void GenericDisplay::set_O( T3 O ) { set_O( O[ 0 ], O[ 1 ], O[ 2 ] ); }
void GenericDisplay::set_X( T3 X ) { set_X( X[ 0 ], X[ 1 ], X[ 2 ] ); }
void GenericDisplay::set_Y( T3 Y ) { set_Y( Y[ 0 ], Y[ 1 ], Y[ 2 ] ); }

void GenericDisplay::rotate( T x, T y, T z ) {
    rotate( T3( x, y, z ) );
}

void GenericDisplay::zoom( T c, T x, T y ) {
    T mwh = min( w, h );
    x = ( x - w / 2 ) * trans_cpu.d / mwh;
    y = ( y - h / 2 ) * trans_cpu.d / mwh;
    T3 P = trans_cpu.O + x * trans_cpu.X + y * trans_cpu.Y;
    trans_cpu.O = P + ( trans_cpu.O - P ) / c;
    trans_cpu.d /= c;
    trans_has_changed = true;
}

void GenericDisplay::rotate( T3 V ) {
    if ( not C_has_been_defined ) {
        C_has_been_defined = true;
        C = trans_cpu.O;
    }
    trans_cpu.rotate_s( V, C );
    trans_has_changed = true;
}

GenericDisplay::T3 GenericDisplay::get_O() const { return trans_cpu.O; }
GenericDisplay::T3 GenericDisplay::get_X() const { return trans_cpu.X; }
GenericDisplay::T3 GenericDisplay::get_Y() const { return trans_cpu.Y; }
GenericDisplay::T GenericDisplay::get_d() const { return trans_cpu.d; }
GenericDisplay::T GenericDisplay::get_a() const { return trans_cpu.a; }

void GenericDisplay::get_trans_data( String &res, const String &name ) {
    res << name << " = {\n";
    res << "  O : [ " << trans_cpu.O[ 0 ] << ", " << trans_cpu.O[ 1 ] << ", " << trans_cpu.O[ 2 ] << " ],\n";
    res << "  X : [ " << trans_cpu.X[ 0 ] << ", " << trans_cpu.X[ 1 ] << ", " << trans_cpu.X[ 2 ] << " ],\n";
    res << "  Y : [ " << trans_cpu.Y[ 0 ] << ", " << trans_cpu.Y[ 1 ] << ", " << trans_cpu.Y[ 2 ] << " ],\n";
    res << "  a : " << trans_cpu.a << ",\n";
    res << "  d : " << trans_cpu.d << "\n";
    res << "};\n";
}

int GenericDisplay::get_w() const { return w; }
int GenericDisplay::get_h() const { return h; }
void GenericDisplay::set_w( int w ) { this->w = w; }
void GenericDisplay::set_h( int h ) { this->h = h; }

void GenericDisplay::update_p_min_p_max( bool use_trans ) {
    p_min = +std::numeric_limits<T>::max();
    p_max = -std::numeric_limits<T>::max();
    for( int n = 0; n < items.size(); ++n )
        items[ n ]->update_p_min_p_max( this, p_min, p_max, use_trans );
}

void GenericDisplay::fit() {
    update_p_min_p_max( false );
    T3 C = T( 0.5 ) * ( p_min + p_max );
    set_O( C );
    set_d( 1.5 * max( p_max[ 0 ] - p_min[ 0 ], p_max[ 1 ] - p_min[ 1 ] ) );
}

DisplayTrans *GenericDisplay::get_trans_gpu() {
    if ( not trans_gpu ) {
        CSC( cudaMalloc( &trans_gpu, sizeof( DisplayTrans ) ) );
        trans_has_changed = true;
    }
    if ( trans_has_changed ) {
        trans_has_changed = false;
        CSC( cudaMemcpy( trans_gpu, &trans_cpu, sizeof( DisplayTrans ), cudaMemcpyHostToDevice ) );
    }
    return trans_gpu;
}

END_METIL_NAMESPACE;
