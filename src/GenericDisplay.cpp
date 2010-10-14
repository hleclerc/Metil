#include "GenericDisplay.h"
#include "CudaMetil.h"

#include <limits>

BEG_METIL_NAMESPACE;

GenericDisplay::GenericDisplay( int w, int h ) : w( w ), h( h ) {
    trans_gpu = 0;
}

GenericDisplay::~GenericDisplay() {
    for( ST i = items.size() - 1; i >= 0; --i )
        DEL( items[ i ] );
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

int GenericDisplay::get_w() const { return w; }
int GenericDisplay::get_h() const { return h; }
void GenericDisplay::set_w( int w ) { this->w = w; }
void GenericDisplay::set_h( int h ) { this->h = h; }

void GenericDisplay::update_p_min_p_max() {
    p_min = +std::numeric_limits<T>::max();
    p_max = -std::numeric_limits<T>::max();
    for( int n = 0; n < items.size(); ++n )
        items[ n ]->update_p_min_p_max( this, p_min, p_max );
    p_min[2]=0;
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
