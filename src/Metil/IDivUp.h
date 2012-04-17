#ifndef IDIVUP_H
#define IDIVUP_H

#include "Config.h"

BEG_METIL_NAMESPACE

template<long a,long b>
struct IDivUp {
    enum { res = ( a + b - 1 ) / b };
};

END_METIL_NAMESPACE

#endif // IDIVUP_H
