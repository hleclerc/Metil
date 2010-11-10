#ifndef MUTEX_H
#define MUTEX_H

#include "Config.h"
#include <pthread.h>

BEG_METIL_NAMESPACE;

class Mutex {
public:
    Mutex();
    ~Mutex();

    void lock();
    void free();

private:
    friend class WaitCondition;
    pthread_mutex_t mutex;
};

END_METIL_NAMESPACE;

#endif // MUTEX_H
