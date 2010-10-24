#include "BigRat.h"
#include "Stream.h"
#include "CommonFunctions.h"
#include "File.h"
#include "CString.h"

#include <stdlib.h> /// labs

namespace Metil {

BigRat::BigRat() : den( 1 ) {}

BigRat::BigRat( const BigRat &b ) : num( b.num ), den( b.den ) { }

BigRat &BigRat::operator=(const BigRat &b) { num = b.num; den = b.den; return *this; }

BigRat::BigRat( NoCan, const BigInt &n, const BigInt &d ) : num( n ), den( n ) {}

BigRat::BigRat( const CString &num, const CString &den, long _base ) : num( num ), den( den ) { cannonicalize(); }

//void init_from_sign_expo_mant( bool sign, Int32 expo, Unsigned64 mant ) {
//    num = mant;
//    den = 1;
//    BI b2( 2 );
//    if      ( expo > 0 ) { while ( expo-- ) num = num * b2; }
//    else if ( expo < 0 ) { while ( expo++ ) den = den * b2; }
//    else                 { num = 1; den = 1; }
//    if ( sign )
//        num.val = - num.val;
//    cannonicalize();
//}

//    La fonction utilise les fractions continues : cf par exemple manuel de calcul numérique appliqué C. Guilpin, ed. EDP Sciences.
//    Un mot sur le paramètre tol. On compare notre fraction q à la valeur initiale val en calculant | q - val | / (1 + | val | ) et en comparant le résultat à l'epsilon du type flottant fois 2^tol. Expérimentalement tol = 4 convient.
//    Un pire cas pour les fractions continues est le nombre d'or, noté phi,  solution positive de l'équation x^2 = x + 1 soit x = 1 + 1 / x d'où le développement en fraction continue : 1 + 1 / ( 1 + 1 / ( 1 + 1 / ( ...   ))))). Tous les coefficients valent un. Voir la page de wikipedia \a http://fr.wikipedia.org/wiki/Nombre_d'or . C'est pour ce nombre que j'ai choisi une limite de 40 pour la boucle.
//    phi = (1+sqrt(5))/2 ~ 1.618033988749894848204586834365638117720309179805.
//
//    \friend raphael.pasquier@lmt.ens-cachan.fr
//    template<class TFLOAT,int base2,class T2,int offset2,bool owning2> static void approx(const TFLOAT &val, BigInt<base2,T2,offset2,owning2> &nume, BigInt<base2,T2,offset2,owning2> &deno, int tol=4 ) {
//        Float64 ent,v,abs_v, i_abs_v;
//        BigInt<base2,T2,offset2,owning2> tmpA,tmpB;
//
//        abs_v = fabs(val);
//        i_abs_v = 1./(1.+abs_v);
//        v = modf(abs_v,&ent);
//        //std::cout << " frac  = " << std::setprecision(17) << v << "    ent = " << std::setprecision(17) << ent << std::endl;
//        BigInt<base2,T2,offset2,owning2> A0(ent);
//        BigInt<base2,T2,offset2,owning2> B0(1);
//
//        //if (v/(ent+1.)<1.e-10){ //if (fabs(v)<ldexp(std::numeric_limits<Float64>::epsilon(),20)) {
//        if ((fabs(abs_v-Float64(A0)/Float64(B0))*i_abs_v)<ldexp(std::numeric_limits<TFLOAT>::epsilon(),tol)) {
//            if (val>0.)
//                nume = A0;
//            else
//                nume = -A0;
//            deno = B0;
//            return;
//        } else
//            v = 1./v;
//        v = modf(v,&ent);
//        BigInt<base2,T2,offset2,owning2> B1(ent);
//        BigInt<base2,T2,offset2,owning2> A1;
//        BigInt<base2,T2,offset2,owning2> one(1);
//        A1 = A0*B1+one;
//        //std::cout << " frac  = " << std::setprecision(17) << v << "    ent = " << std::setprecision(17) << ent << std::endl;
//        //if (v/(ent+1.)<1.e-8) { //if (fabs(v)<ldexp(std::numeric_limits<Float64>::epsilon(),20)) {
//        if ((fabs(abs_v-Float64(A1)/Float64(B1))*i_abs_v)<ldexp(std::numeric_limits<TFLOAT>::epsilon(),tol)) {
//            if (val>0.)
//                nume = A1;
//            else
//                nume = -A1;
//            deno = B1;
//            return;
//        } else
//            v = 1./v;
//
//        for(int jj=0;jj<40;jj++) {
//            v = modf(v,&ent);
//            //std::cout << " @ " << jj << " @  frac  = " << std::setprecision(17) << v << "    ent = " << std::setprecision(17) << ent << std::endl;
//            tmpA = A1;
//            tmpB = B1;
//            BigInt<base2,T2,offset2,owning2> tmp(ent);
//            A1 = A1 * tmp + A0;
//            B1 = B1 * tmp + B0;
//            //std::cout << jj << " ____ " << A1 << "  /  " << B1 << " ____ " << std::endl;
//            //std::cout << " erreur = " << (fabs(abs_v-Float64(A1)/Float64(B1))*i_abs_v) << std::endl;
//            //if (v/(ent+1.)<1.e-8) { //if (fabs(v)<ldexp(std::numeric_limits<Float64>::epsilon(),26)) {
//            if ((fabs(abs_v-Float64(A1)/Float64(B1))*i_abs_v)<ldexp(std::numeric_limits<TFLOAT>::epsilon(),tol))
//                break;
//            v = 1./v;
//            A0 = tmpA;
//            B0 = tmpB;
//        }
//        if (val>0.)
//            nume = A1;
//        else
//            nume = -A1;
//        deno = B1;
//    }

//     BigRat( const Float64 &val ) {
//         const ieee754_double &v = reinterpret_cast<const ieee754_double &>( val );
//         init_from_sign_expo_mant( v.ieee.negative, (Int32)v.ieee.exponent - IEEE754_DOUBLE_BIAS - 52, ( Unsigned64( v.ieee.mantissa0 + 0x100000UL ) << 32 ) + v.ieee.mantissa1 );
//     }

//     BigRat( const Float96 &val ) {
//         if ( val == 0 ) { num = 0; den = 1; return; }
//         const ieee854_long_double &v = reinterpret_cast<const ieee854_long_double &>( val );
//         init_from_sign_expo_mant( v.ieee.negative, (Int32)v.ieee.exponent - IEEE854_LONG_DOUBLE_BIAS - 63, ( Unsigned64( v.ieee.mantissa0 ) << 32 ) + v.ieee.mantissa1 );
//     }

//    BigRat( const Float96 &val ) {
//        approx<Float96,base,T,offset>(val,num,den);
//    }

void BigRat::cannonicalize() {
    if ( den.val < 0 ) {
        num.val = -num.val;
        den.val = -den.val;
    }
    //
    if ( num.val < 0 ) {
        num.val = -num.val;
        BigInt g = gcd( num, den );
        if ( g.val ) {
            num = num / g;
            den = den / g;
        }
        num.val = -num.val;
    } else {
        BigInt g = gcd( num, den );
        if ( g.val ) {
            num = num / g;
            den = den / g;
        }
    }

}
///
BigRat BigRat::operator-() const { BigRat res = *this; res.num.val = - res.num.val; return res; }

void BigRat::operator+=(const BigRat &b) { *this = *this + b; }
void BigRat::operator-=(const BigRat &b) { *this = *this - b; }
void BigRat::operator*=(const BigRat &b) { *this = *this * b; }
void BigRat::operator/=(const BigRat &b) { *this = *this / b; }
void BigRat::operator%=(const BigRat &b) { *this = *this % b; }

///
BigRat::operator bool   () const { return bool(num); }

BigRat::operator Int8 () const { return Int8 ( num / den ); }
BigRat::operator Int16() const { return Int16( num / den ); }
BigRat::operator Int32() const { return Int32( num / den ); }
BigRat::operator Int64() const { return Int64( num / den ); }

BigRat::operator Unsigned8 () const { return Unsigned8 ( num / den ); }
BigRat::operator Unsigned16() const { return Unsigned16( num / den ); }
BigRat::operator Unsigned32() const { return Unsigned32( num / den ); }
BigRat::operator Unsigned64() const { return Unsigned64( num / den ); }

BigRat::operator Float32() const { return Float32(num) / Float32(den); }
BigRat::operator Float64() const { return Float64(num) / Float64(den); }
BigRat::operator Float96() const { return Float96(num) / Float96(den); }

///
bool BigRat::operator==(const BigRat &b) const { return num==b.num and den==b.den; }
bool BigRat::operator!=(const BigRat &b) const { return num!=b.num or  den!=b.den; }
bool BigRat::operator< (const BigRat &b) const { BigInt i = num * b.den, j = b.num * den; return i <  j; }
bool BigRat::operator<=(const BigRat &b) const { BigInt i = num * b.den, j = b.num * den; return i <= j; }
bool BigRat::operator> (const BigRat &b) const { BigInt i = num * b.den, j = b.num * den; return i >  j; }
bool BigRat::operator>=(const BigRat &b) const { BigInt i = num * b.den, j = b.num * den; return i >= j; }

bool BigRat::operator>=(int b) const { return *this >= BigRat(b); }
bool BigRat::operator> (int b) const { return *this >  BigRat(b); }

bool BigRat::is_integer                () const { return den.is_equal_to_one(); }
bool BigRat::is_odd                    () const { return is_integer() and num.is_odd (); }
bool BigRat::is_even                   () const { return is_integer() and num.is_even(); }
bool BigRat::is_strictly_negative      () const { return num.is_strictly_negative(); }
bool BigRat::is_strictly_positive      () const { return num.is_strictly_positive(); }
bool BigRat::is_positive_or_null       () const { return num.is_positive_or_null (); }
bool BigRat::is_negative_or_null       () const { return num.is_negative_or_null (); }
bool BigRat::is_equal_to_zero          () const { return num.is_equal_to_zero    (); }
bool BigRat::is_equal_to_one           () const { return num.is_equal_to_one() and den.is_equal_to_one(); }
bool BigRat::is_equal_to_two           () const { return num.is_equal_to_two() and den.is_equal_to_one(); }
bool BigRat::is_equal_to_three         () const { return num.n == 0 and num.val ==  3 and den.is_equal_to_one(); }
bool BigRat::is_equal_to_minus_one     () const { return num.n == 0 and num.val == -1 and den.is_equal_to_one(); }
bool BigRat::is_equal_to_minus_two     () const { return num.n == 0 and num.val == -2 and den.is_equal_to_one(); }
bool BigRat::is_equal_to_one_half      () const { return num.is_equal_to_one() and den.is_equal_to_two(); }
bool BigRat::is_equal_to_minus_one_half() const { return num.n == 0 and num.val == -1 and den.is_equal_to_two(); }

void BigRat::write_to_stream( Stream &os ) const {
     num.write_to_stream( os );
     if ( den.n or den.val != 1 )
         den.write_to_stream( os << '/' );
}

bool is_always_strictly_positive( const BigRat &a ) { return a.num.is_strictly_positive(); }
bool is_always_positive_or_null ( const BigRat &a ) { return a.num.is_positive_or_null (); }
bool is_always_equal_to_one     ( const BigRat &a ) { return a.num.is_equal_to_one() and a.den.is_equal_to_one(); }
bool is_always_equal_to_zero    ( const BigRat &a ) { return a.num.is_equal_to_zero(); }

BigRat inv( const BigRat &a ) {
    if ( a.num.is_equal_to_zero() )
        return 0;
    if ( a.num.is_strictly_negative() )
        return BigRat( -a.den, -a.num );
    return BigRat( a.den, a.num );
}

// +
BigRat operator+( const BigRat &a, const BigRat &b ) { return BigRat( a.num * b.den + b.num * a.den, a.den * b.den ); }
BigRat operator+( const BigRat &a, Int32         b ) { return BigRat( a.num         + b     * a.den, a.den         ); }
BigRat operator+( Int32         a, const BigRat &b ) { return BigRat( a     * b.den + b.num        ,         b.den ); }
BigRat operator+( const BigRat &a, const BigInt &b ) { return BigRat( a.num         + b     * a.den, a.den         ); }
BigRat operator+( const BigInt &a, const BigRat &b ) { return BigRat( a     * b.den + b.num        ,         b.den ); }
Float32 operator+( const BigRat &a, Float32                      b ) { return Float32( a ) + b; }
Float32 operator+( Float32                      a, const BigRat &b ) { return a + Float32( b ); } 
Float64 operator+( const BigRat &a, Float64                      b ) { return Float64( a ) + b; }
Float64 operator+( Float64                      a, const BigRat &b ) { return a + Float64( b ); } 
Float96 operator+( const BigRat &a, Float96                     &b ) { return Float96( a ) + b; }
Float96 operator+( Float96      &a, const BigRat                &b ) { return a + Float96( b ); } 

// -
BigRat operator-( const BigRat &a, const BigRat &b ) { return BigRat( a.num * b.den - b.num * a.den, a.den * b.den ); }
BigRat operator-( const BigRat &a, Int32         b ) { return BigRat( a.num         - b     * a.den, a.den         ); }
BigRat operator-( Int32         a, const BigRat &b ) { return BigRat( a     * b.den - b.num        ,         b.den ); }
BigRat operator-( const BigRat &a, const BigInt &b ) { return BigRat( a.num         - b     * a.den, a.den         ); }
BigRat operator-( const BigInt &a, const BigRat &b ) { return BigRat( a     * b.den - b.num        ,         b.den ); }
Float32 operator-( const BigRat &a, Float32                      b ) { return Float32( a ) - b; }
Float32 operator-( Float32                      a, const BigRat &b ) { return a - Float32( b ); } 
Float64 operator-( const BigRat &a, Float64                      b ) { return Float64( a ) - b; }
Float64 operator-( Float64                      a, const BigRat &b ) { return a - Float64( b ); } 
Float96 operator-( const BigRat &a, Float96                     &b ) { return Float96( a ) - b; }
Float96 operator-( Float96      &a, const BigRat                &b ) { return a - Float96( b ); }

// *
BigRat operator*( const BigRat &a, const BigRat &b ) { return BigRat( a.num * b.num, a.den * b.den ); }
BigRat operator*( const BigRat &a, Int32         b ) { return BigRat( a.num * b, a.den ); }
BigRat operator*( Int32         a, const BigRat &b ) { return BigRat( a * b.num, b.den ); }
BigRat operator*( const BigRat &a, const BigInt &b ) { return BigRat( a.num * b, a.den ); }
BigRat operator*( const BigInt &a, const BigRat &b ) { return BigRat( a * b.num, b.den ); }
Float32 operator*( const BigRat &a, Float32                      b ) { return Float32( a ) * b; }
Float32 operator*( Float32                      a, const BigRat &b ) { return a * Float32( b ); } 
Float64 operator*( const BigRat &a, Float64                      b ) { return Float64( a ) * b; }
Float64 operator*( Float64                      a, const BigRat &b ) { return a * Float64( b ); }
Float96 operator*( const BigRat &a, Float96                     &b ) { return Float96( a ) * b; }
Float96 operator*( Float96      &a, const BigRat                &b ) { return a * Float96( b ); } 

// /
BigRat operator/( const BigRat &a, const BigRat &b ) { return BigRat( a.num * b.den, a.den * b.num ); }
BigRat operator/( const BigRat &a, Int32         b ) { return BigRat( a.num, a.den * b ); }
BigRat operator/( Int32         a, const BigRat &b ) { return BigRat( a * b.den, b.num ); }
BigRat operator/( const BigRat &a, const BigInt &b ) { return BigRat( a.num, a.den * b ); }
BigRat operator/( const BigInt &a, const BigRat &b ) { return BigRat( a * b.den, b.num ); }
Float32 operator/( const BigRat &a, Float32                      b ) { return Float32( a ) / b; }
Float32 operator/( Float32                      a, const BigRat &b ) { return a / Float32( b ); } 
Float64 operator/( const BigRat &a, Float64                      b ) { return Float64( a ) / b; }
Float64 operator/( Float64                      a, const BigRat &b ) { return a / Float64( b ); } 
Float96 operator/( const BigRat &a, Float96                     &b ) { return Float96( a ) / b; }
Float96 operator/( Float96      &a, const BigRat                &b ) { return a / Float96( b ); }

// %
BigRat operator%( const BigRat &a, const BigRat &b ) {
    return BigRat( ( a.num * b.den ) % ( b.num * a.den ), a.den * b.den );
}


BigRat abs( const BigRat &a ) {
    return BigRat( BigRat::NoCan(), abs( a.num ), a.den );
}

BigRat mod( const BigRat &a, const BigRat &b ) {
    if ( a.is_integer() and b.is_integer() )
        return a.num % b.num;
    BigRat res = a;
    ASSERT( 0, "TODO" );
    return res;
}

BigRat floor(const BigRat &a) { /// hum
    return Int64( floor( double( a ) ) );
}

BigRat ceil (const BigRat &a) { /// hum
    return Int64( ceil( double( a ) ) );
}


} // namespace Metil
