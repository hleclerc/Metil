#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplay.h"
#include "BasicMesh.h"
#include "CudaMetil.h"

using namespace Metil;

int main() {
    //    cudaSetDevice( 1 );
    BasicMesh mesh;
    mesh.load_vtu( "/home/leclerc/Data/resultat_0_0.vtu" );
    // mesh.make_rect( elem_type_Triangle, BasicVec<float>( 0.5, 0.5, 0 ), BasicVec<float>( 2, 2, 0 ), BasicVec<int>( 20, 20 ) );
    PRINT( mesh.nb_nodes() );
    PRINT( mesh.nb_elements() );

    // display
    const MachineId *machine_id = MachineId::cpu( 0 )->gpu( 0 );
    Ps<BasicMesh_Compacted> compacted_mesh = make_cs( &mesh, 1, machine_id );

    //
    BitmapDisplay display( 800, 600 );

    DisplayItem_BasicMesh disp_item( compacted_mesh );
    // disp_item.set_coloring_field( 1, -1.4, 1.1, 0 );
    display << &disp_item;

    // display.set_X( 0.707, 0.0, -0.707 );
    display.set_Y( 0.0, 0.707, -0.707 );
    display.fit();
    display.set_d( 0.5 * display.get_d() );
    display.render();
    display.copy_gpu_to_cpu();
    display.save_png( "toto.png" );
}
