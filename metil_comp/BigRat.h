#ifndef BIGRAT_H
#define BIGRAT_H

#include "BigInt.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file BigRat.cpp
#endif

namespace Metil {

/**
   Big rational
 */
class BigRat {
public:
    /// see constructor with NoCan
    struct NoCan {};
    
    BigRat();
    BigRat( const BigRat &b );
    BigRat( const CString &num, const CString &den, long _base = 0 );
    BigRat( NoCan, const BigInt &n, const BigInt &d ); /// -> no canonicalization (that is we take n as numerator, d as denominator and that's it)

    template<class T2>
    BigRat( T2 numerator, T2 denominator = 1 ) : num( numerator ), den( denominator ) {
        cannonicalize();
    }

    BigRat &operator=(const BigRat &b);
    BigRat &operator=(const Bool       &val);
    BigRat &operator=(const Int32      &val);
    BigRat &operator=(const Unsigned32 &val);
    BigRat &operator=(const Int64      &val);
    BigRat &operator=(const Unsigned64 &val);

    void cannonicalize();

    BigRat operator-() const;
    
    void operator+=(const BigRat &b);
    void operator-=(const BigRat &b);
    void operator*=(const BigRat &b);
    void operator/=(const BigRat &b);
    void operator%=(const BigRat &b);
    
    ///
    operator bool () const;
    
    operator Int8 () const;
    operator Int16() const;
    operator Int32() const;
    operator Int64() const;
    
    operator Unsigned8 () const;
    operator Unsigned16() const;
    operator Unsigned32() const;
    operator Unsigned64() const;
    
    operator Float32() const;
    operator Float64() const;
    operator Float96() const;
    
    ///
    bool operator==(const BigRat &b) const;
    bool operator!=(const BigRat &b) const;
    bool operator< (const BigRat &b) const;
    bool operator<=(const BigRat &b) const;
    bool operator> (const BigRat &b) const;
    bool operator>=(const BigRat &b) const;

    bool operator>=(int b) const;
    bool operator> (int b) const;

    bool is_integer                () const;
    bool is_odd                    () const;
    bool is_even                   () const;
    bool is_strictly_negative      () const;
    bool is_strictly_positive      () const;
    bool is_positive_or_null       () const;
    bool is_negative_or_null       () const;
    bool is_equal_to_zero          () const;
    bool is_equal_to_one           () const;
    bool is_equal_to_two           () const;
    bool is_equal_to_three         () const;
    bool is_equal_to_minus_one     () const;
    bool is_equal_to_minus_two     () const;
    bool is_equal_to_one_half      () const;
    bool is_equal_to_minus_one_half() const;
    
    void write_to_stream( Stream &os ) const;

    friend bool is_always_strictly_positive( const BigRat &a );
    friend bool is_always_positive_or_null ( const BigRat &a );
    friend bool is_always_equal_to_one     ( const BigRat &a );
    friend bool is_always_equal_to_zero    ( const BigRat &a );
    friend BigRat inv( const BigRat &a );
    // +
    friend BigRat operator+( const BigRat &a, const BigRat &b );
    friend BigRat operator+( const BigRat &a, Int64                        b );
    friend BigRat operator+( Int64                        a, const BigRat &b );
    friend BigRat operator+( const BigRat &a, Int32                        b );
    friend BigRat operator+( Int32                        a, const BigRat &b );
    friend BigRat operator+( const BigRat &a, const BigInt                &b );
    friend BigRat operator+( const BigInt &a, const BigRat                &b );
    friend Float32 operator+( const BigRat &a, Float32                      b );
    friend Float32 operator+( Float32                      a, const BigRat &b );
    friend Float64 operator+( const BigRat &a, Float64                      b );
    friend Float64 operator+( Float64                      a, const BigRat &b );
    friend Float96 operator+( const BigRat &a, Float96                     &b );
    friend Float96 operator+( Float96      &a, const BigRat                &b );
    
    
    
    // -
    friend BigRat operator-( const BigRat &a, const BigRat &b );
    friend BigRat operator-( const BigRat &a, Int64                        b );
    friend BigRat operator-( Int64                        a, const BigRat &b );
    friend BigRat operator-( const BigRat &a, Int32                        b );
    friend BigRat operator-( Int32         a, const BigRat                &b );
    friend BigRat operator-( const BigRat &a, const BigInt                &b );
    friend BigRat operator-( const BigInt &a, const BigRat                &b );
    friend Float32 operator-( const BigRat &a, Float32                      b );
    friend Float32 operator-( Float32                      a, const BigRat &b );
    friend Float64 operator-( const BigRat &a, Float64                      b );
    friend Float64 operator-( Float64                      a, const BigRat &b );
    friend Float96 operator-( const BigRat &a, Float96                     &b );
    friend Float96 operator-( Float96      &a, const BigRat                &b );
    // *
    friend BigRat operator*( const BigRat &a, const BigRat &b );
    friend BigRat operator*( const BigRat &a, Int64                        b );
    friend BigRat operator*( Int64                        a, const BigRat &b );
    friend BigRat operator*( const BigRat &a, Int32         b );
    friend BigRat operator*( Int32         a, const BigRat &b );
    friend BigRat operator*( const BigRat &a, const BigInt &b );
    friend BigRat operator*( const BigInt &a, const BigRat &b );
    friend Float32 operator*( const BigRat &a, Float32                      b );
    friend Float32 operator*( Float32                      a, const BigRat &b );
    friend Float64 operator*( const BigRat &a, Float64                      b );
    friend Float64 operator*( Float64                      a, const BigRat &b );
    friend Float96 operator*( const BigRat &a, Float96                     &b );
    friend Float96 operator*( Float96      &a, const BigRat                &b );
    // /
    friend BigRat operator/( const BigRat &a, const BigRat &b);
    friend BigRat operator/( const BigRat &a, Int64                        b );
    friend BigRat operator/( Int64                        a, const BigRat &b );
    friend BigRat operator/( const BigRat &a, Int32         b );
    friend BigRat operator/( Int32         a, const BigRat &b );
    friend BigRat operator/( const BigRat &a, const BigInt &b );
    friend BigRat operator/( const BigInt &a, const BigRat &b );
    friend Float32 operator/( const BigRat &a, Float32                      b );
    friend Float32 operator/( Float32                      a, const BigRat &b );
    friend Float64 operator/( const BigRat &a, Float64                      b );
    friend Float64 operator/( Float64                      a, const BigRat &b );
    friend Float96 operator/( const BigRat &a, Float96                     &b );
    friend Float96 operator/( Float96      &a, const BigRat                &b );
    // %
    friend BigRat operator%( const BigRat &a, const BigRat &b );
    friend BigRat abs( const BigRat &a );
    friend BigRat mod( const BigRat &a, const BigRat &b );
    
private:
    BigInt num, den;
};

}

#endif // BIGRAT_H
