#ifndef GENERICDISPLAY_H
#define GENERICDISPLAY_H

#include "DisplayTrans.h"
#include "DisplayItem.h"
#include "BasicVec.h"

BEG_METIL_NAMESPACE;

/**
*/
class GenericDisplay {
public:
    typedef float T;
    typedef BasicVec<T,3> T3;

    GenericDisplay( int w = 400, int h = 400 );
    ~GenericDisplay();

    GenericDisplay &operator<<( DisplayItem *item ); ///< item won't be owned by this

    void set_O( T Ox, T Oy, T Oz );
    void set_X( T Xx, T Xy, T Xz );
    void set_Y( T Yx, T Yy, T Yz );
    void rotate( T x, T y, T z );

    void set_O( T3 O );
    void set_X( T3 X );
    void set_Y( T3 Y );
    void rotate( T3 V );
    void zoom( T c, T x, T y ); ///< c is the coeff, x and y are in screen coordinates

    void set_d( T d ); ///< viewable diameter
    void set_a( T a ); ///< perspective angle (degree)

    T3 get_O() const;
    T3 get_X() const;
    T3 get_Y() const;
    T get_d() const;
    T get_a() const;

    int get_w() const;
    int get_h() const;
    void set_w( int w );
    void set_h( int h );
    void get_trans_data( struct String &res, const struct String &name );

    DisplayTrans *get_trans_gpu();
    void update_p_min_p_max( bool use_trans = true );
    void fit();

    T3 p_min; ///< after projection
    T3 p_max; ///< after projection
    T3 C; ///< center of rotation
protected:
    int w, h;
    bool C_has_been_defined;
    BasicVec<DisplayItem *> items;

    bool trans_has_changed;
    DisplayTrans trans_cpu;
    DisplayTrans *trans_gpu;
};

END_METIL_NAMESPACE;

#endif // GENERICDISPLAY_H
