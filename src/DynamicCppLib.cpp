#include "DynamicCppLib.h"
#include "System.h"

BEG_METIL_NAMESPACE;

DynamicCppLib::DynamicCppLib( const String &cpp_file ) {
    // filename
    String bas_name = get_env( "METIL_COMP_DIR" );
    if ( not bas_name.size() )
        bas_name = "compilations";
    if ( not bas_name.ends_with("/") )
        bas_name << "/";

    // compilation if necessary
    String lib_name = bas_name + ".so";
    SI64 date_cpp = last_modification_time_or_zero_of_file_named( cpp_file );
    SI64 date_lib = last_modification_time_or_zero_of_file_named( lib_name );
    if ( date_lib <= date_cpp ) { // we have to compile the cpp
        String cmd = get_env( "METIL_CXX_CMD" );
        ASSERT( cmd.size(), "METIL_CXX_CMD is not defined in env var (done by metil_comp)" );
        cmd << " -DMETIL_GENE_DYLIB -g3 -fPIC -shared -o "  << lib_name << " "  << cpp_file;
        if ( exec_cmd( cmd ) )
            ERROR( "Pb during compilation of %s", cpp_file.c_str() );
    }

    // open the .so
    lib.open( lib_name );
    if ( not lib )
        ERROR( "Error during lib load %s", lib.error().c_str() );
}

void *DynamicCppLib::get_sym( const String &name ) {
    return lib.get_sym( name );
}

END_METIL_NAMESPACE;
