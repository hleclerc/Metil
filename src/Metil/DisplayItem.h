#ifndef DISPLAYITEM_H
#define DISPLAYITEM_H

#include "DisplayTrans.h"

BEG_METIL_NAMESPACE;

class GenericDisplay;
class BitmapDisplay;
class VectorDisplay;

class DisplayItem {
public:
    typedef BasicVec<float,3> T3;

    virtual void update_min_max( T3 &mi, T3 &ma, const DisplayTrans::Buf &trans_buf ) const = 0;
    virtual void update_min_max( T3 &mi, T3 &ma ) const = 0;
    virtual void render_to( BitmapDisplay *display ) = 0;
    virtual void render_to( VectorDisplay *display ) = 0;

    virtual void shrink( float v ) {} ///< add v to polygon shrink
};

END_METIL_NAMESPACE;

#endif // DISPLAYITEM_H
