#ifndef DISPLAYITEM_H
#define DISPLAYITEM_H

#include "Config.h"

BEG_METIL_NAMESPACE;

class BitmapDisplay;
class VectorDisplay;

class DisplayItem {
public:
    virtual void render_to( BitmapDisplay *display ) = 0;
    virtual void render_to( VectorDisplay *display ) = 0;
};

END_METIL_NAMESPACE;

#endif // DISPLAYITEM_H
