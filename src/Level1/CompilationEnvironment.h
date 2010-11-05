#ifndef COMPILATIONENVIRONMENT_H
#define COMPILATIONENVIRONMENT_H

#include "BasicVec.h"
#include "String.h"

BEG_METIL_LEVEL1_NAMESPACE;

class CompilationEnvironment {
public:
    CompilationEnvironment();

    String find_src( const String &filename, const String &current_dir ) const; // use current_dir and include_dirs to find filename
    String comp_dir() const;

    void add_inc_path( const String &d );

    String obj_suffix( bool dyn ); ///< .so, .o, ...

    String obj_for( const String &cpp, bool dyn ); ///<

    String make_exe_cmd( const String &exe );
    String make_lnk_cmd( const String &exe, bool lib, bool dyn );
    String make_obj_cmd( const String &obj, const String &cpp, bool dyn );

    int make_obj( const String &obj, const String &cpp, bool dyn );
    int make_exe( const String &exe, const String &cpp );

protected:
    BasicVec<String> inc_paths;
    BasicVec<String> lib_paths;
    BasicVec<String> lib_names;
    BasicVec<String> obj_files;
    String _comp_dir;
    String CXX;
    String LD;
    String NVCC;
    String CPPFLAGS;
    String LDFLAGS;
    bool device_emulation;
    SI32 maxrregcount;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // COMPILATIONENVIRONMENT_H
