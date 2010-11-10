#include "Mutex.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name pthread
#endif

BEG_METIL_NAMESPACE;

Mutex::Mutex() {
    pthread_mutex_init( &mutex, 0 );
}

Mutex::~Mutex() {
    pthread_mutex_destroy( &mutex );
}

void Mutex::lock() {
    pthread_mutex_lock( &mutex );
}

void Mutex::free() {
    pthread_mutex_unlock( &mutex );
}

END_METIL_NAMESPACE;
