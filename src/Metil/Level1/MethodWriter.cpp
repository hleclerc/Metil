#include "CompilationEnvironment.h"
#include "MethodFinder.h"
#include "StringHelp.h"
#include "../System.h"

#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

MethodWriter::MethodWriter( MethodWriter *parent ) : n( parent ? parent->n.string : code ), parent( parent ) {
    for( int i = 0; i < nb_args_max; ++i )
        type[ i ] = 0;
    ret_ins = "return ";
    machine_type = MachineId::Cpu;
    add_include( "Metil/Level1/Type.h" );
}

MethodWriter &MethodWriter::operator<<( const String &str ) {
    if ( parent )
        return parent->operator<<( str );
    code << str;
    return *this;
}

void MethodWriter::add_include( const String &include ) {
    if ( parent )
        parent->add_include( include );
    else if ( not includes.contains( include ) )
        includes << include;
}

void MethodWriter::add_preliminary( const String &txt ) {
    if ( parent )
        parent->add_preliminary( txt );
    else
        preliminary << txt;
}

void MethodWriter::add_type_decl( const String &name ) {
    if ( parent )
        parent->add_type_decl( name );
    else {
        if ( ext_types.contains( name ) )
            return;
        ST p = name.find( '_' );
        String cons = p >= 0 ? name.beg_upto( p ) : name;
        ext_types << name;
        add_include( "Metil/Level1/TypeConstructor_" + cons + ".h" );
        add_preliminary( "DECL_AND_DEFI_TYPE( " + cons + ", " + name + " );\n" );
    }
}

bool MethodWriter::get_os_defined() const {
    if ( parent )
        return parent->get_os_defined();
    return os_defined;
}

void MethodWriter::set_os_defined( bool v ) {
    if ( parent )
        parent->set_os_defined( v );
    else
        os_defined = v;
}

void MethodWriter::beg_def( const String &def_name ) {
    ASSERT( parent == 0, "beg_def should be done in main MethodWriter" );
    code << "__extern_C__ ";
    code << decl_of( def_name, type[ 0 ], type[ 1 ], type[ 2 ] ) << " {\n";
    os_defined = false;
}

void MethodWriter::end_def() {
    ASSERT( parent == 0, "end_def should be done in main MethodWriter" );
    code << "}\n\n";
}

StringWithSepInCppLineMaker MethodWriter::ret() {
    n.string << ret_ins;
    return n.string;
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
    typename MF::Item *item = MF::find_item( mw.get_type( 0 ), mw.get_type( 1 ), mw.get_type( 2 ), false );
    if ( item and item->gene and not item->meth ) {
        mw.beg_def( MethodName::get_name() );
        item->gene( mw );
        mw.end_def();
    }
}


void MethodWriter::make_cpp_for_types( const String cpp_name, Type *type_0, Type *type_1, Type *type_2 ) {
    MethodWriter mw;
    mw.type[ 0 ] = type_0;
    mw.type[ 1 ] = type_1;
    mw.type[ 2 ] = type_2;
    mw.arg[ 0 ] = "a";
    mw.arg[ 1 ] = "b";
    mw.arg[ 2 ] = "c";
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
    // filename
    String bas_name = "gen_met_for";
    if ( type_0 ) bas_name << "__" << type_0->name;
    if ( type_1 ) bas_name << "__" << type_1->name;
    if ( type_2 ) bas_name << "__" << type_2->name;

    CompilationEnvironment &ce = CompilationEnvironment::get_main_compilation_environment();
    String lib_name = ce.lib_for( bas_name, true );

    // already loaded ?
    static std::map<String,DynamicLibrary> libs;
    std::map<String,DynamicLibrary>::iterator iter = libs.find( lib_name );
    if ( iter != libs.end() )
        return iter->second;

    // if lib exists, load it
    DynamicLibrary &res = libs[ lib_name ];
    SI64 date_dep = last_modification_time_or_zero_of_file_named( dep_file );
    SI64 date_lib = last_modification_time_or_zero_of_file_named( lib_name );
    if ( date_lib <= date_dep ) { // make cpp, compile and load it
        String cpp_name = ce.cpp_for( bas_name );
        make_cpp_for_types( cpp_name, type_0, type_1, type_2 );

        CompilationEnvironment loc_ce( &ce );
        loc_ce.add_CPPFLAG( "-DMETIL_GENE_DYLIB", cpp_name );
        if ( loc_ce.make_lib( lib_name, cpp_name, true ) )
            ERROR( "Pb during compilation of %s", cpp_name.c_str() );
    }

    res.open( lib_name );
    if ( not res )
        ERROR( "Error during lib load %s", res.error().c_str() );

    //
    return res;
}

bool MethodWriter::call_gene( const String &method, Type *type_0, const Mos &arg_0, const String &ret, bool abort_if_not_found ) {
    MethodWriter nw( this );
    nw.type[ 0 ] = type_0;
    nw.arg [ 0 ] = arg_0;
    nw.ret_ins = ret.size() ? ret : ret_ins;
    #define DECL_MET( T, N ) \
        if ( method == #N ) { \
            typedef MethodFinder<MethodName_##N> MF; \
            if ( MF::Item *item = MF::find_item( type_0, 0, 0, abort_if_not_found, true ) ) { \
                item->gene( nw ); \
                return true; \
            } \
            return false; \
        }
    #include "DeclMethodsUnary.h"
    #undef DECL_MET
    ERROR( "unknown method name %s (assuming nb_arg == 1)", method.c_str() );
    return false;
}

bool MethodWriter::call_gene( const String &method, Type *type_0, Type *type_1, const Mos &arg_0, const Mos &arg_1, const String &ret, bool abort_if_not_found ) {
    MethodWriter nw( this );
    nw.type[ 0 ] = type_0;
    nw.type[ 1 ] = type_1;
    nw.arg [ 0 ] = arg_0;
    nw.arg [ 1 ] = arg_1;
    nw.ret_ins = ret.size() ? ret : ret_ins;
    #define DECL_MET( T, N ) \
        if ( method == #N ) { \
            typedef MethodFinder<MethodName_##N> MF; \
            if ( MF::Item *item = MF::find_item( type_0, type_1, 0, abort_if_not_found, true ) ) { \
                item->gene( nw ); \
                return true; \
            } \
            return false; \
        }
    #include "DeclMethodsBinary.h"
    #undef DECL_MET
    ERROR( "unknown method name %s (assuming nb_arg == 2)", method.c_str() );
    return false;
}

END_METIL_LEVEL1_NAMESPACE;
