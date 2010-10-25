#ifndef METHODWRITER_H
#define METHODWRITER_H

#include "DynamicLibrary.h"
#include "Mos.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
class MethodWriter {
public:
    MethodWriter( Type *type_0, Type *type_1, Type *type_2 );

    MethodWriter &operator<<( const String &str );
    void beg_def( const String &def_name );
    void end_def();
    int nb_types() const;
    void write_to( String &os );

    static String name_for( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static String c_name_for( const String &method_name, Type *type_0, Type *type_1, Type *type_2 );
    static DynamicLibrary &get_lib_for_types( Type *type_0, Type *type_1, Type *type_2 );
    static void make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 );

    String code;
    Type *type[ 3 ];
};

typedef void MethodMaker( MethodWriter &mw, Mos *mos );

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODWRITER_H
