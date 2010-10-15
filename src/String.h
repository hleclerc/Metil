#ifndef STRING_H
#define STRING_H

#include "Val.h"
#include "Dout.h"
#include "NewString.h"

BEG_METIL_NAMESPACE;

/**
*/
struct String : public Level1::MO {
    struct Endl  { void write_str( String &os ) const; }; ///< @see endl
    struct Flsh  { void write_str( String &os ) const; }; ///< @see flush

    // init
    String( const MO &o ) : MO( o ) {}
    String() { type = &Level1::metil_type_cst_VoidString; }
    String( const String &s ) : MO( CM_1( copy, s ) ) {}
    String( const char   *a ) { type = &Level1::metil_type_cst_ConstCharPtr; data = (void *)a; }
    String( char          v ) { type = &Level1::metil_type_cst_ConstCharPtr; data = char_ptr + 2 * (unsigned char)v; } ///< *this will be a single char
    String( const NewString &v ) { type = &Level1::metil_type_bas_OwcpString  ; data = v.data; } ///< *this will be a single char

    template<class T>
    String( const T &val ) { type = &Level1::metil_type_cst_VoidString; operator<<( val ); }

    // =
    String &operator=( const String &s ) {
        MO r = CM_1( copy, s );
        CM_1( del, *this );
        data = r.data;
        type = r.type;
        return *this;
    }

    // destroy
    ~String() { CM_1( del, *this ); }

    // +
    String operator+( const String &b ) const { return CM_2( append, *this, b ); }
    String operator+( const char   *b ) const { return *this + String( b ); }
    String operator+( char          b ) const { return *this + String( b ); }

    // +=
    template<class T>
    String &operator+=( const T &val ) { return *this << val; }

    // ==
    Val operator==( const String &b ) const { return CM_2( equal, *this, b ); }
    Val operator==( char b ) const { return operator==( String( b ) ); }

    // <<
    String &operator<<( const char *s ) { CM_2( self_append, *this, MO( (char *)s, &Level1::metil_type_cst_ConstCharPtr ) ); return *this; }
    String &operator<<(       char *s ) { TODO; return *this; }
    String &operator<<(       char  s ) { CM_2( self_append, *this, MO( char_ptr + 2 * (unsigned char)s, &Level1::metil_type_cst_ConstCharPtr ) ); return *this; }
    String &operator<<( MO          s ) { CM_2( self_append, *this, s ); return *this; }

    template<class T>
    String &operator<<( const T &val ) { val.write_str( *this ); return *this; }

    #define DECL_SELF_OP_POD( T ) String &operator<<( T v ) { CM_2( self_append, *this, Level1::REF_Number( v ) ); return *this; }
    DECL_SELF_OP_POD( SI8   );
    DECL_SELF_OP_POD( SI16  );
    DECL_SELF_OP_POD( SI32  );
    DECL_SELF_OP_POD( SI64  );
    DECL_SELF_OP_POD( PI8   );
    DECL_SELF_OP_POD( PI16  );
    DECL_SELF_OP_POD( PI32  );
    DECL_SELF_OP_POD( PI64  );
    DECL_SELF_OP_POD( FP32  );
    DECL_SELF_OP_POD( FP64  );
    DECL_SELF_OP_POD( FP80  );
    #undef DECL_SELF_OP_POD


    // methods
    Val size() const { return CM_1( size, *this ); }
    const char *c_str() { return (const char *)CM_1( ptr_z, *this ); }
    void flush() { CM_1( flush, *this ); }
    void write_separator( int num );
    Val find( const String &str ) const { return CM_2( find, *this, str ); } ///< return index of first str found in this. Else, return -1
    String beg_upto( const Val &s ) const { return CM_2( beg_upto, *this, s ); } ///< "abcd".beg_upto( 1 ) -> "a"
    String end_from( const Val &s ) const { return CM_2( end_from, *this, s ); } ///< "abcd".beg_upto( 1 ) -> "a"
    String replace( const String &a, const String &b ) const;
    String &write( const void *ptr, ST len ) { CM_1( write, *this, ptr, len ); return *this; }
    Val begins_by( const String &str ) const;
    Val ends_with( const String &str ) const;

    operator bool() const { return CM_1( convert_to_Bool, *this ); }
    operator SI32() const { return CM_1( convert_to_SI32, *this ); }
    operator SI64() const { return CM_1( convert_to_SI64, *this ); }
    operator FP32() const { return CM_1( convert_to_FP32, *this ); }
    operator FP64() const { return CM_1( convert_to_FP64, *this ); }
    operator FP80() const { return CM_1( convert_to_FP80, *this ); }

    // static attributes
    static Endl endl; ///< file << String::endl; will diplay a carriage return and flush the file
    static Flsh flsh; ///< file << String::flsh; will flush the file
    static char char_ptr[]; ///< storage...
};

inline String operator+( char        a, const String &b ) { return String( a ) + b; }
inline String operator+( const char *a, const String &b ) { return String( a ) + b; }

extern String cout;
extern String cerr;
extern String cin ;

/**
  @brief I/O file
*/
struct File : public String {
    File( String filename, String mode = "r" );
};

/**
  @brief I/O file
*/
struct Socket : public String {
    Socket( int socket_id );
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

