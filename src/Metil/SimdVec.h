#ifndef SIMDVEC_H
#define SIMDVEC_H

#include "TypePromote.h"
#include "RefOf.h"

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __INTEL_COMPILER
        typedef __m128 __v4sf;
    #endif
#endif
#ifdef __SSE2__
    #include <emmintrin.h>
    #ifdef __INTEL_COMPILER
        typedef __m128d __v2df;
    #endif
#endif

BEG_METIL_NAMESPACE;

template<class T,unsigned s>
struct SimdVec {
    SimdVec() {}
    SimdVec(const T &v) { for(unsigned i=0;i<s;++i) val[i] = v; }
    SimdVec(const T &v0,const T &v1) { val[0] = v0; val[1] = v1; }
    SimdVec(const T &v0,const T &v1,const T &v2,const T &v3) { val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3; }
    template<class T2> SimdVec(const SimdVec<T2,s> &v) { for(unsigned i=0;i<s;++i) val[i] = (T)v[i]; }
    static const unsigned nb_elem = s;
    static SimdVec zero() { return SimdVec( T(0) ); }
    const T &operator[](unsigned i) const { return val[i]; }
    T &operator[](unsigned i) { return val[i]; }
    T sum() const { T res = val[0]; for(unsigned i=1;i<s;++i) res += val[i]; return res; }
    static SimdVec range() { SimdVec res; for( unsigned i = 0; i < s; ++i ) res[ i ] = i; return res; }

    SimdVec<typename RefOf<T>::T,s> operator*() {
         SimdVec<typename RefOf<T>::T,s> res;
         for( unsigned i = 0; i < s; ++i )
             res[ i ] = *val[ i ];
         return res; 
    }
    
    
    T val[ s ];
};

template<class T> struct SimdSize;

class Plus;
class Minus;
class Multiplies;
class Divides;
class Modulus;
class And;
class Or;
class Xor;
class Min;
class Max;

template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Plus      ,P1,P2>::T,s> operator+(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Minus     ,P1,P2>::T,s> operator-(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Multiplies,P1,P2>::T,s> operator*(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Divides   ,P1,P2>::T,s> operator/(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Modulus   ,P1,P2>::T,s> operator%(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<And       ,P1,P2>::T,s> operator&(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Or        ,P1,P2>::T,s> operator|(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Xor       ,P1,P2>::T,s> operator^(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Min       ,P1,P2>::T,s> min(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Max       ,P1,P2>::T,s> max(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator+=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator-=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator*=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator/=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator%=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator&=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator|=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b)  __attribute__((always_inline));
template<class P1,class P2,unsigned s> void operator^=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) __attribute__((always_inline));

template<class T,unsigned s> SimdVec<T,s> operator-(const SimdVec<T,s> &a) __attribute__((always_inline));
template<class T,unsigned s> SimdVec<T,s> neg      (const SimdVec<T,s> &a) __attribute__((always_inline));
template<class T,unsigned s> SimdVec<T,s> conj     (const SimdVec<T,s> &a) __attribute__((always_inline));

template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Plus      ,P1,P2>::T,s> operator+(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Plus,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] + b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Minus     ,P1,P2>::T,s> operator-(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Minus,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] - b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Multiplies,P1,P2>::T,s> operator*(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Multiplies,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] * b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Divides   ,P1,P2>::T,s> operator/(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Divides,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] / b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Modulus   ,P1,P2>::T,s> operator%(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Divides,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] % b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<And       ,P1,P2>::T,s> operator&(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<And,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] & b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Or        ,P1,P2>::T,s> operator|(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Or,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] | b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Xor       ,P1,P2>::T,s> operator^(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Xor,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = a[i] ^ b[i]; return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Min       ,P1,P2>::T,s> min(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Min,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = min(a[i],b[i]); return res; }
template<class P1,class P2,unsigned s> SimdVec<typename TypePromote<Max       ,P1,P2>::T,s> max(const SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { SimdVec<typename TypePromote<Max,P1,P2>::T,s> res; for(unsigned i=0;i<s;++i) res[i] = max(a[i],b[i]); return res; }
template<class P1,class P2,unsigned s> void operator+=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] + b[i]; }
template<class P1,class P2,unsigned s> void operator-=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] - b[i]; }
template<class P1,class P2,unsigned s> void operator*=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] * b[i]; }
template<class P1,class P2,unsigned s> void operator/=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] / b[i]; }
template<class P1,class P2,unsigned s> void operator%=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] % b[i]; }
template<class P1,class P2,unsigned s> void operator&=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] & b[i]; }
template<class P1,class P2,unsigned s> void operator|=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] | b[i]; }
template<class P1,class P2,unsigned s> void operator^=(SimdVec<P1,s> &a,const SimdVec<P2,s> &b) { for(unsigned i=0;i<s;++i) a[i] = a[i] ^ b[i]; }

