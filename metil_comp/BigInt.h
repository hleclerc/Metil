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

#ifndef METIL_BIG_INT_H
#define METIL_BIG_INT_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file BigInt.cpp
#endif

#include "TypeConfig.h"

namespace Metil {

class BigRat;
class CString;

/*!
   unlimited int.
 */
struct BigInt {
    BigInt();
    BigInt( Unsigned64 v );
    BigInt( Int64 v );
    BigInt( Unsigned32 v );
    BigInt( Int32 v );
    BigInt( const CString &digits, int base = 10 ); ///

    BigInt( const BigInt &b ); 
    void operator=(const BigInt &b);

    ~BigInt();

    void operator+=( const BigInt &b );
    void operator-=( const BigInt &b );
    void operator*=( const BigInt &b );
    void operator/=( const BigInt &b );
    void operator%=( const BigInt &b );
    BigInt operator-() const;

    bool operator< ( const BigInt &b ) const;
    bool operator<=( const BigInt &b ) const;
    bool operator==( const BigInt &b ) const;
    bool operator!=( const BigInt &b ) const;
    bool operator> ( const BigInt &b ) const;
    bool operator>=( const BigInt &b ) const;
    
    bool is_odd() const;
    bool is_even() const;
    
    void basic_assert() const;
   
    operator Float32() const;
    operator Float64() const;
    operator Float96() const;
    
    operator Int8 () const;
    operator Int16() const;
    operator Int32() const;
    operator Int64() const;
    
    operator Unsigned8 () const;
    operator Unsigned16() const;
    operator Unsigned32() const;
    operator Unsigned64() const;
    
    operator bool() const;
    bool is_equal_to_zero     () const;
    bool is_equal_to_one      () const;
    bool is_equal_to_two      () const;
    bool is_equal_to_minus_one() const;

    bool is_strictly_positive() const;
    bool is_positive_or_null () const;
    bool is_strictly_negative() const;
    bool is_negative_or_null () const;

    /** display in base 10 */
    void write_to_stream( class Stream &os ) const;
    
    friend BigInt operator+(const BigInt &a,const BigInt &b);
    friend BigInt operator-(const BigInt &a,const BigInt &b);
    friend BigInt operator*( BigInt a, BigInt b );
    friend BigInt mul_by_lonely_digit( int a,const BigInt &b); /// a is assumed to be < base
    friend int div_by_lonely_digit( BigInt &a, int b ); /// a =in and out . Return the rest.
    friend BigInt operator/( BigInt a, BigInt b );
    friend BigInt operator%( BigInt a, BigInt b );
    friend BigInt gcd( BigInt a, BigInt b );
    friend BigInt abs( const BigInt &a );
    friend BigRat inv( const BigRat &a );
    friend BigRat abs( const BigRat &a ); 

    void set_positive(); /// same effet than abs() but inplace
    
private:
    friend void partial_mac(BigInt &res,const BigInt &a, int m, int offset);
    friend class BigRat;
    template<class TT> friend void init( BigInt &b, TT v );
    void mul_by_base( unsigned nb = 1 );
    void div_by_base();
    void rm_zeroes_at_beginning();
    
    int val;    /// first val ( high weight, the only one which can be < 0 )
    int *ext;   /// supplementary data ( if *this > base )
    unsigned n; /// number if integers int ext. au plus 2^32 chiffres en base "base".
};


bool is_always_strictly_positive( const BigInt &a );
bool is_always_positive_or_null ( const BigInt &a );
bool is_always_equal_to_one     ( const BigInt &a );
bool is_always_equal_to_zero    ( const BigInt &a );

BigInt operator*( const BigInt &a, Int32 b );
BigInt operator*( Int32 a, const BigInt &b );
BigInt operator*( const BigInt &a, Int64 b );
BigInt operator*( Int64 a, const BigInt &b );

Float32 operator+( Float32 a, const BigInt &b );
Float64 operator+( Float64 a, const BigInt &b );
Float96 operator+( Float96 a, const BigInt &b );
Float32 operator+( const BigInt &a, Float32 b );
Float64 operator+( const BigInt &a, Float64 b );
Float96 operator+( const BigInt &a, Float96 b );

Float32 operator-( Float32 a, const BigInt &b );
Float64 operator-( Float64 a, const BigInt &b );
Float96 operator-( Float96 a, const BigInt &b );
Float32 operator-( const BigInt &a, Float32 b );
Float64 operator-( const BigInt &a, Float64 b );
Float96 operator-( const BigInt &a, Float96 b );

Float32 operator*( Float32 a, const BigInt &b );
Float64 operator*( Float64 a, const BigInt &b );
Float96 operator*( Float96 a, const BigInt &b );
Float32 operator*( const BigInt &a, Float32 b );
Float64 operator*( const BigInt &a, Float64 b );
Float96 operator*( const BigInt &a, Float96 b );

Float32 operator/( Float32 a, const BigInt &b );
Float64 operator/( Float64 a, const BigInt &b );
Float96 operator/( Float96 a, const BigInt &b );
Float32 operator/( const BigInt &a, Float32 b );
Float64 operator/( const BigInt &a, Float64 b );
Float96 operator/( const BigInt &a, Float96 b );

BigInt operator-( const BigInt &a, Int32 b );
BigInt operator/( const BigInt &a, Int32 b );

Int32 operator%( const BigInt &a, Int32 b );


}

#endif // METIL_BIG_INT_H

