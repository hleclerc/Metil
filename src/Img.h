#ifndef IMG_H
#define IMG_H

#include "MachineId.h"
#include "Array.h"

BEG_METIL_NAMESPACE;

class Img : public Array<Val> {
public:
    Img();
    Img( ST w, ST h, Level1::Type *bas_type ); ///< typed 2D image
    Img( const String &filename ); ///< load( filename )

    template<class T,int dim>
    Img( const String &filename, S<T> t, const BasicVec<ST,dim> &XS ) { ///< raw data
        load( filename, t, XS );
    }

    void load( const String &filename ); ///< try to guess the type using the filename extension
    void load( const String &filename, Level1::Type *type, const BasicVec<ST> &XS );

    template<class T,int dim>
    void load( const String &filename, S<T> t, const BasicVec<ST,dim> &XS ) { ///< raw data
        load( filename, &Level1::type_ptr( t ), XS );
    }

    void load_tiff( const String &filename );
    void load_qimg( const String &filename );

    Val w() const; ///< width
    Val h() const; ///< height
    Val d() const; ///< depth

    // void save_png( const Val &min = 0, const Val &max = -1 ); ///<
    // void save_png( bool auto_contrast ); ///<
};

END_METIL_NAMESPACE;

#endif // IMG_H
