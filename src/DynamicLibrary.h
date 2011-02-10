#ifndef DYNAMICLIBRARY_H
#define DYNAMICLIBRARY_H

#include "MetilString.h"

BEG_METIL_NAMESPACE;

class DynamicLibrary {
public:
    DynamicLibrary();
    ~DynamicLibrary();

    bool open( String name );
    operator bool() const;
    String error() const;
    void *get_sym( String name );

    String file;
    void *data;
};

END_METIL_NAMESPACE;

#endif // DYNAMICLIBRARY_H
