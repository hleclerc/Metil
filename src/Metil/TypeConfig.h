#ifndef TYPE_CONFIG_H
#define TYPE_CONFIG_H

#include "Config.h"
#include <stdint.h>

BEG_METIL_NAMESPACE

template<class P>
struct NI {
    NI( P data ) : data( data ) {}
    P data;
};

typedef float       FP32;
typedef double      FP64;
typedef long double FP80;

typedef bool        Bool;

typedef int8_t      SI8 ;
typedef int16_t     SI16;
typedef int32_t     SI32;
typedef int64_t     SI64;

typedef uint8_t     PI8 ;
typedef uint16_t    PI16;
typedef uint32_t    PI32;
typedef uint64_t    PI64;

typedef NI<PI8 >    NI8 ; ///< negative or null unsigned number
typedef NI<PI16>    NI16; ///< negative or null unsigned number
typedef NI<PI32>    NI32; ///< negative or null unsigned number
typedef NI<PI64>    NI64; ///< negative or null unsigned number

struct Ref {}; ///< @brief Used to declare a ref MetilObject... @see Val, Vec, ...
struct Size {}; ///< @brief Used for constructor of "sizeable" objects to specify the number of elements of the objects at the beginning @see Vec, Mat, ...
struct StaticSize {}; ///< @brief Used for constructor of "sizeable" objects to specify the number of elements of the objects (fixes) @see Vec, Mat, ...
struct Rese {}; ///<  @brief Used for constructor of "sizeable" objects to specify the number of reserved elements in the objects at the beginning @see Vec, Mat, ...
struct StaticRese {}; ///<  @brief Used for constructor of "sizeable" objects to specify the number of reserved elements in the objects (fixed) @see Vec, Mat, ...
#define APPLY_WN( res, n ) res.apply( #n, n )

// ---------------------- size types ----------------------

namespace Level1 {
    template<int N> struct SigSChoice {};
    template<> struct SigSChoice<4> { typedef SI32 T; };
    template<> struct SigSChoice<8> { typedef SI64 T; };

    template<int N> struct PosSChoice {};
    template<> struct PosSChoice<4> { typedef PI32 T; };
    template<> struct PosSChoice<8> { typedef PI64 T; };
}

typedef Level1::SigSChoice<sizeof(void *)>::T ST; ///< signed size type
typedef Level1::PosSChoice<sizeof(void *)>::T PT; ///< unsigned size type


END_METIL_NAMESPACE


#endif // TYPE_CONFIG_H
