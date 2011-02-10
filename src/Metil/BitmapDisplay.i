%{
    #include "BitmapDisplay.h"
%}

%include "GenericDisplay.i"

namespace Metil {
    class BitmapDisplay : public GenericDisplay {
    public:
        BitmapDisplay( int w = 400, int h = 400 );

        void render();
        void copy_gpu_to_cpu(); ///< after render()
        void save_png( const char *filename ); ///< make and save png to a file
        void save_png_in_sock( int socket_id, const char *name ); ///< make and save png to a file
    };
}
