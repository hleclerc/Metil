#include "DisplayItem_BasicMesh.h"
#include "BitmapDisplay.h"
#include "BasicMesh.h"
#include "CudaMetil.h"

using namespace Metil;

int main() {
    // Array<String> a( 2 );
    // PRINT( a.size() );
    cudaSetDevice( 1 );

    // user
    BasicMesh mesh;
    mesh.add_node(  0,  0, 0 );
    mesh.add_node( 10,  0, 0 );
    mesh.add_node(  0, 10, 0 );

    mesh.add_elem( elem_type_Triangle, 0, 1, 2 );
    mesh.elem_groups[ 0 ].pos_nodes.resize( 3 );
    mesh.elem_groups[ 0 ].pos_nodes[ 0 ] << 666;

    Ps<BasicMesh_Compacted> m = make_cs( &mesh, 1, MachineId::cpu( 0 ) );
    Ps<BasicMesh_Compacted> g = strdup( m, MachineId::gpu( 0 ) );
    memcpy( m, g );

    PRINT( m->pos_nodes.size() );
    PRINT( m->pos_nodes[ 0 ].size() );
    PRINT( m->pos_nodes[ 0 ][ 1 ] );
    PRINT( m->elem_groups[ 0 ].pos_nodes );

    // compacted version
//    Ps<BasicMesh_Compacted> m = make_cs( &mesh, 1, MachineId::gpu( 0 ) );

//    // display
//    BitmapDisplay display;
//    display << NEW( DisplayItem_BasicMesh, m );

//    display.set_d( 50 );
//    display.set_O( 5, 5, 0 );

//    display.render();
//    display.copy_gpu_to_cpu();
//    display.save_png( "test.png" );
//    String a("123456");
//    PRINT( a.begins_by( "12" ) );
//    PRINT( a.begins_by( "13" ) );
//    PRINT( a.ends_with( "46" ) );
//    PRINT( a.ends_with( "56" ) );
}
