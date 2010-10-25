#ifndef VAL_H
#define VAL_H

#include "CString.h"
#include "BasicVec.h"
#include "File.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Val.cpp
#endif

namespace Metil {

class ValItem;

///
class Val {
public:
    Val();
    Val( Int32 val );
    Val( Int64 val );
    Val( Int32 num, Int32 den );
    Val( Int64 num, Int64 den );
    Val( const CString &nb, int base ); /// construct a number (integer or rationnal) (3/4+5 won't work).
    Val( Float32 val );
    Val( Float64 val );
    Val( const CString &cpp, const CString &tex = CString() );
    Val( const ValItem *op );

    Val( const Val &ex );
    Val &operator=( const Val &ex );

    ~Val();

    // display
    void write_to_stream( Stream &os ) const;

    void get_type_name( Stream &os ) const;
    void get_tiny_repr( Stream &os ) const;

    void write_dot( Stream &os, bool want_parents = false ) const; // graphviz
    void write_tex( Stream &os ) const;

    void display_dot( const String &base_filename = ".res", bool want_parents = false ) const; // graphviz
    void display_tex( const String &base_filename = ".res", bool non_blocking = false ) const;

    // info
    bool is_a_Number() const;
    operator double() const;
    operator long  () const;

    int poly_deg( const BasicVec<Val> &variables ) const; /// total degree resp to variables (x*y -> 2 if {x,y} \subset variable). return -1 if *this == 0. returns -2 if not a polynomial.

    // methods
    Val operator+( const Val &ex ) const;
    Val operator-( const Val &ex ) const;
    Val operator*( const Val &ex ) const;
    Val operator/( const Val &ex ) const;

    Val operator-() const;

    Val diff( const Val &variable ) const;
    Val subs( const Val &from, const Val &to ) const;
    Val subs( const BasicVec<Val> &from, const BasicVec<Val> &to ) const;

    // functions
    friend Val cos ( const Val &ex );
    friend Val sin ( const Val &ex );
    friend Val sqrt( const Val &ex );
    friend Val log ( const Val &ex );
    friend Val exp ( const Val &ex );
    friend Val abs ( const Val &ex );

    friend Val pow( const Val &a, const Val &b );

    friend BasicVec<Val> diff( const BasicVec<Val> &expressions, const Val &variable ); // get derivatives of expr respestive to variable
    friend BasicVec<Val> subs( const BasicVec<Val> &expressions, const BasicVec<Val> &from, const BasicVec<Val> &to ); //

    // attribute
    const ValItem *op;
};

template<class T> Val operator+( const T &a, const Val &b ) { return Val( a ) + b; }
template<class T> Val operator-( const T &a, const Val &b ) { return Val( a ) - b; }
template<class T> Val operator*( const T &a, const Val &b ) { return Val( a ) * b; }
template<class T> Val operator/( const T &a, const Val &b ) { return Val( a ) / b; }
template<class T> Val       pow( const T &a, const Val &b ) { return pow( Val( a ), b); }

template<class T> Val operator+( const Val &a, const T &b ) { return a + Val( b ); }
template<class T> Val operator-( const Val &a, const T &b ) { return a - Val( b ); }
template<class T> Val operator*( const Val &a, const T &b ) { return a * Val( b ); }
template<class T> Val operator/( const Val &a, const T &b ) { return a / Val( b ); }
template<class T> Val       pow( const Val &a, const T &b ) { return pow(a, Val( b )); }

Val sqrt( int      a );
/*Val sqrt( unsigned a );*/ /// problème sur une machine 32 bits pour définir Val( unsigned int )

}

#endif // VAL_H
