#ifndef ISASCALAR_H
#define ISASCALAR_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

///
template<class T> struct IsAScalar { static const bool res = false; };

template<> struct IsAScalar<FP32> { static const bool res = true; };
template<> struct IsAScalar<FP64> { static const bool res = true; };
template<> struct IsAScalar<FP80> { static const bool res = true; };
template<> struct IsAScalar<Bool> { static const bool res = true; };
template<> struct IsAScalar<SI8 > { static const bool res = true; };
template<> struct IsAScalar<SI16> { static const bool res = true; };
template<> struct IsAScalar<SI32> { static const bool res = true; };
template<> struct IsAScalar<SI64> { static const bool res = true; };
template<> struct IsAScalar<PI8 > { static const bool res = true; };
template<> struct IsAScalar<PI16> { static const bool res = true; };
template<> struct IsAScalar<PI32> { static const bool res = true; };
template<> struct IsAScalar<PI64> { static const bool res = true; };

END_METIL_NAMESPACE

#endif // ISASCALAR_H
