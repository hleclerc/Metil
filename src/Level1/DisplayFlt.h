#ifndef BASICBASENFLTNUMBER_H
#define BASICBASENFLTNUMBER_H

#include "String.h"

#ifdef DOXYGEN
namespace Level1 {
#else
BEG_METIL_LEVEL1_NAMESPACE
#endif

/// used to display floating point number
template<int base,int nb_digits>
struct BasicBaseNFltNumber {
    static const int size = nb_digits + 2;

    BasicBaseNFltNumber() {
        for(int i=0;i<size;++i)
            data[ i ] = 0;
        expo_base = 0;
    }

    BasicBaseNFltNumber( char v ) {
        data[ 0 ] = v;
        for(int i=1;i<size;++i)
            data[ i ] = 0;
        expo_base = 0;
    }

    void mul_by_2(){
        int a = 0;
        for(int i=size-1;i>=0;--i) {
            a += data[ i ] * 2;
            data[ i ] = a % base;
            a /= base;
        }
        if ( a ) {
            for(int i=size-2;i>=0;--i)
                data[ i + 1 ] = data[ i ];
            data[ 0 ] = a;
            ++expo_base;
        }
    }

    void div_by_2(){
        int a = 0;
        for(int i=0;i<size;++i) {
            a += data[ i ];
            data[ i ] = a / 2;
            a = ( a & 1 ) * base;
        }
        if ( not data[ 0 ] ) {
            for(int i=1;i<size;++i)
                data[ i - 1 ] = data[ i ];
            data[ size - 1 ] = a / 2;
            --expo_base;
        }
    }

    void div_by_2_denorm() {
        for(int i=0,a=0;i<size;++i) {
            a += data[ i ];
            data[ i ] = a / 2;
            a = ( a & 1 ) * base;
        }
    }

    void operator+=( const BasicBaseNFltNumber &v ) {
        int a = 0;
        for(int i=size-1;i>=0;--i) {
            int vs = i + v.expo_base - expo_base;
            a += data[ i ] + ( vs >= 0 and vs < size ? v.data[ vs ] : 0 );
            data[ i ] = a % base;
            a /= base;
        }
        if ( a ) {
            for(int i=size-1;i>0;--i)
                data[ i ] = data[ i - 1 ];
            data[ 0 ] = a;
            ++expo_base;
        }
    }

    void round_up() {
        int a = 5;
        for( int i = size - 2; i >= 0; --i ) {
            a += data[ i ];
            data[ i ] = a % base;
            a /= base;
        }
        if ( a ) {
            for( int i = size - 1; i > 0; --i )
                data[ i ] = data[ i - 1 ];
            data[ 0 ] = a;
            ++expo_base;
        }
    }

    void write_str( String &os ) const {
        NewString res( nb_digits + 1 );
        char *str = res.ptr();
        str[ 0 ] = '0' + data[ 0 ];
        str[ 1 ] = '.';
        for(int j = 1, c = 2; j < nb_digits; ++j, ++c )
            str[ c ] = '0' + data[ j ];
        //
        os << String( res );
        if ( expo_base )
            os << 'e'  << expo_base;
    }

    int expo_base;
    char data[ size ];
};

template<int len_mant, int len_expo, int off_mant, int off_sign, int off_expo, int bia_expo>
struct DisplayFlt {
    static void display( String &os, const PI8 *v ) {
        const int nb_digits = 8; // ( len_mant + 2 ) / 3;

        // get expo
        int expo = bia_expo;
        for(int n=0,d=off_expo,c=1;n<len_expo;++n,++d,c*=2)
            if ( v[ d / 8 ] & ( 1 << d % 8 ) )
                expo += c;
        bool z = ( expo == bia_expo );

        // get 2^expo
        BasicBaseNFltNumber<10,nb_digits> coef( 1 );
        for( ; expo > 0; --expo ) coef.mul_by_2();
        for( ; expo < 0; ++expo ) coef.div_by_2();

        // c^i * 2^(expo-i)
        BasicBaseNFltNumber<10,nb_digits> res( coef );
        for(int n=len_mant,d=off_mant+len_mant-1;n>0;--n,--d) {
            coef.div_by_2_denorm();
            if ( v[ d / 8 ] & ( 1 << d % 8 ) ) {
                res += coef;
                z = 0;
            }
        }

        // display sign
        if ( v[ off_sign / 8 ] & ( 1 << off_sign % 8 ) ) // sign
            os << '-';

        // -> 0 in floating point representation
        if ( z ) {
            os << '0';
        } else {
            // round
            if ( res.data[ nb_digits ] > 5 )
                res.round_up();

            // display
            os << res;
        }
    }
};


END_METIL_LEVEL1_NAMESPACE

#endif // BASICBASENFLTNUMBER_H
