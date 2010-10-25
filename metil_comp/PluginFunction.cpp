#include "PluginFunction.h"
#include "ExternCompilationEnvironment.h"
#include "File.h"
#include "AbiData.h"
#include "CompilationGraph.h"
#include "AutoPtr.h"
#include "System.h"
#include <map>

namespace Metil {

static std::map<String,AutoPtr<AbiData> > abi_data_map;

void *make_function( const String &cpp_filename, const String &cpp_function ) {
    CompilationEnvironment &ce = compilation_environment();
    String lib_filename = ce.lib_file_for( cpp_filename, true );

    //
    AutoPtr<AbiData> &abi_data = abi_data_map[ lib_filename ];
    if ( not abi_data ) {
        AutoPtr<CompilationGraphProgram> cg;
        cg = new CompilationGraphProgram( ce, lib_filename, true );
        cg->add_src_file( cpp_filename );

        // do it
        int res_make = cg->make();
        if ( res_make )
            return 0;

        // loading
        abi_data = AbiData::load( lib_filename );
        if ( not *abi_data )
            PRINT( abi_data->last_error() );
    }

    return abi_data->get_symbol( cpp_function );
}


} // namespace Metil
