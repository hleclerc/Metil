#include "WaitCondition.h"

BEG_METIL_NAMESPACE;

WaitCondition::WaitCondition() {
    pthread_cond_init( &cond, 0 );
}

WaitCondition::~WaitCondition(){
    pthread_cond_destroy( &cond );
}

void WaitCondition::wait( Mutex &mutex ) {
    pthread_cond_wait( &cond, &mutex.mutex );
}

void WaitCondition::wake_one() {
     pthread_cond_signal( &cond );
}

void WaitCondition::wake_all() {
    pthread_cond_broadcast( &cond );
}

END_METIL_NAMESPACE;
