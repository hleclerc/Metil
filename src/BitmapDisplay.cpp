#include "BitmapDisplay.h"
#include "StringHelp.h"
#include "CudaMetil.h"
#include "Base64.h"
#include "Png.h"

#include <sys/socket.h>

BEG_METIL_NAMESPACE;

BitmapDisplay::BitmapDisplay( int w, int h ) : GenericDisplay( w, h ) {
    img_cpu = 0;
    img_gpu = 0;
}

void BitmapDisplay::render() {
    update_p_min_p_max();
    DOUT( p_min[2] );
    DOUT( p_max[2] );
    //
    first_item_ = true;
    for( ST i = 0; i < items.size(); ++i )
        items[ i ]->render_to( this );
}

bool BitmapDisplay::first_item() {
    bool res = first_item_;
    first_item_ = false;
    return res;
}

Ps<char> BitmapDisplay::make_png( const char *prelim, ST prelim_size ) {
    return Metil::make_png( get_img_cpu_ptr(), w, h, prelim, prelim_size );
}

void BitmapDisplay::save_png( const String &filename ) {
    Ps<char> data = make_png();
    File os( filename, "w" );
    os.write( data.data, data.size );
    data.free();
}

void BitmapDisplay::write_to_sockect( int socket_id, const char *txt ) {
    send( socket_id, txt, Level1::strlen( txt ), 0 );
}

void BitmapDisplay::save_png_in_sock( int socket_id, const char *name ) {
    String res;
    res << name << " = 'data:image/png;base64,";

    Ps<char> data = make_png();
    to_base_64( res, data.data, data.size );
    data.free();

    res << "';\n";
    PRINT( res );
    send( socket_id, res.c_str(), ST( res.size() ), 0 );
}

ST BitmapDisplay::nb_lines() {
    return nb_img * h + 1;
}

ST BitmapDisplay::rese_img() {
    return sizeof( unsigned ) * w * nb_lines();
}

void BitmapDisplay::copy_gpu_to_cpu() {
    cudaMemcpy( get_img_cpu_ptr(), get_img_gpu_ptr(), rese_img(), cudaMemcpyDeviceToHost );
}

unsigned *BitmapDisplay::get_img_gpu_ptr() {
    if ( not img_gpu )
        cudaMalloc( &img_gpu, rese_img() );
    return img_gpu;
}

unsigned *BitmapDisplay::get_img_cpu_ptr() {
    if ( not img_cpu )
        img_cpu = (unsigned *)malloc( rese_img() );
    return img_cpu;
}

END_METIL_NAMESPACE;
