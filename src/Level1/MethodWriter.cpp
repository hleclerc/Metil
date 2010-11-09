#include "CompilationEnvironment.h"
#include "MethodFinder.h"
#include "StringHelp.h"
#include "System.h"

#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

MethodWriter::MethodWriter( Type *type_0, Type *type_1, Type *type_2 ) : n( code ) {
    type[ 0 ] = type_0;
    type[ 1 ] = type_1;
    type[ 2 ] = type_2;
    includes << "Level1/Type.h";
}

MethodWriter &MethodWriter::operator<<( const String &str ) {
    code << str;
    return *this;
}

void MethodWriter::add_include( const String &include ) {
    if ( not includes.contains( include ) )
        includes << include;
}

void MethodWriter::add_preliminary( const String &txt ) {
    preliminary << txt;
}

void MethodWriter::beg_def( const String &def_name ) {
    code << "__extern_C__ ";
    code << decl_of( def_name, type[ 0 ], type[ 1 ], type[ 2 ] ) << " {\n";
}

void MethodWriter::end_def() {
    code << "}\n";
}

int MethodWriter::nb_types() const {
    return bool( type[ 0 ] ) + bool( type[ 1 ] ) + bool( type[ 2 ] );
}

void MethodWriter::write_to( String &os ) {
    StringWithSepInCppLineMaker on( os );
    for( int i = 0; i < includes.size(); ++i )
        on << "#include <" + includes[ i ] + ">";
    on << "";
    on << "#ifdef METIL_GENE_DYLIB";
    on << "#define __extern_C__ extern \"C\"";
    on << "#else";
    on << "#define __extern_C__";
    on << "#endif";
    on << "";
    on << "BEG_METIL_LEVEL1_NAMESPACE;";
    if ( preliminary.size() ) {
        on << "";
        on << preliminary;
    }
    on << "";
    on << code;
    on << "END_METIL_LEVEL1_NAMESPACE;";
}



String MethodWriter::def_str( const String &method_name, Type *type_0, Type *type_1, Type *type_2 ) {
    String res = "metil_def_";
    res << method_name;
    if ( type_0 or type_1 or type_2 )
        res << "__when";
    if ( type_0 ) res << "__a__is__" << type_0->name;
    if ( type_1 and type_0 ) res << "__and";
    if ( type_1 ) res << "__b__is__" << type_1->name;
    if ( type_2 and ( type_0 or type_1 ) ) res << "__and";
    if ( type_2 ) res << "__c__is__" << type_2->name;
    return res;
}

String MethodWriter::decl_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2 ) {
    String type;
    #define DECL_MET( T, N ) if ( method_name == #N ) type = #T
    #include "DeclMethods.h"
    #undef DECL_MET
    ASSERT( type.size(), "method '%s' not found", method_name.c_str() );

    // metil_def_...__when__...
    String def_name = def_str( method_name, type_0, type_1, type_2 );

    // if ( type == ... ) return ...;
    #include "MethodWriterDecl.h"

    ERROR( "-> %s", type.c_str() );
    return String();
}

String MethodWriter::symb_of( const String &method_name, Type *type_0, Type *type_1, Type *type_2, bool cpp ) {
    ASSERT( cpp == 0, "TODO : C++ name mangling" );
    return def_str( method_name, type_0, type_1, type_2 );

    //    // cpp mangling
    //    String type;
    //    #define DECL_MET( T, N ) if ( def_name == #N ) type = #T
    //    #include "DeclMethods.h"
    //    #undef DECL_MET
    //    ASSERT( type.size(), "method '%s' not found", def_name.c_str() );

    //    // if ( type == ... ) { args = ...; }
    //    String args;
    //    #include "MethodWriterSymb.h"

    //    ASSERT( args.size(), "-> %s", type.c_str() );
    //    String bas = "metil_def_" + def_name, res;
    //    res << "_ZN5Metil6Level1" << bas.size() << bas << args;
    //    return res;
}

template<class MethodName>
void try_to_generate( MethodWriter &mw ) {
    typedef MethodFinder<MethodName> MF;
    typename MF::Item *item = MF::find_item( mw.type[ 0 ], mw.type[ 1 ], mw.type[ 2 ], false );
    if ( item and item->gene and not item->meth ) {
        BasicVec<Mos> mos( "a", "b", "c" );
        mw.beg_def( MethodName::get_name() );
        item->gene( mw, mos.ptr(), "return " );
        mw.end_def();
    }
}


void MethodWriter::make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 ) {
    MethodWriter mw( type_0, type_1, type_2 );
    if ( type_0 ) type_0->constructor->default_mw( mw );
    if ( type_1 ) type_1->constructor->default_mw( mw );
    if ( type_2 ) type_2->constructor->default_mw( mw );

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
    c.close();

    // exec_cmd( "indent --k-and-r-style -brf " + cpp_name, false );
}

DynamicLibrary &MethodWriter::get_lib_for_types( Type *type_0, Type *type_1, Type *type_2, const char *dep_file ) {
    static std::map<SI64,DynamicLibrary> libs;
    SI64 n = type_0->number + ( SI64( type_1 ? type_1->number : 0 ) << 24 ) + ( SI64( type_2 ? type_2->number : 0 ) << 48 );
    std::map<SI64,DynamicLibrary>::iterator iter = libs.find( n );
    if ( iter != libs.end() )
        return iter->second;
    DynamicLibrary &res = libs[ n ];

    // filenames
    String bas_name = "gen_met_for";
    if ( type_0 ) bas_name << "__" << type_0->name;
    if ( type_1 ) bas_name << "__" << type_1->name;
    if ( type_2 ) bas_name << "__" << type_2->name;

    CompilationEnvironment &ce = CompilationEnvironment::get_main_compilation_environment();
    String lib_name = ce.lib_for( bas_name, true );

    // if lib exists, load it
    SI64 date_dep = last_modification_time_or_zero_of_file_named( dep_file );
    SI64 date_lib = last_modification_time_or_zero_of_file_named( lib_name );
    if ( date_lib <= date_dep ) { // make cpp, compile and load it
        String cpp_name = ce.cpp_for( bas_name );
        make_cpp_for_types( cpp_name, type_0, type_1, type_2 );

        CompilationEnvironment loc_ce( ce );
        loc_ce.add_CPPFLAG( "-DMETIL_GENE_DYLIB" );
        if ( loc_ce.make_lib( lib_name, cpp_name, true ) )
            ERROR( "Pb during compilation of %s", cpp_name.c_str() );
        //        String cmd = get_env( "METIL_CXX_CMD" );
        //        ASSERT( cmd.size(), "METIL_CXX_CMD is not defined in env var" );
        //        cmd << "  -g3 -fPIC -shared -o "  << lib_name << " "  << cpp_name;
        //        if ( exec_cmd( cmd ) )
        //            ERROR( "Pb during compilation of %s", cpp_name.c_str() );
    }

    res.open( lib_name );
    if ( not res )
        ERROR( "Error during lib load %s", res.error().c_str() );

    //
    return res;
}

END_METIL_LEVEL1_NAMESPACE;
