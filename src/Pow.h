#ifndef POW_H
#define POW_H

#include "Config.h"

BEG_METIL_NAMESPACE;

template<int m,int e>
struct Pow {
    enum { res = m * Pow<m,e-1>::res };
};

template<int m>
struct Pow<m,0> {
    enum { res = 1 };
};

END_METIL_NAMESPACE;

#endif // POW_H
