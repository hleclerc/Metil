#ifndef TYPEWITHOUTPTR_H
#define TYPEWITHOUTPTR_H

#include "Config.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<class R>
struct TypeWithoutPtr {
    typedef R T;
};

template<class R>
struct TypeWithoutPtr<R *> {
    typedef R T;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPEWITHOUTPTR_H
