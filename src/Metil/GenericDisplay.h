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
    typedef int I;
    typedef BasicVec<T,3> T3;

    GenericDisplay( int w = 400, int h = 400 );
    ~GenericDisplay();

    GenericDisplay &operator<<( DisplayItem *item ); ///< item won't be owned by this
    virtual void render() = 0;

    void set_O( T Ox, T Oy, T Oz );
    void set_X( T Xx, T Xy, T Xz );
    void set_Y( T Yx, T Yy, T Yz );

    void set_O( T3 O );
    void set_X( T3 X );
    void set_Y( T3 Y );
    void set_d( T  d ); ///< viewable diameter
    void set_a( T  a ); ///< perspective angle (degree)
    void set_w( I  w );
    void set_h( I  h );

    T3 get_O() const;
    T3 get_X() const;
    T3 get_Y() const;
    T  get_d() const;
    T  get_a() const;
    I  get_w() const;
    I  get_h() const;

    void fit   (); ///< change O and zoom factor to view all the parts in the screen
    void zoom  ( T c, T x, T y ); ///< c is the coeff, x and y are in screen coordinates
    void pan   ( T x, T y ); ///< x and y are in screen coordinates
    void shrink( T v ); ///< shrink polygons of +/- v var_inter
    void rotate( T x, T y, T z ); ///< around C
    void rotate( T3 V ); ///< around C

    void get_trans_data( struct String &res, const struct String &name );

    void get_min_max_real( T3 &mi, T3 &ma ); ///< min and max in world coordinates
    void get_min_max_view( T3 &mi, T3 &ma ); ///< min and max in world coordinates

    DisplayTrans trans; ///< operator to transform real -> screen coordinates
    T3 C; ///< center of rotation
protected:
    int w, h;
    bool trans_has_changed;
    bool C_has_been_defined; ///< if center of rotation has alread been defined
    BasicVec<DisplayItem *> items;
};

END_METIL_NAMESPACE;

#endif // GENERICDISPLAY_H
