#include "Thread.h"

BEG_METIL_NAMESPACE;

Thread::~Thread() {
}

static void *_run( void *data ) {
    reinterpret_cast<Thread *>( data )->run();
    return 0;
}

void Thread::exec() {
    pthread_create( &thread, 0, _run, this );
}

void Thread::wait() {
    void *ret;
    pthread_join( thread, &ret );
}

END_METIL_NAMESPACE;
