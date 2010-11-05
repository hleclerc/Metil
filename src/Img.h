#ifndef IMG_H
#define IMG_H

#include "Array.h"

BEG_METIL_NAMESPACE;

class Img : public Array<Val> {
public:
    Img();
    Img( const String &filename ); ///< load( filename )

    void load( const String &filename ); ///< try to guess the type using the filename extension

    void load_tiff( const String &filename );
    void load_qimg( const String &filename );
};

END_METIL_NAMESPACE;

#endif // IMG_H
