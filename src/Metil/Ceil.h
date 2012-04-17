#ifndef CEIL_H
#define CEIL_H

#include "Config.h"

BEG_METIL_NAMESPACE

template<int a,int b>
struct Ceil {
    enum { res = ( a + b - 1 ) / b * b };
};

END_METIL_NAMESPACE

#endif // CEIL_H
