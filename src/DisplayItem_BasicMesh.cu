#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplay.h"

BEG_METIL_NAMESPACE;

DisplayItem_BasicMesh::DisplayItem_BasicMesh( Ps<BasicMesh_Compacted> mesh ) : mesh( mesh ) {
}

__global__
void DisplayItem_BasicMesh_render_kernel( unsigned *img, int w, int h, const BasicMesh_Compacted *mesh ) {
    for( int y = 0; y < h; ++y )
        for( int x = 0; x < w; ++x )
            img[ y * w + x ] = 0xFF000000; // + ( y * 255 / h );

    const BasicVecRef<float> &x = mesh->pos_nodes[ 0 ];
    const BasicVecRef<float> &y = mesh->pos_nodes[ 1 ];
    const BasicVecRef<float> &z = mesh->pos_nodes[ 2 ];
    for( int i = 0; i < x.size(); ++i ) {
        img[ int( y[ i ] ) * w + int( x[ i ] ) ] = 0xFFFFFFFF;
    }
}


void DisplayItem_BasicMesh::render_to( BitmapDisplay *display ) {
    ASSERT( mesh.pos.is_a_gpu(), "render works only with data on gpu" );
    DisplayItem_BasicMesh_render_kernel<<<1,1>>>( display->get_img_gpu_ptr(), display->get_w(), display->get_h(), mesh.ptr() );
}

void DisplayItem_BasicMesh::render_to( VectorDisplay * ) {
    // fill elem_count
    unsigned *elem_count = get_elem_count_GPU_ptr( mesh.nb_types() );
    int size_for_1t = ( NB_BLOCKS_FOR_ELEM_COUNT + 1 ) * sb() + 1;
    Display::Trans *trans = get_trans_GPU_ptr();
    CSC(( make_elem_count_kernel<<<NB_BLOCKS_FOR_ELEM_COUNT,128>>>( elem_count, trans, wb(), hb(), sb(), w, h, m ) ));
}

END_METIL_NAMESPACE;
