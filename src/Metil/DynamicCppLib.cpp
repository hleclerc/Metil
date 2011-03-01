#include "Level1/CompilationEnvironment.h"
#include "DynamicCppLib.h"
#include "System.h"

BEG_METIL_NAMESPACE;

DynamicCppLib::DynamicCppLib( const String &_cpp_name, const CppMaker &cpp_maker ) {
    Level1::CompilationEnvironment &ce = Level1::CompilationEnvironment::get_main_compilation_environment();
    String cpp_name = ce.comp_dir() + _cpp_name;
    if ( not file_exists( cpp_name ) ) {
        File cpp_file( cpp_name, "w" );
        StringWithSepInCppLineMaker cnn_file( cpp_file );
        cpp_maker( cpp_file, cnn_file );
    }
    make_and_open( cpp_name );
}

DynamicCppLib::DynamicCppLib( const String &cpp_name ) {
    make_and_open( cpp_name );
}

void DynamicCppLib::make_and_open( const String &cpp_name ) {
    Level1::CompilationEnvironment &ce = Level1::CompilationEnvironment::get_main_compilation_environment();
    // ce.add_macro( "METIL_GENE_DYLIB" );

    String lib_file = ce.lib_for( cpp_name, true );
    ce.make_lib( lib_file, cpp_name, true );

    // open the .so
    lib.open( lib_file );
    if ( not lib )
        ERROR( "Error during lib load %s", lib.error().c_str() );
}

void *DynamicCppLib::get_sym( const String &name ) {
    return lib.get_sym( name );
}

END_METIL_NAMESPACE;
