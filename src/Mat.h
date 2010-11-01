#ifndef MAT_H
#define MAT_H

#include "Vec.h"

BEG_METIL_NAMESPACE;

/**
*/
class Mat : public Array<Val> {
public:
    Mat();
    Mat( ST r, ST c, Level1::Type *base_type = 0 );

protected:
    Level1::MO *init_dyn_mat( ST r, ST c );
};

END_METIL_NAMESPACE;

#endif // MAT_H
