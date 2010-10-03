#ifndef STRING_H
#define STRING_H

#include "Type.h"
#include "Dout.h"

BEG_METIL_NAMESPACE;

struct String : public Level1::MO {
    struct Endl  { void write_str( String &os ) const; }; ///< @see endl
    struct Flsh  { void write_str( String &os ) const; }; ///< @see flush

    String() { type = &Level1::metil_type_cst_VoidString; }
    String( const char *a ) { data = (void *)a; type = &Level1::metil_type_cst_ConstCharPtr; }
    String( MO o ) : MO( o ) {}

    ~String() { CM_1( del, *this ); }


    // operator<<
    String &operator<<( const char *s ) { CM_2( self_append, *this, MO( (char *)s, &Level1::metil_type_cst_ConstCharPtr ) ); return *this; }
    String &operator<<(       char *s ) { TODO; return *this; }
    String &operator<<(       char  s ) { TODO; return *this; }
    String &operator<<( MO          s ) { CM_2( self_append, *this, s ); return *this; }

    //template<class T>
    // String &operator<<( const T &val ) { val.write_str( *this ); return *this; }

    void flush() { type->flush( *this ); }

    static Endl endl; ///< file << String::endl; will diplay a carriage return and flush the file
    static Flsh flsh; ///< file << String::flsh; will flush the file
};

extern String cout;
extern String cerr;
extern String cin ;

/**
  @brief I/O file
*/
struct File : public String {
    File( const String &filename, const String &mode = "r" );
};

#define PRINT( A ) \
    Metil::coutn << "  " << #A << " -> " << (A)
#define PRINTN( A ) \
    Metil::coutn << "  " << #A << " ->\n" << (A)

END_METIL_NAMESPACE;

// coutn, cerrn
#include "StringWithSepInCppLine.h"
BEG_METIL_NAMESPACE;
extern StringWithSepInCppLineMaker coutn;
extern StringWithSepInCppLineMaker cerrn;
END_METIL_NAMESPACE;

#endif // STRING_H

