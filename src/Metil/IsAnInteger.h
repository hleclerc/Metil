#ifndef ISANINTEGER_H
#define ISANINTEGER_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

template<class T> struct IsAnInteger { static const bool res = false; };

template<> struct IsAnInteger<SI8      > { static const bool res = true; };
template<> struct IsAnInteger<SI16     > { static const bool res = true; };
template<> struct IsAnInteger<SI32     > { static const bool res = true; };
template<> struct IsAnInteger<SI64     > { static const bool res = true; };

template<> struct IsAnInteger<PI8 > { static const bool res = true; };
template<> struct IsAnInteger<PI16> { static const bool res = true; };
template<> struct IsAnInteger<PI32> { static const bool res = true; };
template<> struct IsAnInteger<PI64> { static const bool res = true; };

END_METIL_NAMESPACE

#endif // ISANINTEGER_H
