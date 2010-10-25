/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef METIL_STRING_H
#define METIL_STRING_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file String.cpp
#endif

#include "CommonFunctions.h"

namespace Metil {

/**
    contains a C compatible string (ended by a \0)
    data() returns this C compatible string

	@author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class String {
public:
    struct Size {};
    struct Rese {};

    String();
    String( Size, int new_size ); // start with size() = new_size and a \0 at the end.
    String( char c );
    String( const char *c );
    String( const char *beg, const char *end );

    template<class T>
    String( const T &val );

    String( const String &c );
    String &operator=( const String &c );
    String &operator=( const char *c );
    String &operator=( char c );

    ~String();

    operator const char *() const { return d; }

    operator bool() const;

    char &operator[]( int i ) { return d[ i ]; }
    char operator[]( int i ) const { return d[ i ]; }

    int size() const { return s; }

    const char *data() const { return d; }
    char *data() { return d; }

    void reserve( int new_size );
    void resize ( int new_size );
    void reserve_room_for( int room_size );

    String &operator+=( const char *o );
    String &operator+=( const String &o );
    String &operator+=( char o );

    String operator+( const char *o ) const;
    String operator+( const String &o ) const;
    String operator+( char o ) const;

    friend String operator+( const char *a, const String &b );
    friend String operator+( char a, const String &b );

    bool operator==( const char *o ) const;
    bool operator==( const String &o ) const;
    bool operator==( char o ) const;

    friend bool operator==( const char *a, const String &b );
    friend bool operator==( char a, const String &b );

    bool operator!=( const char *o ) const;
    bool operator!=( const String &o ) const;
    bool operator!=( char o ) const;

    friend bool operator!=( const char *a, const String &b );
    friend bool operator!=( char a, const String &b );

    String lstrip( int nb_char_to_remove_at_the_beg ) const; /// String("abcde").lstrip(2) -> cde
    String rstrip( int nb_char_to_remove_at_the_end ) const; /// String("abcde").rstrip(1) -> abcd

    String rstrip( char c ) const; /// String("abcdee").rstrip('e') -> abcd

    void rstrip_inplace( char c ); /// String res = "abcdee"; res.inplace_rstrip('e'); res -> abcd

    int rfind( char c ) const;

    bool get_line( int &p, String &line ) const; /// returns false if impossible to get a new line (end of string)

    void reset( char *data, int size = 0, int rese = 0 ); /// change internal data without free(...) of old one -> use with caution (useful with realloc)

    bool starts_with( char v ) const;
    bool ends_with  ( char v ) const;

    bool starts_with( const char *v ) const;
    bool ends_with  ( const char *v ) const;

    bool contains( const char *v ) const;

    bool operator<( const String &s ) const;

    void write_to_stream ( class Stream &os ) const;
    bool read_from_stream( class Stream &os );

    virtual void write( const void *data, int size );
    virtual void write( char data );

    static int strlen( const char *a );
    static int strcmp( const char *a, const char *b );
    static int strncmp( const char *a, const char *b, int n );

    friend class File;
    friend class CString;
private:
    char *d;
    int s, r;
};

} // namespace Metil

#include "StringStream.h"

namespace Metil {

template<class T>
String::String( const T &val ) {
    StringStream<String> ss;
    ss << val;
    d = ss.str.d;
    s = ss.str.s;
    r = ss.str.r;
    ss.str.d = 0;
}

} // namespace Metil

#endif
