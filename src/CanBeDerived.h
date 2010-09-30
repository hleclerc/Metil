#ifndef CanBeDerived_H
#define CanBeDerived_H

#include "TypeConfig.h"

BEG_METIL_LEVEL1_NAMESPACE;

/// @brief static const attribute res must be equal to true if T do not contain virtual methods. @see DEL
template<class T>
struct CanBeDerived {
    static const bool res = T::can_be_derived;
};

template<> struct CanBeDerived<Bool > { static const bool res = false; };

template<> struct CanBeDerived<SI8 > { static const bool res = false; };
template<> struct CanBeDerived<SI16> { static const bool res = false; };
template<> struct CanBeDerived<SI32> { static const bool res = false; };
template<> struct CanBeDerived<SI64> { static const bool res = false; };

template<> struct CanBeDerived<PI8 > { static const bool res = false; };
template<> struct CanBeDerived<PI16> { static const bool res = false; };
template<> struct CanBeDerived<PI32> { static const bool res = false; };
template<> struct CanBeDerived<PI64> { static const bool res = false; };

template<> struct CanBeDerived<NI8 > { static const bool res = false; };
template<> struct CanBeDerived<NI16> { static const bool res = false; };
template<> struct CanBeDerived<NI32> { static const bool res = false; };
template<> struct CanBeDerived<NI64> { static const bool res = false; };

template<> struct CanBeDerived<FP32> { static const bool res = false; };
template<> struct CanBeDerived<FP64> { static const bool res = false; };
template<> struct CanBeDerived<FP80> { static const bool res = false; };

template<class T> struct CanBeDerived<T *> { static const bool res = false; };

END_METIL_LEVEL1_NAMESPACE

#endif // CanBeDerived_H
