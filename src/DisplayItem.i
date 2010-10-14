%{
    #include "DisplayItem.h"
%}

%include "TypeConfig.i"

namespace Metil {
    class GenericDisplay;
    class BitmapDisplay;
    class VectorDisplay;

    class DisplayItem {
    public:
    virtual void render_to( BitmapDisplay *display ) = 0;
    virtual void render_to( VectorDisplay *display ) = 0;
    };
}

