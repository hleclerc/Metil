#ifndef DISPLAYITEM_H
#define DISPLAYITEM_H

#include "BasicVec.h"

BEG_METIL_NAMESPACE;

class GenericDisplay;
class BitmapDisplay;
class VectorDisplay;

class DisplayItem {
public:
    typedef BasicVec<float,3> T3;

    virtual void update_p_min_p_max( GenericDisplay *display, T3 &p_min, T3 &p_max, bool use_trans ) = 0;
    virtual void render_to( BitmapDisplay *display ) = 0;
    virtual void render_to( VectorDisplay *display ) = 0;

    virtual void shrink( float v ) {} ///< add v to polygon shrink
};

END_METIL_NAMESPACE;

#endif // DISPLAYITEM_H
