#ifndef DYNAMICLIBRARY_H
#define DYNAMICLIBRARY_H

#include "String.h"

BEG_METIL_NAMESPACE;

class DynamicLibrary {
public:
    DynamicLibrary();
    bool open( String name );
    ~DynamicLibrary();

    operator bool() const;
    String error() const;
    void *get_sym( String name );

    void *data;
};

END_METIL_NAMESPACE;

#endif // DYNAMICLIBRARY_H
