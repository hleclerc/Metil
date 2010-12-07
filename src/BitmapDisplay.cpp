#include "Level1/StringHelp.h"
#include "BitmapDisplay.h"
#include "CudaMetil.h"
#include "Base64.h"
#include "Png.h"

#include <limits>
#include <sys/socket.h>

BEG_METIL_NAMESPACE;

BitmapDisplay::BitmapDisplay( int w, int h ) : GenericDisplay( w, h ) {
}

void BitmapDisplay::render() {
    _first_item = false;
    for( ST i = 0; i < items.size(); ++i )
        items[ i ]->render_to( this );
}

bool BitmapDisplay::get_and_update_first_item() {
    bool res = _first_item;
    _first_item = false;
    return res;
}

Ps<char> BitmapDisplay::make_png( const char *prelim, ST prelim_size ) {
    BasicVec<U> tmp; img_rgba.copy_to( tmp );
    return Metil::make_png( (unsigned char *)tmp.ptr(), w, h, false, prelim, prelim_size );
}

void BitmapDisplay::save_png( const String &filename ) {
    Ps<char> data = make_png();
    File os( filename, "w" );
    os.write( data.data, data.size );
    data.free();
}

void BitmapDisplay::save_png_in_sock( int socket_id, const char *name ) {
    TODO;
    //    Socket res( socket_id );
    //    Ps<char> data;

    //    //
    //    //res << name << ".z_min = " << p_min[ 2 ] << ";\n";
    //    //res << name << ".z_max = " << p_max[ 2 ] << ";\n";
    //    get_trans_data( res, String( name ) + ".RP" );
    //    get_trans_data( res, String( name ) + ".IP" );

    //
    #define DISP_IMG( N ) \
        data = Metil::make_png( (unsigned char *)N.get_cpu_ptr(), w, h ); \
           res << name << "." #N ".src = 'data:image/png;base64,"; \
           base_64_encode( res, data.data, data.size ); \
           res << "';\n"; \
           data.free()

    //    DISP_IMG( img_zznv );
    //    DISP_IMG( img_nnnn );
    //    DISP_IMG( img_rgba );

    #undef DISP_IMG
}

BitmapDisplay::U BitmapDisplay::get_elem_number( int x, int y ) const {
    return img_nnnn[ w * x + y ];
}

void BitmapDisplay::get_img_rgba( U *bits ) const {
    cudaMemcpy( bits, img_rgba.ptr(), sizeof( unsigned ) * img_rgba.rese, cudaMemcpyDeviceToHost );
}

// <<<<<<< HEAD:src/BitmapDisplay.cpp
// unsigned *BitmapDisplay::Img::get_gpu_ptr() {
//     if ( rese_gpu != rese() ) {
//         if ( gpu )
//             CSC(( cudaFree( gpu ) ));
//         gpu = 0;
//     }
//     if ( not gpu ) {
//         rese_gpu = rese();
// <<<<<<< HEAD:src/BitmapDisplay.cpp
//         cudaMalloc( &gpu, rese_gpu );
// =======
//         CSC(( cudaMalloc( &gpu, rese_gpu ) ));
// >>>>>>> 425c737172cae11916a779b502574027b6d6a926:src/BitmapDisplay.cpp
//     }
//     return gpu;
// =======
// BitmapDisplay::U *BitmapDisplay::get_img_rgba_ptr() {
//     img_rgba.reserve_without_copy( w * h );
//     return img_rgba.ptr();
// >>>>>>> 08ba0ff894d144e4e37115e835c5e9cb219a29a6:src/BitmapDisplay.cpp
// }

BitmapDisplay::T *BitmapDisplay::get_img_zznv_ptr() {
    img_zznv.reserve_without_copy( w * h );
    return img_zznv.ptr();
}

BitmapDisplay::I *BitmapDisplay::get_img_nnnn_ptr() {
    img_nnnn.reserve_without_copy( w * h );
    return img_nnnn.ptr();
}

END_METIL_NAMESPACE;
