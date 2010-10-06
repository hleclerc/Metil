#ifndef STRUCTCOMPACTOR_H
#define STRUCTCOMPACTOR_H

#include "TypeInformation.h"
#include "BasicVec.h"
#include "String.h"

BEG_METIL_NAMESPACE;

/**
*/
class StructCompactor {
public:
    CANNOT_BE_DERIVED;

    struct BasicProfile {
    };

    /// constructor for generic structure
    template<class T>
    StructCompactor( const T &inst, const String &name = "", int par_level = 0 ) : name( name ), pointed_type( 0 ), par_level( par_level ), int_type( 1 ) {
        inst.apply_bs( *this, BasicProfile() );
    }

    /// constructors for POD types
    #define SC_INIT( T ) \
        StructCompactor( const T &, const String &name = "", int par_level = 0 ) : type( TypeInformation<T>::type() ), name( name ), pointed_type( 0 ), par_level( par_level ), int_type( 0 ) {}
    SC_INIT( SI32 );
    SC_INIT( SI64 );
    SC_INIT( FP32 );
    SC_INIT( FP64 );
    #undef SC_INIT

    /// constructors for ptr types
    template<class T>
    StructCompactor( const BasicVec<T> &inst, const String &name = "", int par_level = 0 ) : name( name ), pointed_type( 0 ), par_level( par_level ), int_type( 0 ) { ///< generic structure
        pointed_type = NEW( StructCompactor, inst[ 0 ], name + '[' + char( 'i' + par_level ) + ']', par_level + 1 );
        type << "BasicVecRef<" << pointed_type->type << " >";
    }

    /// called from apply_bs
    template<class T>
    void apply( const String &name, const T &val ) { items << NEW( StructCompactor, val, name ); } ///< ptr

    // methods
    void make_decl( String &os, const String &sp = "" );
    void make_defi( String &os, const String &sp = "" );
    void make_file();
    void set_type( const char *t ) { type = t; }
    StructCompactor *base_str();
    String needed_alignement() const;
    bool is_POD() const;

private:
    void make_copy( String &os, const String &sp, const String &dst, const String &src, int par_lev );
    void make_push( String &os, const String &sp, const String &dst, int par_lev = 0, const String &suf = "", const String &n = "n" );

    BasicVec<StructCompactor *> items;
    String type;
    String name;
    StructCompactor *pointed_type; ///< if ptr (e.g. if BasicVec<...>)
    int par_level;
    bool int_type; ///< internal type
};


END_METIL_NAMESPACE;

#endif // STRUCTCOMPACTOR_H
