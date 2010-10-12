#include "BitmapDisplay.h"
#include "CudaMetil.h"
#include "Png.h"

BEG_METIL_NAMESPACE;

BitmapDisplay::BitmapDisplay( int w, int h ) : GenericDisplay( w, h ) {
    img_cpu = 0;
    img_gpu = 0;
}

void BitmapDisplay::render() {
    for( ST i = 0; i < items.size(); ++i )
        items[ i ]->render_to( this );
}

Ps<char> BitmapDisplay::make_png() {
    return Metil::make_png( get_img_cpu_ptr(), w, h );
}

void BitmapDisplay::save_png( const String &filename ) {
    Ps<char> data = make_png();
    File os( filename, "w" );
    os.write( data.data, data.size );
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
