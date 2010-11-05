#ifndef DYNAMICCPPLIB_H
#define DYNAMICCPPLIB_H

#include "DynamicLibrary.h"

BEG_METIL_NAMESPACE;

/**
  Used to construct and load a .so from a .cpp

  Make the .so in the construction dir

  If to date of the .so is > of the date of the .cpp, use the already existing .so
*/
class DynamicCppLib {
public:
    DynamicCppLib( const String &cpp_file );
    void *get_sym( const String &name );

    DynamicLibrary lib;
};

END_METIL_NAMESPACE;

#endif // DYNAMICCPPLIB_H
