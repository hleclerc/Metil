#include "DynamicLibrary.h"
#include "String.h"

#ifndef WIN32
    #include <dlfcn.h>
#else
    #include <windows.h>
#endif

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name dl
#endif

BEG_METIL_NAMESPACE;


DynamicLibrary::DynamicLibrary() {
    data = 0;
}

DynamicLibrary::~DynamicLibrary() {
    if ( data )
        dlclose( data );
}

bool DynamicLibrary::open( String name ) {
    static bool global_opened = 0;
    if ( not global_opened ) {
        global_opened = true;
        dlopen( 0, RTLD_GLOBAL );
    }

    file = name;

    #ifdef WIN32
    data = LoadLibrary( (const WCHAR *)lib );
    #else
    data = dlopen( name.c_str(), RTLD_LAZY + RTLD_GLOBAL );
    #endif
    return data;
}

void *DynamicLibrary::get_sym( String name ) {
    return data ? dlsym( data, name.c_str() ) : 0;
}

DynamicLibrary::operator bool() const {
    return data;
}

String DynamicLibrary::error() const {
    return dlerror();
}

END_METIL_NAMESPACE;
