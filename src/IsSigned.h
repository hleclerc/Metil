#ifndef ISSIGNED_H
#define ISSIGNED_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE

template<class T> struct IsSigned { static const bool res = true; };

template<> struct IsSigned<PI8 > { static const bool res = false; };
template<> struct IsSigned<PI16> { static const bool res = false; };
template<> struct IsSigned<PI32> { static const bool res = false; };
template<> struct IsSigned<PI64> { static const bool res = false; };

END_METIL_NAMESPACE

#endif // ISSIGNED_H
