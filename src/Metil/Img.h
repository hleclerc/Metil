#ifndef IMG_H
#define IMG_H

#include "Vec.h"

BEG_METIL_NAMESPACE;

class Img : public Array<Val> {
public:
    Img();
    Img( ST w, ST h, Level1::Type *bas_type ); ///< typed 2D image
    Img( const String &filename ); ///< load( filename )

    Img( Level1::MO mo ) : Array<Val>( mo ) {}

    template<class T>
    Img( const String &filename, S<T> t, const Vec &XS ) { ///< raw data
        load( filename, t, XS );
    }


    void load( const String &filename ); ///< try to guess the type using the file extension
    void load( const String &filename, Level1::Type *type, const Vec &XS );

    template<class T>
    void load( const String &filename, S<T> t, const Vec &XS ) { ///< raw data
        load( filename, Level1::type_ptr( t ), XS );
    }

    void load_tiff( const String &filename );
    void load_qimg( const String &filename );

    Val w() const; ///< width
    Val h() const; ///< height
    Val d() const; ///< depth

    Val size( int i ) const { return sizes()[ i ]; }

    void convert_to_gpu_tex();

    // void save_png( const String &filename ) const;
    // void save_png( const Val &min = 0, const Val &max = -1 ); ///<
    // void save_png( bool auto_contrast ); ///<
};

END_METIL_NAMESPACE;

#endif // IMG_H
