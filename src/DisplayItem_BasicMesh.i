%{
    #include "DisplayItem_BasicMesh.h"
%}

%include "DisplayItem.i"
%include "BasicMesh_Compacted.i"

namespace Metil {
    class DisplayItem_BasicMesh : public DisplayItem {
    public:
        DisplayItem_BasicMesh( Ps<BasicMesh_Compacted> mesh );

        virtual void render_to( BitmapDisplay *display );
        virtual void render_to( VectorDisplay *display );
        // virtual void update_p_min_p_max( GenericDisplay *display, T3 &p_min, T3 &p_max );
    };
}
