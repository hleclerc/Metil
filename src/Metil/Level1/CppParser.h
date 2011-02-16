#ifndef AVOID_GEN
#ifndef CPPPARSER_H
#define CPPPARSER_H

#include "BasicVec.h"
#include "DefStr.h"

#include <map>

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
struct CppParser {
    typedef std::string String;
    struct TypeStr {
        TypeStr( String name = "" ) : name( name ) {
            subs = name.size() ? name.substr( 15 ) : "";
            cons = subs.substr( 0, subs.find( "_" ) );
        }
        bool operator==( const TypeStr &t ) const { return name == t.name; }
        String name;
        String cons;
        String subs;
    };
    struct VTCond {
        bool operator<( const VTCond &vt ) const {
            return vt.str() < str();
        }
        String str() const {
            String res = type;
            for( int i = 0; i < init.size(); ++i )
                res += init[ i ];
            return res;
        }
        String type;
        BasicVec<String> init;
    };

    CppParser();

    void parse( char *c );

    void write_decl( std::ostream &os );
    void write_defi( std::ostream &os, String h );

    bool err;
private:
    void metil_type_bas_( char *&c );
    void metil_type_ref_( char *&c );
    void metil_type_cst_( char *&c );

    void metil_gen_( char *&c );
    void metil_def_( char *&c );

    void write_defi_meth( std::ostream &os, const DefStr &def, bool gen, std::map<VTCond,String> &conds, std::map<String,String> &files );
    void write_defi_type( std::ostream &os );
    void write_defi_meth( std::ostream &os );

    String current_file;
    int    current_line;
    BasicVec<TypeStr> bas;
    BasicVec<TypeStr> ref;
    BasicVec<TypeStr> cst;
    BasicSplittedVec<DefStr,64> gen;
    BasicSplittedVec<DefStr,64> def;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // CPPPARSER_H
#endif // AVOID_GEN
