#ifndef WAITCONDITIONBUNDLE_H
#define WAITCONDITIONBUNDLE_H

#include "WaitCondition.h"

BEG_METIL_NAMESPACE;

/**
 Contrary to the usual WaitCondition, WaitConditionBundle works even if a wake has been triggered before the wait

 wait can optionnaly ask for a defined number of wake before returning.
*/
class WaitConditionBundle {
public:
    WaitConditionBundle() {
        cpt = 0;
    }

    void wait( int obj = 1 ) {
        mutex.lock();
        while ( cpt < obj )
            wait_cond.wait( mutex );
        cpt = 0;
        mutex.free();
    }

    void wake() {
        mutex.lock();
        ++cpt;
        wait_cond.wake_all();
        mutex.free();
    }

private:
    WaitCondition wait_cond;
    Mutex mutex;
    int cpt;
};

END_METIL_NAMESPACE;

#endif // WAITCONDITIONBUNDLE_H
