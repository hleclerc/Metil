#ifndef AVOID_GEN
#ifndef CPPPARSER_H
#define CPPPARSER_H

#include "BasicVec.h"
#include "DefStr.h"
#include "Dout.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
*/
struct CppParser {
    typedef std::string String;
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

    void write_defi_type( std::ostream &os );
    void write_defi_meth( std::ostream &os );

    String current_file;
    int    current_line;
    BasicVec<String> bas;
    BasicVec<String> ref;
    BasicVec<String> cst;
    BasicSplittedVec<DefStr,64> gen;
    BasicSplittedVec<DefStr,64> def;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // CPPPARSER_H
#endif // AVOID_GEN
