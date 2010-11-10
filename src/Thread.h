#ifndef THREAD_H
#define THREAD_H

#include "Config.h"
#include <pthread.h>

BEG_METIL_NAMESPACE;

class Thread {
public:
    virtual ~Thread();
    virtual void run() = 0;

    void exec();
    void wait();

private:
    pthread_t thread;
};

END_METIL_NAMESPACE;

#endif // THREAD_H
