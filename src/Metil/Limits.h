#ifndef LIMITS_H
#define LIMITS_H

#include "IsAnInteger.h"
#include <limits>

BEG_METIL_NAMESPACE;

//template<class T,bool integer=IsAnInteger<T>::res>
//struct Limits {
//    static __inline__ T min() { return std::numeric_limits<T>::min(); }
//    static __inline__ T max() { return std::numeric_limits<T>::max(); }
//};

//template<class T>
//struct Limits<T,false> {
//    static __inline__ T min() { return -std::numeric_limits<T>::max(); }
//    static __inline__ T max() { return +std::numeric_limits<T>::max(); }
//};

template<class T>
struct Limits {
};

template<>
struct Limits<FP32> {
    static __inline__ FP32 min() { return -__FLT_MAX__; }
    static __inline__ FP32 max() { return +__FLT_MAX__; }
};

template<>
struct Limits<FP64> {
    static __inline__ FP64 min() { return -__DBL_MAX__; }
    static __inline__ FP64 max() { return +__DBL_MAX__; }
};

END_METIL_NAMESPACE;

#endif // LIMITS_H
