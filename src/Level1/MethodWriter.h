#ifndef METHODWRITER_H
#define METHODWRITER_H

#include "../DynamicLibrary.h"
#include "../BasicVec.h"
#include "../Mos.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
class MethodWriter {
public:
    enum { nb_args_max = 3 };
    MethodWriter( MethodWriter *parent = 0 );

    MethodWriter &operator<<( const String &str );
    void beg_def( const String &def_name );
    void end_def();
    int nb_types() const;
    void write_to( String &os );
    void add_include( const String &include );
    void add_preliminary( const String &txt ); ///< after includes and namespace
    void add_type_decl( const String &name ); ///< add declaration for type "name" and look if there's a declaration somewhere
    StringWithSepInCppLineMaker ret(); ///< signal return

    bool get_os_defined() const;
    void set_os_defined( bool v );
    Type *get_type( int n ) const { return type[ n ]; }

    static String def_str( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static String decl_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static String symb_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2, bool cpp );
    static DynamicLibrary &get_lib_for_types( Type *type_0, Type *type_1, Type *type_2, const char *dep_file );
    static void make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 );

    bool call_gene( const String &method, Type *type_0, const Mos &arg_0, const String &ret = "", bool abort_if_not_found = false );
    bool call_gene( const String &method, Type *type_0, Type *type_1, const Mos &arg_0, const Mos &arg_1, const String &ret = "", bool abort_if_not_found = false );

    Type *type[ nb_args_max ];
    Mos   arg [ nb_args_max ];
    String ret_ins;
    MachineId::Type machine_type;
    StringWithSepInCppLineMaker n; ///< used to output lines with CR at the end
private:
    MethodWriter( const MethodWriter &parent ) : n( parent.n ) { ERROR("..."); }
    MethodWriter *parent;
    String preliminary;
    String code;
    BasicVec<String> includes;
    BasicVec<String> ext_types;
    bool os_defined;
};

typedef void MethodMaker( MethodWriter &mw );

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODWRITER_H
