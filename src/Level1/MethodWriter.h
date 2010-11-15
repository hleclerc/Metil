#ifndef METHODWRITER_H
#define METHODWRITER_H

#include "DynamicLibrary.h"
#include "BasicVec.h"
#include "Mos.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
class MethodWriter {
public:
    MethodWriter( Type *type_0, Type *type_1, Type *type_2, const MethodWriter *parent = 0 );

    MethodWriter &operator<<( const String &str );
    void beg_def( const String &def_name );
    void end_def();
    int nb_types() const;
    void write_to( String &os );
    void add_include( const String &include );
    void add_preliminary( const String &txt ); ///< after includes and namespace
    void add_type_decl( const String &name ); ///< add declaration for type "name" and look if there's a declaration somewhere


    static String def_str( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static String decl_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static String symb_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2, bool cpp );
    static DynamicLibrary &get_lib_for_types( Type *type_0, Type *type_1, Type *type_2, const char *dep_file );
    static void make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 );

    String preliminary;
    String code;
    StringWithSepInCppLineMaker n;
    Type *type[ 3 ];
    BasicVec<String> includes;
    BasicVec<String> ext_types;
    bool os_defined;
};

typedef void MethodMaker( MethodWriter &mw, const Mos *mos, const String &ret = "return " );

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODWRITER_H
