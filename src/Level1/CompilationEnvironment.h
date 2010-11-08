#ifndef COMPILATIONENVIRONMENT_H
#define COMPILATIONENVIRONMENT_H

#include "CompilationTree.h"
#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

class CompilationEnvironment {
public:
    CompilationEnvironment( CompilationEnvironment *ch = 0 );

    String find_src( const String &filename, const String &current_dir ) const; // use current_dir and include_dirs to find filename
    String comp_dir() const;

    void add_inc_path( const String &path );
    void add_lib_path( const String &path );
    void add_lib_name( const String &name );
    void add_CPPFLAG ( const String &flag );
    void set_CXX     ( const String &path );
    void set_device_emulation( bool flag );
    void set_maxrregcount( int nb_registers );
    void set_comp_dir( const String &path );

    String get_CXX     () const;
    String get_LD      () const;

    void save_env_var( bool update_LD_LIBRARY_PATH = true ) const; ///< save data in environment variables (METIL_INC_PATHS, ...)
    void load_env_var(); ///< append data from environment variables (METIL_INC_PATHS, ...)

    String obj_suffix( bool dyn ); ///< .os, .o, ... depending on the system
    String lib_suffix( bool dyn ); ///< .so, .a, ... depending on the system
    String exe_suffix(); ///< .exe, ... depending on the system

    String cpp_for( const String &bas ); ///< ex: toto -> compilation/toto.cpp
    String obj_for( const String &cpp, bool dyn ); ///< ex: toto.cpp -> compilation/toto.os
    String lib_for( const String &cpp, bool dyn ); ///< ex: toto.cpp -> compilation/toto.so
    String mex_for( const String &cpp ); ///< .mexglx
    String exe_for( const String &cpp ); ///< ex: toto.cpp -> compilation/toto.exe

    String obj_cmd( const String &obj, const String &cpp, bool dyn ) const;
    String lnk_cmd( const String &exe, const BasicVec<String> &obj, bool lib, bool dyn ) const;

    int make_app( const String &app, const String &cpp, bool lib, bool dyn );
    int make_lib( const String &lib, const String &cpp, bool dyn );
    int make_exe( const String &exe, const String &cpp );

    static CompilationEnvironment &get_main_compilation_environment();

protected:
    Ptr<CompilationTree> make_cpp_compilation_tree( const String &cpp );
    Ptr<CompilationTree> make_obj_compilation_tree( const String &obj, Ptr<CompilationTree> cpp, bool dyn );
    Ptr<CompilationTree> make_lnk_compilation_tree( const String &app, const BasicVec<Ptr<CompilationTree> > &obj, bool lib, bool dyn );

    void parse_cpp( BasicVec<Ptr<CompilationTree> > &obj, const String &cpp, bool dyn );
    void extra_obj_cmd( String &cmd, bool dyn ) const;
    void extra_lnk_cmd( String &cmd, bool lib, bool dyn ) const;
    CompilationEnvironment *deepest_child();

    BasicVec<String> inc_paths;
    BasicVec<String> lib_paths;
    BasicVec<String> lib_names;
    String _comp_dir;
    String CXX;
    String LD;
    String NVCC;
    String CPPFLAGS;
    String LDFLAGS;
    bool device_emulation;
    int maxrregcount;

    CompilationEnvironment *child;
    BasicVec<String> parsed;
    std::map<String,Ptr<CompilationTree> > cor_files;
};


END_METIL_LEVEL1_NAMESPACE;

#endif // COMPILATIONENVIRONMENT_H
