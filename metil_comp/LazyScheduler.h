#ifndef LAZYSCHEDULER_H
#define LAZYSCHEDULER_H

#include "LazyObject.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LazyScheduler.cpp
#endif

namespace Metil {

class LazyScheduler {
public:
    LazyScheduler();

    void execute();
    LazyScheduler &operator<<( const LazyObject *obj );

private:
    BasicVec<const LazyObject *> roots;
};

void schedule_and_execute( const LazyObject *obj );

} // namespace Metil

#endif // LAZYSCHEDULER_H
