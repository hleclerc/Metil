#ifndef LIMITS_H
#define LIMITS_H

#include "IsAnInteger.h"
#include <limits>

BEG_METIL_NAMESPACE;

template<class T,bool integer=IsAnInteger<T>::res>
struct Limits {
    static T min() { return std::numeric_limits<T>::min(); }
    static T max() { return std::numeric_limits<T>::max(); }
};

template<class T>
struct Limits<T,false> {
    static T min() { return -std::numeric_limits<T>::max(); }
    static T max() { return +std::numeric_limits<T>::max(); }
};

END_METIL_NAMESPACE;

#endif // LIMITS_H