template<class T,unsigned s> SimdVec<T,s> operator-(const SimdVec<T,s> &a) { SimdVec<T,s> res; for(unsigned i=0;i<s;++i) res[i] =    - a[i] ; return res; }
template<class T,unsigned s> SimdVec<T,s> neg      (const SimdVec<T,s> &a) { SimdVec<T,s> res; for(unsigned i=0;i<s;++i) res[i] =    - a[i] ; return res; }
template<class T,unsigned s> SimdVec<T,s> conj     (const SimdVec<T,s> &a) { SimdVec<T,s> res; for(unsigned i=0;i<s;++i) res[i] = conj(a[i]); return res; }

template<class T,unsigned s> SimdVec<T,s> floor    (const SimdVec<T,s> &a) { SimdVec<T,s> res; for(unsigned i=0;i<s;++i) res[i] = floor(a[i]); return res; }
template<class T,unsigned s> SimdVec<T,s> heaviside(const SimdVec<T,s> &a) { SimdVec<T,s> res; for(unsigned i=0;i<s;++i) res[i] = (a[i]>=0)  ; return res; }


#ifdef __SSE__
// float
template<> struct SimdSize<float> { static const unsigned res = 4; };

template<> struct SimdVec<float,4> {
    SimdVec() {}
    SimdVec(const float &v) { val = _mm_set1_ps(v); }
    SimdVec(const __v4sf &v) { val = v; }
    SimdVec(const SimdVec &v) { val = v.val; }
    template<class T2> SimdVec(const SimdVec<T2,4> &v) { val = _mm_set_ps(v[0],v[1],v[2],v[3]); }
    SimdVec(const float &v0,const float &v1,const float &v2,const float &v3) { val = _mm_set_ps(v3,v2,v1,v0); }
    static __v4sf zero() { return _mm_setzero_ps(); }
    static const unsigned nb_elem = 4;
    const float &operator[](unsigned i) const { return ((const float *)&val)[i]; }
    float &operator[](unsigned i) { return ((float *)&val)[i]; }
    float sum() const { float res = ((const float *)&val)[0]; for(unsigned i=1;i<4;++i) res += ((const float *)&val)[i]; return res; }
    static SimdVec range() { return SimdVec( 0, 1, 2, 3 ); }
    
    template<class TS>
    void write_str( TS &os ) const {
        os << operator[]( 0 );
        for(ST i=1;i<nb_elem;++i) {
            os.write_separator( 0 );
            os << operator[]( i );
        }
    }
    
    __v4sf val;
};
inline SimdVec<float,4> operator+(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator-(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator*(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator/(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator&(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator|(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> operator^(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> min(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline SimdVec<float,4> max(const SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator+=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator-=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator*=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator/=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator&=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator|=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));
inline void operator^=(SimdVec<float,4> &a,const SimdVec<float,4> &b) __attribute__((always_inline));

inline SimdVec<float,4> operator+(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_add_ps(a.val,b.val); }
inline SimdVec<float,4> operator-(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_sub_ps(a.val,b.val); }
inline SimdVec<float,4> operator*(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_mul_ps(a.val,b.val); }
inline SimdVec<float,4> operator/(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_div_ps(a.val,b.val); }
inline SimdVec<float,4> operator&(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_and_ps(a.val,b.val); }
inline SimdVec<float,4> operator|(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_or_ps(a.val,b.val); }
inline SimdVec<float,4> operator^(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_xor_ps(a.val,b.val); }
inline SimdVec<float,4> min(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_min_ps(a.val,b.val); }
inline SimdVec<float,4> max(const SimdVec<float,4> &a,const SimdVec<float,4> &b) { return _mm_max_ps(a.val,b.val); }
inline void operator+=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_add_ps(a.val,b.val); }
inline void operator-=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_sub_ps(a.val,b.val); }
inline void operator*=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_mul_ps(a.val,b.val); }
inline void operator/=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_div_ps(a.val,b.val); }
inline void operator&=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_and_ps(a.val,b.val); }
inline void operator|=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_or_ps(a.val,b.val); }
inline void operator^=(SimdVec<float,4> &a,const SimdVec<float,4> &b) { a.val = _mm_xor_ps(a.val,b.val); }

inline SimdVec<float,4> sqrt (const SimdVec<float,4> &a) { return _mm_sqrt_ps (a.val); }
inline SimdVec<float,4> rsqrt(const SimdVec<float,4> &a) { return _mm_rsqrt_ps(a.val); }
inline SimdVec<float,4> neg  (const SimdVec<float,4> &a) { return SimdVec<float,4>( 0 ) - a; }
inline SimdVec<float,4> inv  (const SimdVec<float,4> &a) { return _mm_rcp_ps(a.val); }


#endif // __SSE__


#ifdef __SSE2__

// int
template<> struct SimdSize<int> { static const unsigned res = 4; };

template<> struct SimdVec<int,4> {
    SimdVec() {}
    SimdVec(const int &v) { val = _mm_set1_epi32( v ); }
    SimdVec(const __m128i &v) { val = v; }
    SimdVec(const SimdVec &v) { val = v.val; }
    template<class T2> SimdVec(const SimdVec<T2,4> &v) { val = _mm_set_epi32( v[0], v[1], v[2], v[3] ); }
    SimdVec( int v0, int v1, int v2, int v3 ) { val = _mm_set_epi32( v3, v2, v1, v0 ); }
    static __m128i zero() { return _mm_setzero_si128(); }
    static const unsigned nb_elem = 4;
    const int &operator[](unsigned i) const { return ((const int *)&val)[i]; }
    int &operator[](unsigned i) { return ((int *)&val)[i]; }
    int sum() const { int res = ((const int *)&val)[0]; for(unsigned i=1;i<4;++i) res += ((const int *)&val)[i]; return res; }
    static SimdVec range() { return SimdVec( 0, 1, 2, 3 ); }
    
    template<class TS>
    void write_str( TS &os ) const {
        os << operator[]( 0 );
        for(ST i=1;i<nb_elem;++i) {
            os.write_separator( 0 );
            os << operator[]( i );
        }
    }
    
    __m128i val;
};
inline SimdVec<int,4> operator+(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline SimdVec<int,4> operator-(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline SimdVec<int,4> operator*(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline SimdVec<int,4> operator/(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline SimdVec<int,4> operator%(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline SimdVec<int,4> operator&(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline SimdVec<int,4> operator|(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline SimdVec<int,4> operator^(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline SimdVec<int,4> min(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline SimdVec<int,4> max(const SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline void operator+=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline void operator-=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline void operator*=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
//inline void operator/=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline void operator&=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline void operator|=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));
inline void operator^=(SimdVec<int,4> &a,const SimdVec<int,4> &b) __attribute__((always_inline));

inline SimdVec<int,4> operator+(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_add_epi32( a.val,b.val); }
inline SimdVec<int,4> operator-(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_sub_epi32(a.val,b.val); }
//inline SimdVec<int,4> operator*(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_mul_epu32(a.val,b.val); }
//inline SimdVec<int,4> operator/(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { SimdVec<int,4> res; for( int i = 0; i < 4; ++i ) res[ i ] = a[ i ] / b[ i ]; return res; }
//inline SimdVec<int,4> operator%(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { SimdVec<int,4> res; for( int i = 0; i < 4; ++i ) res[ i ] = a[ i ] % b[ i ]; return res; }
inline SimdVec<int,4> operator&(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_and_si128(a.val,b.val); }
inline SimdVec<int,4> operator|(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_or_si128(a.val,b.val); }
inline SimdVec<int,4> operator^(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { return _mm_xor_si128(a.val,b.val); }
//inline SimdVec<int,4> min(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { SimdVec<int,4> res; for( int i = 0; i < 4; ++i ) res[ i ] = min( a[ i ], b[ i ] ); return res; }
//inline SimdVec<int,4> max(const SimdVec<int,4> &a,const SimdVec<int,4> &b) { SimdVec<int,4> res; for( int i = 0; i < 4; ++i ) res[ i ] = max( a[ i ], b[ i ] ); return res; }
inline void operator+=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_add_epi32(a.val,b.val); }
inline void operator-=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_sub_epi32(a.val,b.val); }
//inline void operator*=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_mul_epu32(a.val,b.val); }
//inline void operator/=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a = a / b; }
inline void operator&=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_and_si128(a.val,b.val); }
inline void operator|=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_or_si128(a.val,b.val); }
inline void operator^=(SimdVec<int,4> &a,const SimdVec<int,4> &b) { a.val = _mm_xor_si128(a.val,b.val); }

inline SimdVec<int,4> neg  (const SimdVec<int,4> &a) { return SimdVec<int,4>( 0 ) - a; }

// double
template<> struct SimdSize<double> { static const unsigned res = 2; };

template<> struct SimdVec<double,2> {
    SimdVec() {}
    SimdVec(double v) { val = _mm_set1_pd(v); }
    inline SimdVec(const __v2df &v) { val = v; }
    //         inline SimdVec(const SimdVec &v) { val = v.val; }
    //         inline SimdVec &operator=(const SimdVec &v) { val = v.val; return *this; }
    template<class T2> SimdVec(const SimdVec<T2,2> &v) { val = _mm_set_pd(v[0],v[1]); }
    SimdVec(double v0,double v1) { val = _mm_set_pd(v1,v0); }
    static __v2df zero() { return _mm_setzero_pd(); }
    static const unsigned nb_elem = 2;
    const double &operator[](unsigned i) const { return ((const double *)&val)[i]; }
    double &operator[](unsigned i) { return ((double *)&val)[i]; }
    double sum() const { double res = ((const double *)&val)[0]; for(unsigned i=1;i<2;++i) res += ((const double *)&val)[i]; return res; }
     
    __v2df val;
};
inline SimdVec<double,2> operator+(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator-(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator*(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator/(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator&(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator|(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> operator^(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> min(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline SimdVec<double,2> max(const SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator+=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator-=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator*=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator/=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator&=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator|=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));
inline void operator^=(SimdVec<double,2> &a,const SimdVec<double,2> &b) __attribute__((always_inline));

inline SimdVec<double,2> operator+(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_add_pd(a.val,b.val); }
inline SimdVec<double,2> operator-(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_sub_pd(a.val,b.val); }
inline SimdVec<double,2> operator*(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_mul_pd(a.val,b.val); }
inline SimdVec<double,2> operator/(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_div_pd(a.val,b.val); }
inline SimdVec<double,2> operator&(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_and_pd(a.val,b.val); }
inline SimdVec<double,2> operator|(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_or_pd(a.val,b.val); }
inline SimdVec<double,2> operator^(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_xor_pd(a.val,b.val); }
inline SimdVec<double,2> min(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_min_pd(a.val,b.val); }
inline SimdVec<double,2> max(const SimdVec<double,2> &a,const SimdVec<double,2> &b) { return _mm_max_pd(a.val,b.val); }
inline void operator+=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_add_pd(a.val,b.val); }
inline void operator-=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_sub_pd(a.val,b.val); }
inline void operator*=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_mul_pd(a.val,b.val); }
inline void operator/=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_div_pd(a.val,b.val); }
inline void operator&=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_and_pd(a.val,b.val); }
inline void operator|=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_or_pd(a.val,b.val); }
inline void operator^=(SimdVec<double,2> &a,const SimdVec<double,2> &b) { a.val = _mm_xor_pd(a.val,b.val); }
#endif // __SSE2__

#ifdef __SSE2__
inline SimdVec<double,2> sqrt (const SimdVec<double,2> &a) { return _mm_sqrt_pd (a.val); }
// inline SimdVec<double,2> rsqrt(const SimdVec<double,2> &a) { return _mm_rsqrt_pd(a.val); }
#endif // __SSE2__


END_METIL_NAMESPACE;

#endif // SIMDVEC_H
