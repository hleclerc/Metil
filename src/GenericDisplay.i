%{
    #include "GenericDisplay.h"
%}

%include "DisplayItem.i"

namespace Metil {
    class GenericDisplay {
    public:
        typedef float T;
        // typedef BasicVec<T,3> T3;

        GenericDisplay( int w = 400, int h = 400 );

        void set_O( T Ox, T Oy, T Oz );
        void set_X( T Xx, T Xy, T Xz );
        void set_Y( T Yx, T Yy, T Yz );
        void set_d( T d );
        void set_a( T a );

        int get_w() const;
        int get_h() const;
        void set_w( int w );
        void set_h( int h );

        void update_p_min_p_max();
        void fit();

        // T3 p_min; ///< after projection
        // T3 p_max; ///< after projection
    };

    %extend GenericDisplay {
        GenericDisplay &add_item( DisplayItem *item ) { *self << item; return *self; }
    };
}

