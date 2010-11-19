#ifndef IMG_H
#define IMG_H

#include "MachineId.h"
#include "Array.h"

BEG_METIL_NAMESPACE;

class Img : public Array<Val> {
public:
    Img();
    Img( ST w, ST h, Level1::Type *bas_type );
    Img( const String &filename, const MachineId *machine = 0 ); ///< load( filename )

    void load( const String &filename, const MachineId *machine = 0 ); ///< try to guess the type using the filename extension

    void load_tiff( const String &filename, const MachineId *machine );
    void load_qimg( const String &filename, const MachineId *machine );

    Val w() const; ///< width
    Val h() const; ///< height

    // void save_png( const Val &min = 0, const Val &max = -1 ); ///<
    // void save_png( bool auto_contrast ); ///<
};

END_METIL_NAMESPACE;

#endif // IMG_H
