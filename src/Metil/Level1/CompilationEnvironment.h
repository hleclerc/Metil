#ifndef COMPILATIONENVIRONMENT_H
#define COMPILATIONENVIRONMENT_H

#include "CompilationTree.h"
#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

class CompilationEnvironment {
public:
    CompilationEnvironment( CompilationEnvironment *ch = 0 );

    String find_src( const String &filename, const String &current_dir, const BasicVec<String> &add_paths = BasicVec<String>(), bool allow_cur_dir = true ) const; // use current_dir and include_dirs to find filename
    String comp_dir() const;

    void add_inc_path( const String &path );
    void add_lib_path( const String &path );
    void add_lib_name( const String &name );
    void add_fra_name( const String &name );
    void add_CPPFLAG ( const String &flag );
    void add_GPUFLAG ( const String &flag );
    void add_LDFLAG  ( const String &flag );
    void add_def_proc( const String &proc );

    void add_CPPFLAG ( const String &flag, const String &cpp ); ///< add flag only for cpp

    void set_CXX     ( const String &path );
    void set_device_emulation( bool flag );
    void set_maxrregcount( int nb_registers );
    void set_comp_dir( const String &path );
    void set_nb_threads( int nb_threads );
    void set_dbg_level( int level );
    void set_opt_level( int level );

    String get_NVCC() const;
    String get_CXX () const;
    String get_CC  () const;
    String get_LD  () const;

    int get_nb_threads() const;
    int get_dbg_level() const;
    int get_opt_level() const;
    int get_device_emulation() const;
    int want_m32() const;

    void get_inc_paths( BasicVec<String> &res ) const;
    void get_def_procs( BasicVec<String> &res ) const;

    void save_env_var( bool update_LD_LIBRARY_PATH = true ) const; ///< save data in environment variables (METIL_INC_PATHS, ...)
    void load_env_var(); ///< append data from environment variables (METIL_INC_PATHS, ...)

    String obj_suffix( bool dyn ); ///< .os, .o, ... depending on the system
    String lib_suffix( bool dyn ); ///< .so, .a, ... depending on the system
    String exe_suffix(); ///< .exe, ... depending on the system
    String dep_suffix(); ///< .dep

    String h_for( const String &bas ); ///< ex: toto -> compilation/toto.h
    String cpp_for( const String &bas ); ///< ex: toto -> compilation/toto.cpp
    String cu_for ( const String &bas ); ///< ex: toto -> compilation/toto.cu
    String obj_for( const String &cpp, bool dyn ); ///< ex: toto.cpp -> compilation/toto.os
    String lib_for( const String &cpp, bool dyn ); ///< ex: toto.cpp -> compilation/toto.so
    String mex_for( const String &cpp ); ///< .mexglx
    String exe_for( const String &cpp ); ///< ex: toto.cpp -> compilation/toto.cpp.exe
    String dep_for( const String &cpp ); ///< ex: toto.cpp -> compilation/toto.cpp.dep

    String obj_cmd( const String &obj, const String &cpp, bool dyn ) const;
    String lnk_cmd( const String &exe, const BasicVec<String> &obj, bool lib, bool dyn ) const;

    Ptr<CompilationTree> make_compilation_tree( const String &app, const String &cpp, bool lib, bool dyn, bool make_libs = true );
    int make_app( const String &app, const String &cpp, bool lib, bool dyn, bool make_libs = true );
    int make_lib( const String &lib, const String &cpp, bool dyn );
    int make_exe( const String &exe, const String &cpp );

    static CompilationEnvironment &get_main_compilation_environment();

protected:
    Ptr<CompilationTree> make_cpp_compilation_tree( const String &cpp );
    Ptr<CompilationTree> make_obj_compilation_tree( const String &obj, Ptr<CompilationTree> cpp, bool dyn );
    Ptr<CompilationTree> make_lnk_compilation_tree( const String &app, const BasicVec<Ptr<CompilationTree> > &obj, bool lib, bool dyn );

    void parse_cpp( BasicVec<Ptr<CompilationTree> > &obj, const String &cpp, bool dyn );
    void extra_obj_cmd( String &cmd, bool dyn, bool cu, const String &cpp ) const;
    void extra_lnk_cmd( String &cmd, bool lib, bool dyn ) const;
    CompilationEnvironment *deepest_child();

    BasicVec<String> inc_paths;
    BasicVec<String> lib_paths;
    BasicVec<String> lib_names;
    BasicVec<String> fra_names;
    BasicVec<String> def_procs;
    String _comp_dir;
    String CXX;
    String CC;
    String LD;
    String NVCC;
    String CPPFLAGS;
    String GPUFLAGS;
    String LDFLAGS;
    int device_emulation;
    int maxrregcount;
    int nb_threads;
    int dbg_level;
    int opt_level;
    int system_uses_frameworks;

    std::map<String,String> loc_CPPFLAGS; ///< per cpp

    CompilationEnvironment *child;
    BasicVec<String> parsed;
    std::map<String,Ptr<CompilationTree> > cor_files;
};


END_METIL_LEVEL1_NAMESPACE;

#endif // COMPILATIONENVIRONMENT_H
