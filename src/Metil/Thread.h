#ifndef THREAD_H
#define THREAD_H

#include "Config.h"
#include <pthread.h>

BEG_METIL_NAMESPACE;

/**
  @brief new thread...

  Example:
@code
struct Toto : public Thread {
    virtual void run() { sleep( 1 ); }
};
int main() {
    Toto toto;
    toto.exec();
    ... // do some stuff in parallel of toto.run()
    toto.wait(); // wait until toto has finished
}
@endcode
*/
class Thread {
public:
    virtual ~Thread();
    virtual void run() = 0;

    void exec(); ///< call run() in a new separate thread
    void wait(); ///< wait until run is finished (after an exec call)

private:
    pthread_t thread;
};

END_METIL_NAMESPACE;

#endif // THREAD_H
