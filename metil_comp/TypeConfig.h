#ifndef TYPE_CONFIG_H
#define TYPE_CONFIG_H

#include <limits>
#include <sys/types.h>

namespace Metil {

typedef float       Float32;
typedef double      Float64;
typedef long double Float96;

typedef bool        Bool;

typedef __int8_t    Int8;
typedef __int16_t   Int16;
typedef __int32_t   Int32;
typedef __int64_t   Int64;

typedef __uint8_t   Unsigned8;
typedef __uint16_t  Unsigned16;
typedef __uint32_t  Unsigned32;
typedef __uint64_t  Unsigned64;

namespace Private {
    template<int N> struct SizeTypeChoice {};
    template<> struct SizeTypeChoice<4> { typedef Int32 T; };
    template<> struct SizeTypeChoice<8> { typedef Int64 T; };
    
    template<int N> struct UnsignedSizeTypeChoice {};
    template<> struct UnsignedSizeTypeChoice<4> { typedef Unsigned32 T; };
    template<> struct UnsignedSizeTypeChoice<8> { typedef Unsigned64 T; };
}


typedef Private::SizeTypeChoice        <sizeof(void *)>::T SizeType;
typedef Private::UnsignedSizeTypeChoice<sizeof(void *)>::T UnsignedSizeType;

// #define FLOAT64_MIN_VAL (-std::numeric_limits<Float64>::max())
// #define FLOAT64_MAX_VAL (std::numeric_limits<Float64>::max())
// #define INT32_MIN_VAL (-std::numeric_limits<Int32>::max())
// #define INT32_MAX_VAL (std::numeric_limits<Int32>::max())

} // namespace Metil

#endif // TYPE_CONFIG_H
