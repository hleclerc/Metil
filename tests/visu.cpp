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
    BitmapDisplay display;
    display << new DisplayItem_BasicMesh( compacted_mesh );

    display.fit();
    display.render();
    display.copy_gpu_to_cpu();
    display.save_png( "toto.png" );
}
