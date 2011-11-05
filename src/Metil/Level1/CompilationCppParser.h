#ifndef COMPILATIONCPPPARSER_H
#define COMPILATIONCPPPARSER_H

#include "CompilationEnvironment.h"
#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

class CompilationCppParser {
public:
    CompilationCppParser( CompilationEnvironment &ce, const String &cpp_file, const String &dep_file );
    ~CompilationCppParser();

    // output
    BasicVec<String> inc_files; ///< files that have been included
    BasicVec<String> moc_files; ///<
    BasicVec<String> src_files; ///< .cpp files that are recquired to link this file

    BasicVec<String> lib_paths; ///< -L...
    BasicVec<String> lib_names; ///< -l... i.e. recquired .so / .dll / .dylib files
    BasicVec<String> fra_names; ///< -l... i.e. recquired .so / .dll / .dylib files
    BasicVec<String> inc_paths; ///< -I...
    BasicVec<String> cpp_flags; ///<
    BasicVec<String> lnk_flags; ///<
    BasicVec<String> gpu_flags; ///<

    BasicVec<String> var_templ; ///< template variables
    
private:
    struct Define {
        BasicVec<String> args;
        String val;
    };

    bool init_using_dep( CompilationEnvironment &ce, const String &cpp_file, const String &dep_file );
    void parse_src_file_rec( CompilationEnvironment &ce, const String &filename );
    void make_h_py( const String &h_py, const String &inc_file );

    BasicVec<String> ce_inc_paths; ///< -I... which come from CompilationEnvironment
    BasicVec<String> ce_def_procs; ///< -D... which come from CompilationEnvironmentd

    BasicVec<String> already_parsed;
    std::map<String,Define> defines;
    String dep_file;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // COMPILATIONCPPPARSER_H
