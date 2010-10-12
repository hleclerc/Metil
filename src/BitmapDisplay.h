#ifndef BitmapDisplay_H
#define BitmapDisplay_H

#include "GenericDisplay.h"
#include "String.h"
#include "Ps.h"

BEG_METIL_NAMESPACE;

/**
  Create a bitmap image from a DisplayItem list

  The resulting image will contain r(8)g(8)b(8)a(8), z(16)dot(n,z)(8)val(8), num_elem(32)
*/
class BitmapDisplay : public GenericDisplay {
public:
    static const int nb_img = 3;
    BitmapDisplay( int w = 400, int h = 400 );

    void render();
    void copy_gpu_to_cpu(); ///< after render()
    Ps<char> make_png(); ///< after copy_gpu_to_cpu()
    void save_png( const String &filename ); ///< make and save png to a file

    unsigned *get_img_gpu_ptr();
    unsigned *get_img_cpu_ptr();

    ST rese_img(); ///< size of image in bytes
    ST nb_lines(); ///< total nb lines in img

protected:
    unsigned *img_cpu; //
    unsigned *img_gpu; //
};

END_METIL_NAMESPACE;

#endif // BitmapDisplay_H
