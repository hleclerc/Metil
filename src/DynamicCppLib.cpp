#include "Level1/CompilationEnvironment.h"
#include "DynamicCppLib.h"
#include "System.h"

BEG_METIL_NAMESPACE;

DynamicCppLib::DynamicCppLib( const String &cpp_file ) {
    Level1::CompilationEnvironment &ce = Level1::CompilationEnvironment::get_main_compilation_environment();
    // ce.add_macro( "METIL_GENE_DYLIB" );

    String lib_file = ce.lib_for( cpp_file, true );
    ce.make_lib( lib_file, cpp_file, true );

    // open the .so
    lib.open( lib_file );
    if ( not lib )
        ERROR( "Error during lib load %s", lib.error().c_str() );
}

void *DynamicCppLib::get_sym( const String &name ) {
    return lib.get_sym( name );
}

END_METIL_NAMESPACE;
