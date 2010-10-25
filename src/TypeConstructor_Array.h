#ifndef TYPECONSTRUCTOR_ARRAY_H
#define TYPECONSTRUCTOR_ARRAY_H

#include "TypeConstructor.h"
#include "BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;
/**
  name -> contains
    - dim
    - size[ 0 ]
    - rese[ 0 ]
    - ...
    - size[ n ]
    - rese[ n ]
    - [Owcp]
    - [ExtPtr]
*/
class TypeConstructor_Array : public TypeConstructor {
public:
    virtual void init( Type *type );

    BasicVec<ST> size;
    BasicVec<ST> rese;
    bool owcp;
    bool ext_ptr;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_ARRAY_H
