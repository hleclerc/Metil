#ifndef BASICBASENINTNUMBER_H
#define BASICBASENINTNUMBER_H

#include "../MetilString.h"

BEG_METIL_LEVEL1_NAMESPACE

template<int base,int nb_digits>
struct BasicBaseNIntNumber {
    BasicBaseNIntNumber() {
        for(int i=0;i<nb_digits;++i)
            data[ i ] = 0;
    }

    BasicBaseNIntNumber( char v ) {
        data[ nb_digits - 1 ] = v;
        for(int i=nb_digits-2;i>=0;--i)
            data[ i ] = 0;
    }

    void mul_by_inf_base( char v ){
        for(int i=nb_digits-1,a=0;i>=0;--i) {
            a += data[ i ] * v;
            data[ i ] = a % base;
            a /= base;
        }
    }

    void operator+=( const BasicBaseNIntNumber &v ) {
        for(int i=nb_digits-1,a=0;i>=0;--i) {
            a += data[ i ] + v.data[ i ];
            data[ i ] = a % base;
            a /= base;
        }
    }

    void write_str( String &os ) const {
        for(int i=0;;++i) {
            if ( i == nb_digits ) {
                os << '0';
                break;
            }
            if ( data[ i ] != 0 ) {
                ST len = nb_digits - i;
                NewString res( len );
                char *str = res.ptr();
                for(int j=i,c=0;j<nb_digits;++j,++c)
                    str[ c ] = '0' + data[ j ];
                //
                os << String( res );
                break;
            }
        }
    }

    SI8 data[ nb_digits ];
};


template<int nb_bits,int base>
struct Coef_B {
    static const int nb_digits = ( nb_bits + 2 ) / 3;
    typedef BasicBaseNIntNumber<base,nb_digits> B;

    Coef_B() {
        data[ 0 ] = 1;
        for(int i=1;i<nb_bits;++i) {
            data[ i ] = data[ i - 1 ];
            data[ i ].mul_by_inf_base( 2 );
        }
    }

    B data[ nb_bits > 0 ? nb_bits : 1 ];
};

template<int len_mant, int len_sign, int off_mant, int off_sign>
struct DisplayInt {
    static void display( String &os, const PI8 *v, char sgn_if_nz = 0 ) {
        // 1 2 4 8 16 ...
        typedef Coef_B<len_mant,10> C;
        static C c;

        // base conversion ( \sum b_i * 2^i )
        typename C::B base_10;
        if ( len_sign and ( v[ off_sign / 8 ] & ( 1 << off_sign % 8 ) ) ) { // < 0 ?
            base_10.data[ C::nb_digits - 1 ] = 1;
            for(int n=0,d=off_mant;n<len_mant;++n,++d)
                if ( not ( v[ d / 8 ] & ( 1 << d % 8 ) ) )
                    base_10 += c.data[ n ];
            os << '-';
        } else { // >= 0
            bool nz = 0;
            for(int n=0,d=off_mant;n<len_mant;++n,++d) {
                if ( v[ d / 8 ] & ( 1 << d % 8 ) ) {
                    base_10 += c.data[ n ];
                    nz = 1;
                }
            }
            if ( sgn_if_nz and nz )
                os << sgn_if_nz;
        }

        // display
        os << base_10;
    }
};


END_METIL_LEVEL1_NAMESPACE

#endif // BASICBASENINTNUMBER_H
