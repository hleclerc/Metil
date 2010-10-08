#ifndef TYPECONSTRUCTOR_CONSTCHARPTRWITHSIZE_H
#define TYPECONSTRUCTOR_CONSTCHARPTRWITHSIZE_H

#include "TypeConstructor_String.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct TypeConstructor_ConstCharPtrWithSize : public TypeConstructor_String {
    struct Data {
        Data( const char *data, ST size ) : data( data ), size( size ) {}
        const char *data;
        ST size;
    };
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_CONSTCHARPTRWITHSIZE_H
