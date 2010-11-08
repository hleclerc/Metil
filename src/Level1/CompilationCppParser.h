#ifndef COMPILATIONCPPPARSER_H
#define COMPILATIONCPPPARSER_H

#include "CompilationEnvironment.h"
#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

class CompilationCppParser {
public:
    CompilationCppParser( CompilationEnvironment &ce, const String &cpp_file );

    // output
    BasicVec<String> inc_files; ///< files that have been included
    BasicVec<String> hpy_files; ///< .h.py files
    BasicVec<String> moc_files; ///<
    BasicVec<String> src_files; ///< .cpp files that are recquired to link this file

    BasicVec<String> lib_paths; ///< -L...
    BasicVec<String> lib_names; ///< -l... i.e. recquired .so / .dll / .dylib files
    BasicVec<String> inc_paths; ///< -I...
    BasicVec<String> cpp_flags; ///<
    BasicVec<String> lnk_flags; ///<
    BasicVec<String> gpu_flags; ///<
    bool need_compilation_environment;

private:
    struct Define {
        BasicVec<String> args;
        String val;
    };

    void parse_src_file_rec( CompilationEnvironment &ce, const String &filename );

    // static String filename_from_directive( const char *b );
    std::map<String,Define> defines;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // COMPILATIONCPPPARSER_H
