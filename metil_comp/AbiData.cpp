/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "AbiData.h"
#include "String.h"

#define HAVE_LIBDL

#ifdef HAVE_LIBDL
    #include <dlfcn.h>
#else
    #include <windows.h>
#endif

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name dl
#endif

namespace Metil {

/**

*/
class AbiDataLibDl : public AbiData {
public:
    AbiDataLibDl( const String &lib_name ) {
        #ifdef HAVE_LIBDL
            lib = dlopen( lib_name.data(), RTLD_LAZY );
        #else
            lib = LoadLibrary( lib_name.data() );
        #endif
    }
    virtual ~AbiDataLibDl() {
        #ifdef HAVE_LIBDL
            if ( lib ) dlclose( lib );
        #else
            FreeLibrary( static_cast<HMODULE>( lib ) );
        #endif
    }
    virtual void *get_symbol( const String &symbol ) {
        if ( not lib )
            return 0;
        #ifdef HAVE_LIBDL
            return dlsym( lib, symbol.data() ); 
        #else
            return (void *)GetProcAddress( static_cast<HMODULE>(lib), symbol.data() );
        #endif
    }
    virtual String last_error() const {
        #ifdef HAVE_LIBDL
            return dlerror(); 
        #else
            LPVOID lpMsgBuf;
            
            FormatMessage( 
                            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                            NULL,
                            GetLastError(),
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                            (LPTSTR) &lpMsgBuf,
                            0,
                            NULL 
                            );
            
            // Free the buffer.
            static char *str = 0;
            delete [] str;
            if (lpMsgBuf) {
                str = strcpy(new char[strlen((char*)lpMsgBuf)+1], (char*)lpMsgBuf);
                LocalFree( lpMsgBuf );
            }
            return str;
        #endif
        return String();
    }
    virtual operator bool() const {
        return lib;
    }
    
    void *lib;
};



// ------------------------------------------------------------------------------------
AbiData::~AbiData() {
}

AbiData *AbiData::load( const String &lib_file ) {
    return new AbiDataLibDl( lib_file );
}


}
