#ifndef DYNAMICLIBRARY_H
#define DYNAMICLIBRARY_H

#include "String.h"

BEG_METIL_NAMESPACE;

class DynamicLibrary {
public:
    DynamicLibrary();
    DynamicLibrary( String name );
    ~DynamicLibrary();

    void *get_sym( String name );

    void *data;
};

END_METIL_NAMESPACE;

#endif // DYNAMICLIBRARY_H