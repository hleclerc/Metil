#ifndef IMG_H
#define IMG_H

#include "MachineId.h"
#include "Array.h"

BEG_METIL_NAMESPACE;

class Img : public Array<Val> {
public:
    Img();
    Img( const String &filename, const MachineId *machine = MachineId::cur() ); ///< load( filename )

    void load( const String &filename, const MachineId *machine = MachineId::cur() ); ///< try to guess the type using the filename extension

    void load_tiff( const String &filename, const MachineId *machine );
    void load_qimg( const String &filename, const MachineId *machine );
};

END_METIL_NAMESPACE;

#endif // IMG_H
