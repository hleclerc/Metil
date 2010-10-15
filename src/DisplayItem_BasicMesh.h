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
    virtual void update_p_min_p_max( GenericDisplay *display, T3 &p_min, T3 &p_max, bool use_trans );

    unsigned *get_elem_count_gpu_ptr( ST nb_types, int sb );
    int *get_elem_data_gpu_ptr( ST needed_size );

protected:
     Ps<BasicMesh_Compacted> mesh;

     ST size_elem_data;
     int *elem_data_gpu;

     ST size_elem_count;
     unsigned *elem_count_gpu;
};

END_METIL_NAMESPACE;

#endif // DISPLAYITEM_BASICMESH_H
