/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "BigInt.h"
#include "File.h"
#include "BasicVec.h"
#include "CString.h"

#include <stdlib.h>

namespace Metil {

typedef int T;

static const T base = 1L << ( sizeof( T ) * 4 - 1 ); /// plus portable que EDX:EAX. Le -1 est nécessaire car on utilise un entier signé.
static const T nb_digits_base10 = T( log10( base ) );
static const T base10 = T( pow( 10, nb_digits_base10 ) );

template<class TT> struct BaseForType { static const T res = base; };
template<> struct BaseForType<Unsigned16> { static const Unsigned32 res = base; };
template<> struct BaseForType<Unsigned32> { static const Unsigned32 res = base; };
template<> struct BaseForType<Unsigned64> { static const Unsigned64 res = base; };

BigInt::BigInt() {
    val = 0;
    n = 0;
    ext = 0;
    //PRINT( base );
}

BigInt::BigInt( const CString &digits, int b ) {
    val = 0;
    n = 0;
    ext = 0;
    if (b != 10)
        ASSERT( 0, "TODO" );
    if ( digits.empty() )
        return;
    //
    T sign = 1;
    int i = 0;
    char c;
    if (digits[0] == '-') {
        sign = -1;
        i++;
    }
    val = digits[i]-'0';
    for( i++; (c = digits[i]) != '\0'; ++i ) {
        Unsigned32 t = c - '0';
        BigInt tempon =  mul_by_lonely_digit( b, *this );
        (*this) = tempon + BigInt( t );
    }
    val *= sign;
}

template<class TT> 
void init( BigInt &b, TT v ) {
    if ( v < 0 ) {
        init( b, -v );
        b.val = - b.val;
    } else {
        b.n = 0;
        TT tmp = v;
        while ( tmp >= BaseForType<TT>::res ) {
            tmp /= base;
            ++b.n;
        }
        if ( b.n ) {
            b.ext = (T *)malloc( sizeof( T ) * b.n );
            unsigned n2 = b.n - 1;
            while ( v >= BaseForType<TT>::res ) {
                b.ext[ n2-- ] = v % base;
                v /= base;
            }
        } else
            b.ext = 0;
            b.val = v;
    }
}

BigInt::BigInt( Unsigned64 v ) { init( *this, v ); }
BigInt::BigInt( Int64      v ) { init( *this, v ); }
BigInt::BigInt( Unsigned32 v ) { init( *this, v ); }
BigInt::BigInt( Int32      v ) { init( *this, v ); }

// template<class TT> 
// void BigInt::init_f( TT v = 0 ) { /// version pour Float32, Float64 et Float96 qui est valable seulement si le type Float64 peut représenter le nombre base.
//     if ( v < 0. ) {
//         init_f( -v );
//         val = - val;
//     }
//     else {
//         n = 0;
//         TT tmp = v;
//         while ( tmp >= base ) { tmp /= base; ++n; }
//         if ( n ) {
//             ext = (T *)malloc( sizeof(T) * n );
//             unsigned n2 = n-1;
//             while ( v >= base ) {
//                 Float64 tmp2 = fmod(v,base);
//                 ext[n2--] = T(tmp2) ;
//                 v = (v - tmp2)/base;
//             }
//         }
//         else
//             ext = NULL;
//         val = T(v);
//     }
// }

// void BigInt::init( const BigInt &b ) {
//     val = b.val;
//     n = b.n;
//     if ( b.n ) {
//         ext = (long *)malloc( sizeof(T) * b.n );
//         for(unsigned i=0;i<n;++i) ext[i] = b.ext[i];
//     }
//     else
//         ext = NULL;
// }

BigInt::~BigInt() {
    if ( n )
        free( ext );
    n = 0;
}

BigInt::BigInt( const BigInt &b ) {
    val = b.val;
    n = b.n;
    if ( b.n ) {
        ext = (T *)malloc( sizeof(T) * b.n );
        for(unsigned i=0;i<n;++i) ext[i] = b.ext[i];
    } else
        ext = NULL;
}

void BigInt::operator=(const BigInt &b) {
    if ( n )
        free(ext);
    val = b.val;
    n = b.n;
    if ( b.n ) {
        ext = (T *)malloc( sizeof(T) * b.n );
        for(unsigned i=0;i<n;++i) ext[i] = b.ext[i];
    }
}

void BigInt::operator+=(const BigInt &b) { *this = *this + b; }
void BigInt::operator-=(const BigInt &b) { *this = *this - b; }
void BigInt::operator*=(const BigInt &b) { *this = *this * b; }
void BigInt::operator/=(const BigInt &b) { *this = *this / b; }
void BigInt::operator%=(const BigInt &b) { *this = *this % b; }
BigInt BigInt::operator-() const { /*basic_assert();*/ BigInt r = *this; r.val = -r.val; /*r.basic_assert();*/ return r; }

void BigInt::mul_by_base(unsigned nb ) { /// this = this * base;
    if ( n==0 and val==0 ) return;
    
    T *oe = ext;
    ext = (T *)malloc( sizeof(T) * (n+nb) );
    if ( n ) {
        for(unsigned i=0;i<n;++i)
            ext[i] = oe[i];
        free(oe);
    }
    while ( nb-- )
        ext[n++] = 0;
}

bool BigInt::operator<(const BigInt &b) const {
    if ( val < 0 ) {
        if ( b.val < 0 )
            return -*this > -b;
        return true;
    } else if ( b.val < 0 )
        return false;
        //
        if ( n < b.n ) return true;
        if ( n > b.n ) return false;
        // same n
        if ( n == 0 ) { return val < b.val; }
        if ( b.val < 0 )
            return false;
        //
        if ( val < b.val ) return true;
        if ( val > b.val ) return false;
        for(unsigned i=0;i<n-1;++i) {
            if ( ext[i] < b.ext[i] ) return true;
            if ( ext[i] > b.ext[i] ) return false;
        }
        return ( ext[n-1] < b.ext[n-1] );
}
bool BigInt::operator<=(const BigInt &b) const {
    if ( val < 0 ) {
        if ( b.val < 0 )
            return -*this >= -b;
        return true;
    } else if ( b.val < 0 )
        return false;
        //
        if ( n < b.n ) return true;
        if ( n > b.n ) return false;
    // same n
        if ( n == 0 ) { return val <= b.val; }
        //
        if ( val < b.val ) return true;
        if ( val > b.val ) return false;
        for(unsigned i=0;i<n-1;++i) {
            if ( ext[i] < b.ext[i] ) return true;
            if ( ext[i] > b.ext[i] ) return false;
        }
        return ( ext[n-1] <= b.ext[n-1] );
}

bool BigInt::operator==(const BigInt &b) const {
    if ( n!=b.n ) return false;
    if ( val != b.val ) return false;
    for(unsigned i=0;i<n;++i)
        if ( ext[i] != b.ext[i] )
            return false;
    return true;
}
    
bool BigInt::operator!=(const BigInt &b) const { return not ( *this == b ); }
bool BigInt::operator> (const BigInt &b) const { return ( b <  *this ); }
bool BigInt::operator>=(const BigInt &b) const { return ( b <= *this ); }
    
bool BigInt::is_odd() const {
    if ( n == 0 ) return val & 1;
    return ext[ n - 1 ] & 1;
}
bool BigInt::is_even() const {
    if ( n == 0 ) return not ( val & 1 );
    return not ( ext[ n - 1 ] & 1 );
}

void BigInt::div_by_base() { /// divide this by base
    if ( n ) {
        --n;
        if ( n == 0 )
            free( ext );
    }
    else
        val = 0;
}
void BigInt::rm_zeroes_at_beginning() {
    if ( val or not n ) return;
    for(unsigned i=0;i<n;++i) {
        if ( ext[i] ) { // first non zero
            val = ext[i++];
            n -= i;
            for(unsigned j = 0; j<n ; ++i, ++j)
                ext[j] = ext[i];
            if ( n==0 ) free( ext );
            return;
        }
    }
    // else
    n = 0;
    free( ext );
}

BigInt::operator Float32() const { Float32 res = abs(val);
 for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Float64() const { Float64 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Float96() const { Float96 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }

BigInt::operator Int8 () const { Int8  res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Int16() const { Int16 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Int32() const { Int32 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Int64() const { Int64 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }

BigInt::operator Unsigned8 () const { Unsigned8  res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Unsigned16() const { Unsigned16 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Unsigned32() const { Unsigned32 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }
BigInt::operator Unsigned64() const { Unsigned64 res = abs(val); for(unsigned i=0;i<n;++i) { res *= base; res += ext[i]; } return ( val < 0 ? -res : res ); }

BigInt::operator bool() const { return val; }
bool BigInt::is_equal_to_zero     () const { return val==0; }
bool BigInt::is_equal_to_one      () const { return n==0 and val==1; }
bool BigInt::is_equal_to_two      () const { return n==0 and val==2; }
bool BigInt::is_equal_to_minus_one() const { return n==0 and val==-1; }

bool BigInt::is_strictly_positive() const { return val >  0; }
bool BigInt::is_positive_or_null () const { return val >= 0; }

bool BigInt::is_strictly_negative() const { return val <  0; }
bool BigInt::is_negative_or_null () const { return val <= 0; }

void BigInt::write_to_stream( Stream &oss ) const {
    if ( n == 0 )
        oss << val;
    else {
        char ld[ nb_digits_base10 ];
        BigInt tmp = abs( *this );
        BasicVec<T,-1,1> decimal;
        while( tmp.is_strictly_positive() )
            decimal.push_back( div_by_lonely_digit( tmp, base10 ) );
        if ( this->is_positive_or_null() )
            oss << decimal.back();
        else
            oss << -decimal.back();
        if ( decimal.size() >= 2 )
            for( Unsigned64 i = decimal.size()-2; ; ) {
                // memset( ld, '0', nb_digits_base10 );
                for(int j=0;j<nb_digits_base10;++j)
                   ld[ j ] = '0';
                for( unsigned t = 0; decimal[i]>0; ++t ) {
                    ldiv_t res = ldiv ( decimal[i], 10 );
                    ld[t] = '0' + res.rem;
                    decimal[i] = res.quot;
                }
                for( int t = 0; t<nb_digits_base10; ++t )
                    oss << ld[nb_digits_base10-1-t];
                if (not(i))
                    break;
                i--;
            }
    }
}

BigInt operator+(const BigInt &a,const BigInt &b) {
    if ( b.val < 0 ) {
        if ( a.val < 0 )
            return - ( (-a) + (-b) );
        else
            return a - (-b);
    }
    else if ( a.val < 0 )
        return b - (-a);

    BigInt res;
    res.n = max( a.n, b.n ); /// will grow if ret
    if ( res.n )
        res.ext = (T *)malloc( sizeof( T ) * ( res.n + 1 ) );

    int ret = 0;
    if ( res.n ) {
        unsigned i;
        /// ext
        for(i=1;i<=min( a.n, b.n );++i) {
            int v = a.ext[a.n-i] + b.ext[b.n-i] + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.ext[res.n-i] = v;
        }
            /// mixed ext and val
        if ( i<=a.n ) {
            int v = a.ext[a.n-i] + b.val + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.ext[res.n-i] = v;
            while ( ++i <= a.n ) {
                v = a.ext[a.n-i] + ret;
                if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
                res.ext[res.n-i] = v;
            }
            v = a.val + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.val = v;
        }
        else if ( i<=b.n ) {
            int v = b.ext[b.n-i] + a.val + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.ext[res.n-i] = v;
            while ( ++i <= b.n ) {
                v = b.ext[b.n-i] + ret;
                if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
                res.ext[res.n-i] = v;
            }
            v = b.val + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.val = v;
        }
        else {
            int v = a.val + b.val + ret;
            if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
            res.val = v;
        }
    }
    else {
        int v = a.val + b.val;
        if ( v >= base ) { ret = 1; v -= base; } else ret = 0;
        res.val = v;
    }

    if ( ret ) {
        if ( res.n == 0 )
            res.ext = (T *)malloc( sizeof(T) * 1 );
        for(unsigned i=1;i<=res.n;++i)
            res.ext[res.n-i+1] = res.ext[res.n-i];
        ++res.n;
        res.ext[0] = res.val;
        res.val = 1;
    }
    return res;
}

BigInt operator-(const BigInt &a,const BigInt &b) {
    if ( b.val < 0 ) {
        if ( a.val < 0 )
            return - ( (-a) - (-b) );
        else
            return a + (-b);
    }
    else if ( a.val < 0 )
        return -( (-a) + b );

    if ( a < b ) {
        BigInt res = b - a;
        res.val = - res.val;
        return res;
    }

    BigInt res( 0 );
    if ( a.n ) {
        res.ext = (T *)malloc( sizeof(T) * a.n );
        res.n = a.n;
    }
    /// we can assume that a > b
    int ret = 0;
    unsigned i;
    for(i=1;i<=b.n;++i) {
        int v = a.ext[a.n-i] - b.ext[b.n-i] - ret;
        if ( v < 0 ) { ret = 1; v += base; } else ret = 0;
        res.ext[res.n-i] = v;
    }
    //
    if ( i <= a.n ) {
        int v = a.ext[a.n-i] - b.val - ret;
        if ( v < 0 ) { ret = 1; v += base; } else ret = 0;
        res.ext[res.n-i] = v;

        while ( ++i <= a.n ) {
            v = a.ext[a.n-i] - ret;
            if ( v < 0 ) { ret = 1; v += base; } else ret = 0;
            res.ext[res.n-i] = v;
        }

        v = a.val - ret;
        if ( v < 0 ) { ret = 1; v += base; } else ret = 0;
        res.val = v;
    }
    else {
        int v = a.val - b.val - ret;
        if ( v < 0 ) { ret = 1; v += base; } else ret = 0;
        res.val = v;
    }
    /// elimination of zeros at the beginning
    res.rm_zeroes_at_beginning();

    ///     res.basic_assert();    
    return res;
}

void partial_mac( BigInt &res, const BigInt &a, T m, int offset ) {
    int ret = 0;
    
    T *r = res.ext + res.n - offset;
    
    // a.ext
    for(unsigned i=1;i<=a.n;++i) {
        int v = a.ext[a.n-i] * m + *r + ret;
        if ( v >= base ) { ret = v / base; v %= base; } else ret = 0;
        *(r--) = v;
    }
    
    // a.val
    int v = abs(a.val) * m + *r + ret;
    if ( v >= base ) { ret = v / base; v %= base; } else ret = 0;
    *(r--) = v;
    
    // ret
    // *(r--) += ret;
    while ( ret ) {
        int v = *r + ret;
        if ( v >= base ) { ret = v / base; v %= base; } else ret = 0;
        *(r--) = v;
    }
}

BigInt operator*(BigInt a, BigInt b) {
    if ( a.n + b.n == 0 ) {
        int v = a.val * b.val;
        if ( abs(v) >= base ) {
            BigInt res;
            res.val = v / base;
            res.n = 1;
            res.ext = (T *)malloc( sizeof(T) );
            res.ext[0] = abs(v) % base;
            return res;
        }
        // else
        BigInt res;
        res.val = v;
        return res;
    }
    bool sgn = ( a.val < 0 ) xor ( b.val < 0 );
    a.val = abs( a.val );
    b.val = abs( b.val );
    
    /// we will have to cope with a.ext or b.ext
    BigInt res;
    res.n = a.n + b.n + 2; // 
    res.ext = (T *)malloc( sizeof(T *) * res.n );
    res.val = 0;
    for(unsigned i=0;i<res.n;++i) res.ext[i] = 0;
    
    for(unsigned i=1;i<=b.n;++i)
        partial_mac( res, a, b.ext[b.n-i], i );
    partial_mac( res, a, abs(b.val), b.n+1 );
    
    /// elimination of zeros at the beginning
    res.rm_zeroes_at_beginning();
    
    if ( sgn )
        res.val = -res.val;
    return res;
}

bool is_always_strictly_positive( const BigInt &a ) { return a.is_strictly_positive(); }
bool is_always_positive_or_null ( const BigInt &a ) { return a.is_positive_or_null (); }
bool is_always_equal_to_one     ( const BigInt &a ) { return a.is_equal_to_one     (); }
bool is_always_equal_to_zero    ( const BigInt &a ) { return a.is_equal_to_zero    (); }

BigInt operator*( const BigInt &a, Int64 b ) { return a * BigInt( b ); }
BigInt operator*( Int64 a, const BigInt &b ) { return BigInt( a ) * b; }
BigInt operator*( const BigInt &a, Int32 b ) { return a * BigInt( b ); }
BigInt operator*( Int32 a, const BigInt &b ) { return BigInt( a ) * b; }

/*! a is assumed to be < base */
BigInt mul_by_lonely_digit( T a,const BigInt &b) {
    if ( b.n == 0 ) {
        T v = a * b.val;
        if ( v >= base ) {
            BigInt res;
            res.val = v / base;
            res.n = 1;
            res.ext = (T *)malloc( sizeof(T) );
            res.ext[0] = v % base;
            return res;
        }
        /// else
        BigInt res;
        res.val = v;
        return res;
    }

    /// we will have to cope with a.ext or b.ext
    BigInt res;
    res.n = b.n + 2;
    res.ext = (T *) malloc( sizeof(T *) * res.n );
    res.val = 0;
    for(unsigned i=0;i<res.n;++i) res.ext[i] = 0;

    partial_mac( res, b, a, 1 );

    /// elimination of zeros at the beginning
    res.rm_zeroes_at_beginning();
    return res;
}

BigInt operator/( BigInt a, BigInt b ) {
    BigInt res;
    /// when n == 0 (no extension)
    if ( a.n == 0 and b.n == 0 ) { res.val = a.val / b.val; return res; }
    /// < 0
    if ( a.val<0 or b.val<0 ) {
        bool sgn = ( a.val < 0 ) xor ( b.val < 0 );
        a.val = abs( a.val );
        b.val = abs( b.val );
        res = a / b;
        if ( sgn )
            res.val = -res.val;
        return res;
    }
    /// Ex : 12 / 123
    if ( a < b ) return res;

    /// as in school
    typedef BigInt B;
    while ( a.n > b.n + 1 ) {
        B tmp = b;
        int o = a.n - tmp.n - 1 + (tmp.val < a.val);
        tmp.mul_by_base( o );
        int mult_tot = 0;
        while ( a >= tmp ) {
            int m = a.val * ( a.n==tmp.n ? 1 : base ) / tmp.val / 2;
            a = a - ( m > 1 ? B(m) * tmp : tmp );
            mult_tot += ( m > 1 ? m : 1 );
        }
        B m = mult_tot; m.mul_by_base( o ); res = res + m;
    }
    while ( a >= b ) {
        int m = a.val * ( a.n==b.n ? 1 : base ) / b.val / 2;
        a = a - ( m > 1 ? B(m) * b : b );
        res = res + B( m > 1 ? m : 1 );
    }
    return res;
}

BigInt operator%( BigInt a, BigInt b ) {
    if ( b.n==0 and b.val==0 ) {
        throw "Division by zero";
        return b;
    }

        /// when n == 0 (no extension)
    if ( a.n == 0 and b.n == 0 ) { a.val %= b.val; if (a.val<0) a.val+= b.val; return a; }

            /// < 0
    bool minus_sgn = ( a.val<0 ) xor ( b.val<0 );
    a.val = abs( a.val );
    b.val = abs( b.val );

    /// Ex : 12 % 123
    if ( a < b ) {
        if ( minus_sgn ) a.val = -a.val;
        return a;
    }

    /// as in school
    typedef BigInt B;
    while ( a.n > b.n + 1 ) {
        B tmp = b;
        tmp.mul_by_base( a.n - tmp.n - 1 + (tmp.val < a.val) );
        while ( a >= tmp ) {
            int m = a.val * ( a.n==tmp.n ? 1 : base ) / tmp.val / 2;
            a = a - ( m > 1 ? B(m) * tmp : tmp );
        }
    }
    while ( a >= b ) {
        int m = a.val * ( a.n==b.n ? 1 : base ) / b.val / 2;
        a = a - ( m > 1 ? B(m) * b : b );
    }

    if ( minus_sgn ) a = b - a;

    return a;
}

BigInt gcd( BigInt a, BigInt b ) {
    if ( b.val == 1 and b.n == 0 )
        return 0;

    BigInt old;
    while ( b ) {
        old = b;
        b = a % b;
        a = old;
    }
    return a;
}

BigInt abs( const BigInt &a ) {
    BigInt res = a;
    res.set_positive();
    return res;
}

/// on suppose que b > 0 et b < base . Si a >= 0 alors le reste, r,  et le quotient, q,  correspondent à celui de la définition mathématique. Sinon -a = (-q) * b + (-r) : i.e. q et r sont négatifs et 0 <= abs(r) < b 
T div_by_lonely_digit( BigInt &a, T b ) {
    if (b==1)
        return 0;
    T sign = a.val >= 0 ? 1 : -1;
    a.val = abs( a.val );
    ldiv_t res = ldiv ( a.val, b );
    a.val = res.quot;
    T carry = res.rem;
    if (a.n) {
        for( unsigned i = 0; i<a.n; ++i) {
            res = ldiv ( carry * base + a.ext[i], b );
            a.ext[i] = res.quot;
            carry = res.rem; 
        }
    }
    if (( a.val == 0 ) and (a.n)) {
        a.val = a.ext[0];
        for( unsigned i = 1; i< a.n; ++i)
            a.ext[i-1] = a.ext[i];
        a.n--;
        if (a.n)
            a.ext = (T*) realloc( a.ext, sizeof(T) * a.n );
        else {
            free( a.ext );
            a.ext = NULL;
        }
    }
    a.val *= sign;
    carry *= sign;
    return carry;
}

void BigInt::set_positive() {
    val = abs( val );   
}

Float32 operator+( Float32 a, const BigInt &b ) { return a + Float32( b ); }
Float64 operator+( Float64 a, const BigInt &b ) { return a + Float64( b ); }
Float96 operator+( Float96 a, const BigInt &b ) { return a + Float96( b ); }
Float32 operator+( const BigInt &a, Float32 b ) { return Float32( a ) + b; }
Float64 operator+( const BigInt &a, Float64 b ) { return Float64( a ) + b; }
Float96 operator+( const BigInt &a, Float96 b ) { return Float96( a ) + b; }

Float32 operator-( Float32 a, const BigInt &b ) { return a - Float32( b ); }
Float64 operator-( Float64 a, const BigInt &b ) { return a - Float64( b ); }
Float96 operator-( Float96 a, const BigInt &b ) { return a - Float96( b ); }
Float32 operator-( const BigInt &a, Float32 b ) { return Float32( a ) - b; }
Float64 operator-( const BigInt &a, Float64 b ) { return Float64( a ) - b; }
Float96 operator-( const BigInt &a, Float96 b ) { return Float96( a ) - b; }

Float32 operator*( Float32 a, const BigInt &b ) { return a * Float32( b ); }
Float64 operator*( Float64 a, const BigInt &b ) { return a * Float64( b ); }
Float96 operator*( Float96 a, const BigInt &b ) { return a * Float96( b ); }
Float32 operator*( const BigInt &a, Float32 b ) { return Float32( a ) * b; }
Float64 operator*( const BigInt &a, Float64 b ) { return Float64( a ) * b; }
Float96 operator*( const BigInt &a, Float96 b ) { return Float96( a ) * b; }

Float32 operator/( Float32 a, const BigInt &b ) { return a / Float32( b ); }
Float64 operator/( Float64 a, const BigInt &b ) { return a / Float64( b ); }
Float96 operator/( Float96 a, const BigInt &b ) { return a / Float96( b ); }
Float32 operator/( const BigInt &a, Float32 b ) { return Float32( a ) / b; }
Float64 operator/( const BigInt &a, Float64 b ) { return Float64( a ) / b; }
Float96 operator/( const BigInt &a, Float96 b ) { return Float96( a ) / b; }

BigInt operator-( const BigInt &a, Int32 b ) { return a - BigInt( b ); } // TODO : optimize
BigInt operator/( const BigInt &a, Int32 b ) { BigInt res = a; div_by_lonely_digit( res, b ); return res; }
Int32 operator%( const BigInt &a, Int32 b ) { BigInt tmp = a; return Int32( div_by_lonely_digit( tmp, b ) ); }


}
