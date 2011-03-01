#ifndef DYNAMICCPPLIB_H
#define DYNAMICCPPLIB_H

#include "DynamicLibrary.h"
#include "Ptr.h"

BEG_METIL_NAMESPACE;

/**
  Used to construct and load a .so from a .cpp

  Make the .so in the construction dir

  If to date of the .so is > of the date of the .cpp, use the already existing .so
*/
class DynamicCppLib {
public:
    struct CppMaker {
        virtual void operator()( String &file, StringWithSepInCppLineMaker &file_n ) const = 0;
    };

    DynamicCppLib( const String &cpp_name, const CppMaker &cpp_maker ); ///< if the cpp_file does not exist, make it usin cpp_maker
    DynamicCppLib( const String &cpp_name ); ///< assumes the cpp_file already exist

    void *get_sym( const String &name );

protected:
    void make_and_open( const String &cpp_name );
    DynamicLibrary lib;
};

template<class Symbol>
struct DynamicCppLibAndSymbol : public ObjectWithCptUse {
    DynamicCppLibAndSymbol( const String &cu_name, const DynamicCppLib::CppMaker &cpp_maker, const String &func_name ) : lib( cu_name, cpp_maker ) {
        symbol = reinterpret_cast<Symbol *>( lib.get_sym( func_name ) );
        ASSERT( symbol, "not found" );
    }

    DynamicCppLib lib;
    Symbol *symbol;
};

END_METIL_NAMESPACE;

#endif // DYNAMICCPPLIB_H
