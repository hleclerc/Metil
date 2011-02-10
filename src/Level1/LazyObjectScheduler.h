#ifndef LAZYOBJECTSCHEDULER_H
#define LAZYOBJECTSCHEDULER_H

#include "../BasicVec.h"
#include "../MO.h"

BEG_METIL_LEVEL1_NAMESPACE

/**
*/
class LazyObjectScheduler {
public:
    void add( Level1::MO *o );
    void exec();

private:
    BasicVec<Level1::MO *> roots;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // LAZYOBJECTSCHEDULER_H
