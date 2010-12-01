#include <QtGui/QApplication>

#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplayWidget.h"
#include "BasicMesh.h"
#include "CudaMetil.h"

using namespace Metil;

int main( int argc, char **argv ) {
    cudaSetDevice( 1 );

    // mesh
    BasicMesh mesh;
    mesh.load_vtu( "/home/leclerc/Data/resultat_0_0.vtu" );
    // mesh.make_rect( elem_type_Triangle, BasicVec<float>( 0, 0, 0 ), BasicVec<float>( 1, 1, 0 ), BasicVec<int>( 40, 40 ) );

    // disp_item
    const MachineId *machine_id = MachineId::cpu( 0 )->gpu( 0 );
    Ps<BasicMesh_Compacted> compacted_mesh = make_cs( &mesh, 1, machine_id );
    DisplayItem_BasicMesh disp_item( compacted_mesh );
    disp_item.set_coloring_field( 1, 1, 0, 6, 0 );

    // display
    BitmapDisplay display( 800, 600 );
    display << &disp_item;
    display.fit();
    display.rotate( -0.4, 0, 0 );
    // display.set_Y( 0.0, 0.707, -0.707 );
    display.set_d( 0.8 * display.get_d() );
    display.render();
    display.copy_gpu_to_cpu();
    display.save_png( "toto.png" );

    // QApplication a( argc, argv );
    //    BitmapDisplayWidget widget( 800, 600 );
    //    // disp_item.set_coloring_field( 1, -1.4, 1.1, 0 );
    //    widget.display << &disp_item;
    //    widget.display.fit();
    //    widget.display.set_Y( 0.0, 0.707, -0.707 );
    //    widget.display.set_d( 0.5 * widget.display.get_d() );

    //    widget.show();
    //    return a.exec();
}
