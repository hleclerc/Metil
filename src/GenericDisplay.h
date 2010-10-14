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

    GenericDisplay &operator<<( DisplayItem *item ); ///< item will be owned by this

    //    template<class T>
    //    GenericDisplay &operator<<( T &val ) { ///< we assume that val will exist until this will be destroyed
    //        return operator<<( val.NEW_DisplayItem() );
    //    }

    void set_O( T Ox, T Oy, T Oz );
    void set_X( T Xx, T Xy, T Xz );
    void set_Y( T Yx, T Yy, T Yz );
    void set_d( T d );
    void set_a( T a );

    int get_w() const;
    int get_h() const;
    void set_w( int w );
    void set_h( int h );

    DisplayTrans *get_trans_gpu();
    void update_p_min_p_max();

    T3 p_min; ///< after projection
    T3 p_max; ///< after projection
protected:
    int w, h;
    BasicVec<DisplayItem *> items;

    bool trans_has_changed;
    DisplayTrans trans_cpu;
    DisplayTrans *trans_gpu;
};

END_METIL_NAMESPACE;

#endif // GENERICDISPLAY_H
