#ifndef WAITCONDITION_H
#define WAITCONDITION_H

#include "Mutex.h"

BEG_METIL_NAMESPACE;

/**
  @brief thread condition. Used to wait for events in threads.

  User is responsible to lock and unlock the mutex before and after.

  Example :

@code
Mutex mutex;
WaitCondition wait_cond;

// consumer
mutex.lock();
wait_cond.wait();
mutex.free();

// producer
mutex.lock();
wait_cond.wake_all( mutex );
mutex.free();
@endcode
*/
class WaitCondition {
public:
    WaitCondition();
    ~WaitCondition();

    void wait( Mutex &mutex );
    void wake_all();
    void wake_one();

private:
    pthread_cond_t cond;
};

END_METIL_NAMESPACE;

#endif // WAITCONDITION_H
