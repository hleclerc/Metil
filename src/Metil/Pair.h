#ifndef PAIR_H
#define PAIR_H

#include "Config.h"

BEG_METIL_NAMESPACE

/**
*/
template<class T0,class T1>
struct Pair {
    Pair() {}
    Pair( T0 a, T1 b ) : a( a ), b( b ) {}

    T0 a;
    T1 b;
};

END_METIL_NAMESPACE

#endif // PAIR_H
