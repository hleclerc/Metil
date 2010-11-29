#ifndef DISPLAYTRANS_H
#define DISPLAYTRANS_H

#include "MathBasicVec.h"

BEG_METIL_NAMESPACE;

/**
  Transformation 3D -> 2D for viewing purposes
*/
struct DisplayTrans {
    typedef float T;
    typedef int I;
    typedef Metil::BasicVec<T,3> T3;

    struct Buf {
        __inline__ T3 proj( T x, T y, T z ) const {
            x -= O[ 0 ];
            y -= O[ 1 ];
            z -= O[ 2 ];
            T3 res;
            res[ 0 ] = x * X[ 0 ] + y * X[ 1 ] + z * X[ 2 ];
            res[ 1 ] = x * Y[ 0 ] + y * Y[ 1 ] + z * Y[ 2 ];
            res[ 2 ] = x * Z[ 0 ] + y * Z[ 1 ] + z * Z[ 2 ];
            float m = 1 / ( 1 + p * res[ 2 ] );
            res[ 0 ] = res[ 0 ] * m + wd2;
            res[ 1 ] = res[ 1 ] * m + hd2;
            return res;
        }
        __inline__ T3 proj( const T3 &P ) const {
            return proj( P[ 0 ], P[ 1 ], P[ 2 ] );
        }
        __inline__ T3 eye_dir( T x, T y ) {
            return normalized( x * p * X + y * p * Y + Z );
        }
        T3 O; ///<
        T3 X; ///<
        T3 Y; ///<
        T3 Z; ///<
        T  p; ///<
        I  wd2, hd2;
    };

    DisplayTrans() {
        O = T3( 0, 0, 0 );
        X = T3( 1, 0, 0 );
        Y = T3( 0, 1, 0 );
        a = 20;
        d = 1;
    }

    __inline__ Buf make_buf( int w, int h ) const {
        T mwh = Metil::min( w, h );
        //
        Buf res;
        res.O = O;
        res.X = Metil::normalized( X ) * mwh / d;
        res.Y = Metil::normalized( Y ) * mwh / d;
        res.Z = Metil::normalized( cross( Y, X ) ) * mwh / d;
        res.p = Metil::tan( a * 3.14159265358979323846 / 180 ) / mwh;
        res.wd2 = w / 2;
        res.hd2 = h / 2;
        return res;
    }

    __inline__ T3 s_to_w_vec( const T3 &V ) { ///< screen to world vector
        T3 Z = cross( Y, X );
        return T3(
            V[ 0 ] * X[ 0 ] + V[ 1 ] * Y[ 0 ] + V[ 2 ] * Z[ 0 ],
            V[ 0 ] * X[ 1 ] + V[ 1 ] * Y[ 1 ] + V[ 2 ] * Z[ 1 ],
            V[ 0 ] * X[ 2 ] + V[ 1 ] * Y[ 2 ] + V[ 2 ] * Z[ 2 ]
        );
    }

    __inline__ void rotate_s( const T3 &V, const T3 &C ) { ///< rotate, with v in screen coordinates
        T3 R = s_to_w_vec( V );
        X = rot( X, R );
        Y = rot( Y, R );
        O = C + rot( O - C, R );
    }

    T3 O; ///< position of center of the screen in the real world
    T3 X; ///< normalized axis
    T3 Y; ///< normalized axis
    T  d; ///< diameter of the viewed sphere centered in O in the real world.
    T  a; ///< perspective angle (according to min(w,h)). 0 means no perspective
};

END_METIL_NAMESPACE;


#endif // DISPLAYTRANS_H
