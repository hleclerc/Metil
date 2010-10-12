#ifndef DISPLAYITEM_BASICMESH_H
#define DISPLAYITEM_BASICMESH_H

#include "DisplayItem.h"
#include "BasicMesh_Compacted.h"

BEG_METIL_NAMESPACE;

/**
*/
class DisplayItem_BasicMesh : public DisplayItem {
public:
    DisplayItem_BasicMesh( Ps<BasicMesh_Compacted> mesh );

    virtual void render_to( BitmapDisplay *display );
    virtual void render_to( VectorDisplay *display );

protected:
     Ps<BasicMesh_Compacted> mesh;
};

END_METIL_NAMESPACE;

#endif // DISPLAYITEM_BASICMESH_H
