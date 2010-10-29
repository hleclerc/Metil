#ifndef VEC_H
#define VEC_H

#include "Array.h"

BEG_METIL_NAMESPACE;

/**
  Array of Val (i.e. scalars)
*/
class Vec : public Array<Val> {
public:
    Vec( const Val &v_0 );
    Vec( const Val &v_0, const Val &v_1 );

protected:
    Level1::MO *init_dyn_vec( ST size );
};

END_METIL_NAMESPACE;

#endif // VEC_H
