#ifndef REFOF_H
#define REFOF_H

#include "Config.h"

BEG_METIL_NAMESPACE;

template<class O>
struct RefOf;

template<class O>
struct RefOf<O *> {
    typedef O T;
};

template<class O>
struct RefOf<const O *> {
    typedef O T;
};

END_METIL_NAMESPACE;

#endif // REFOF_H
