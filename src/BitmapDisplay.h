#ifndef BitmapDisplay_H
#define BitmapDisplay_H

#include "GenericDisplay.h"
#include "String.h"
#include "Ps.h"

BEG_METIL_NAMESPACE;

/**
  Create a bitmap image from a DisplayItem list

  The resulting image will contain r(8)g(8)b(8)a(8), z(16)dot(n,z)(8)val(8), num_elem(32)

\code
    BasicMesh mesh;
    mesh.make_rect( elem_type_Triangle, BasicVec<float>( 0, 0, 0 ), BasicVec<float>( 1, 1, 0 ), BasicVec<int>( 2, 2 ) );
    // PRINT( mesh.nb_nodes() );

    // display
    const MachineId *machine_id = MachineId::cpu( 0 )->gpu( 0 );
    Ps<BasicMesh_Compacted> compacted_mesh = make_cs( &mesh, 1, machine_id );

    //
    BitmapDisplay display;
    display.fit();
    display.render();
    display.copy_gpu_to_cpu();
    display.save_png( "toto.png" );
\endcode

*/
class BitmapDisplay : public GenericDisplay {
public:
    typedef BasicVec<float,3> T3;

    struct Img {
        Img( BitmapDisplay *d ) : cpu( 0 ), gpu( 0 ), d( d ) {}
        unsigned *get_cpu_ptr();
        unsigned *get_gpu_ptr();
        void copy_gpu_to_cpu();
        ST rese();

        unsigned *cpu;
        unsigned *gpu;
        BitmapDisplay *d;
    };

    BitmapDisplay( int w = 400, int h = 400 );

    void render();
    void copy_gpu_to_cpu(); ///< after render()
    Ps<char> make_png( const char *prelim = 0, ST prelim_size = 0 ); ///< after copy_gpu_to_cpu()
    void save_png( const String &filename ); ///< make and save png to a file
    void save_png_in_sock( int socket_id, const char *name ); ///< make and save png to a file
    bool first_item(); ///< return true if rendering first item in the img and set first item to 0

    Img img_rgba; ///<
    Img img_zznv; ///<
    Img img_nnnn; ///<
protected:
    bool first_item_; ///<
    float rz_min_max[ 2 ]; ///<
};

END_METIL_NAMESPACE;

#endif // BitmapDisplay_H
