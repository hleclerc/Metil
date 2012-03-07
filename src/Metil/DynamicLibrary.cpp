#include "DynamicLibrary.h"
#include "String.h"
#include "System.h"

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#ifdef METIL_COMP_DIRECTIVE
#ifndef WIN32
#pragma lib_name dl
#endif
#endif

BEG_METIL_NAMESPACE;


DynamicLibrary::DynamicLibrary() {
    data = 0;
}

DynamicLibrary::~DynamicLibrary() {
#ifdef WIN32
    TODO;
#else
    if ( data )
        dlclose( data );
#endif
}

bool DynamicLibrary::open( String name ) {
    file = name;

    #ifdef WIN32
    TODO;
    data = LoadLibrary( name.c_str() );
    #else
    static bool global_opened = 0;
    if ( not global_opened ) {
        global_opened = true;
        dlopen( 0, RTLD_GLOBAL );
    }

    // PRINT( name.c_str() );
    data = dlopen( name.c_str(), RTLD_LAZY + RTLD_GLOBAL );
    // PRINT( error() );
    // exec_cmd( "export" );
    #endif
    return data;
}

void *DynamicLibrary::get_sym( String name ) {
#ifdef WIN32
    TODO;
    return 0;
#else
    return data ? dlsym( data, name.c_str() ) : 0;
#endif
}

DynamicLibrary::operator bool() const {
    return data;
}

String DynamicLibrary::error() const {
#ifdef WIN32
    TODO;
    return "";
#else
    return dlerror();
#endif
}

END_METIL_NAMESPACE;
