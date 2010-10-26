#include "MethodFinder.h"
#include "StringHelp.h"
#include "System.h"

#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

MethodWriter::MethodWriter( Type *type_0, Type *type_1, Type *type_2 ) {
    type[ 0 ] = type_0;
    type[ 1 ] = type_1;
    type[ 2 ] = type_2;
}

MethodWriter &MethodWriter::operator<<( const String &str ) {
    cout << str;
    code << str;
    return *this;
}

void MethodWriter::beg_def( const String &def_name ) {
    code << name_for( def_name, type[ 0 ], type[ 1 ], type[ 2 ] ) << " {\n";
}

void MethodWriter::end_def() {
    code << "}\n";
}

int MethodWriter::nb_types() const {
    return bool( type[ 0 ] ) + bool( type[ 1 ] ) + bool( type[ 2 ] );
}

void MethodWriter::write_to( String &os ) {
    StringWithSepInCppLineMaker on( os );
    on << "#include <Type.h>";
    on << "BEG_METIL_LEVEL1_NAMESPACE;";
    on << code;
    on << "END_METIL_LEVEL1_NAMESPACE;";
}




String MethodWriter::name_for( const String &def_name, Type *type_0, Type *type_1, Type *type_2 ) {
    String type;
    #define DECL_MET( T, N ) if ( def_name == #N ) type = #T
    #include "DeclMethods.h"
    #undef DECL_MET
    ASSERT( type.size(), "method '%s' not found", def_name.c_str() );

    // if ( type == ... ) return ...;
    #include "MethodWriterDecl.h"

    ERROR( "-> %s", type.c_str() );
    return String();
}

String MethodWriter::c_name_for( const String &method_name, Type *type_0, Type *type_1, Type *type_2 ) {
    return name_for( method_name, type_0, type_1, type_2 );
}

template<class MethodName>
void try_to_generate( MethodWriter &mw ) {
    typedef MethodFinder<MethodName> MF;
    typename MF::Item *item = MF::find_item( mw.type[ 0 ], mw.type[ 1 ], mw.type[ 2 ], false );
    if ( item and item->gene and not item->meth ) {
        BasicVec<Mos> mos( "a", "b", "c" );
        mw.beg_def( MethodName::get_name() );
        item->gene( mw, mos.ptr() );
        mw.end_def();
    }
}


void MethodWriter::make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 ) {
    MethodWriter mw( type_0, type_1, type_2 );
    #define DECL_MET( T, N ) try_to_generate<MethodName_##N>( mw )
    if ( mw.nb_types() == 1 ) {
        #include "DeclMethodsUnary.h"
    } else if ( mw.nb_types() == 2 ) {
        #include "DeclMethodsBinary.h"
    } else if ( mw.nb_types() == 3 ) {
        #include "DeclMethodsTernary.h"
    }
    #undef DECL_MET

    File c( cpp_name, "w" );
    mw.write_to( c );
}

DynamicLibrary &MethodWriter::get_lib_for_types( Type *type_0, Type *type_1, Type *type_2 ) {
    static std::map<SI64,DynamicLibrary> libs;
    SI64 n = type_0->number + ( SI64( type_1 ? type_1->number : 0 ) << 24 ) + ( SI64( type_2 ? type_2->number : 0 ) << 48 );
    std::map<SI64,DynamicLibrary>::iterator iter = libs.find( n );
    if ( iter != libs.end() )
        return iter->second;
    DynamicLibrary &res = libs[ n ];

    // filename
    String bas_name = get_env( "METIL_COMP_DIR" );
    if ( not bas_name.size() )
        bas_name = "compilations";
    if ( not bas_name.ends_with("/") )
        bas_name << "/";
    bas_name << "gen_met_for";
    if ( type_0 ) bas_name << "__" << type_0->name;
    if ( type_1 ) bas_name << "__" << type_1->name;
    if ( type_2 ) bas_name << "__" << type_2->name;

    // if lib exists, load it
    String lib_name = bas_name + ".so";
    if ( not file_exists( lib_name ) ) { // make cpp, compile and load it
        String cpp_name = bas_name + ".cpp";
        make_cpp_for_types( cpp_name, type_0, type_1, type_2 );

        String cmd = get_env( "METIL_CXX_CMD" );
        ASSERT( cmd.size(), "METIL_CXX_CMD is not defined in env var" );
        cmd << " -shared -o "  << lib_name << " "  << cpp_name;
        if ( exec_cmd( cmd ) )
            ERROR( "Pb during compilation of %s", cpp_name.c_str() );
    }

    res.open( lib_name );
    if ( not res )
        ERROR( "Error durig lib lod %s", res.error().c_str() );

    //
    return res;
}

END_METIL_LEVEL1_NAMESPACE;
