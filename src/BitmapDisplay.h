#ifndef BitmapDisplay_H
#define BitmapDisplay_H

#include "GenericDisplay.h"
#include "BasicVecGpu.h"
#include "MetilString.h"
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
    typedef unsigned U;

    BitmapDisplay( int w = 400, int h = 400 );
    virtual void render();

    Ps<char> make_png( const char *prelim = 0, ST prelim_size = 0 ); ///< return a pointer on png data
    void save_png( const String &filename ); ///< make and save png to a file
    void save_png_in_sock( int socket_id, const char *name ); ///< make and save png to a file
    bool get_and_update_first_item(); ///< return true if rendering first item in the img and set first item to 0
    U get_elem_number( int x, int y ) const; ///< at the position x, y
    void get_img_rgba( U *bits ) const;

    U *get_img_rgba_ptr();
    T *get_img_zznv_ptr();
    I *get_img_nnnn_ptr();

protected:
    BasicVecGpu<U> img_rgba; ///<
    BasicVecGpu<T> img_zznv; ///<
    BasicVecGpu<I> img_nnnn; ///<
    bool _first_item;
};

END_METIL_NAMESPACE;

#endif // BitmapDisplay_H
