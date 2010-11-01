#include "BitmapDisplay.h"
#include "Level1/StringHelp.h"
#include "CudaMetil.h"
#include "Base64.h"
#include "Png.h"

#include <limits>
#include <sys/socket.h>

BEG_METIL_NAMESPACE;

BitmapDisplay::BitmapDisplay( int w, int h ) : GenericDisplay( w, h ), img_rgba( this ), img_zznv( this ), img_nnnn( this ) {
}

void BitmapDisplay::render() {
    update_p_min_p_max();
    rz_min_max[ 0 ] = 65535;
    rz_min_max[ 1 ] = 0;
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
    return Metil::make_png( (unsigned char *)img_rgba.get_cpu_ptr(), w, h, false, prelim, prelim_size );
}

void BitmapDisplay::save_png( const String &filename ) {
    Ps<char> data = make_png();
    File os( filename, "w" );
    os.write( data.data, data.size );
    data.free();
}

void BitmapDisplay::save_png_in_sock( int socket_id, const char *name ) {
    Socket res( socket_id );
    Ps<char> data;

    //
    res << name << ".z_min = " << p_min[ 2 ] << ";\n";
    res << name << ".z_max = " << p_max[ 2 ] << ";\n";
    get_trans_data( res, String( name ) + ".RP" );
    get_trans_data( res, String( name ) + ".IP" );

    //
    #define DISP_IMG( N ) \
        data = Metil::make_png( (unsigned char *)N.get_cpu_ptr(), w, h ); \
        res << name << "." #N ".src = 'data:image/png;base64,"; \
        to_base_64( res, data.data, data.size ); \
        res << "';\n"; \
        data.free()

    DISP_IMG( img_zznv );
    DISP_IMG( img_nnnn );
    DISP_IMG( img_rgba );

    #undef DISP_IMG
}


ST BitmapDisplay::Img::rese() {
    return 4 * d->get_w() * d->get_h();
}

unsigned *BitmapDisplay::Img::get_cpu_ptr() {
    if ( not cpu )
        cpu = (unsigned *)malloc( rese() );
    return cpu;
}

unsigned *BitmapDisplay::Img::get_gpu_ptr() {
    if ( not gpu )
        cudaMalloc( &gpu, rese() );
    return gpu;
}

void BitmapDisplay::Img::copy_gpu_to_cpu() {
    cudaMemcpy( get_cpu_ptr(), get_gpu_ptr(), rese(), cudaMemcpyDeviceToHost );
}

void BitmapDisplay::copy_gpu_to_cpu() {
    img_rgba.copy_gpu_to_cpu();
    img_zznv.copy_gpu_to_cpu();
    img_nnnn.copy_gpu_to_cpu();
}


END_METIL_NAMESPACE;
