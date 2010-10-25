#ifndef CSTRING_H
#define CSTRING_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CString.cpp
#endif

#include "String.h"

namespace Metil {

/**
    constant string

    contains a C compatible string (ended by a \0)
    data() returns this C compatible string

    CString("toto") does not make any malloc

    @author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class CString {
public:
    struct Size {};

    CString();
    CString( char c );
    CString( const char *c ); /// assumes that c won't be deleted (ok in CString("...") ) !
    CString( const char *beg, const char *end );

    CString( const CString &c );
    CString &operator=( const CString &c );

    template<class T>
    CString( const T &val ) : _owne( true ) {
        StringStream<CString> s;
        s << val;
        _data = s.str._data;
        _size = s.str._size;
        s.str._owne = false;
    }

    ~CString();

    operator const char *() const { return _data; }

    char operator[]( int i ) const { return _data[ i ]; }

    int size() const;
    const char *data() const { return _data; }
    bool empty() const;

    operator bool() const;

    CString &operator+=( const char *o );
    CString &operator+=( const CString &o );
    CString &operator+=( char o );

    CString operator+( const char *o ) const;
    CString operator+( const CString &o ) const;
    CString operator+( char o ) const;

    friend CString operator+( const char *a, const CString &b );
    friend CString operator+( char a, const CString &b );

    bool operator==( const char *o ) const;
    bool operator==( const CString &o ) const;
    bool operator==( char o ) const;

    friend bool operator==( const char *a, const CString &b );
    friend bool operator==( char a, const CString &b );

    bool operator!=( const char *o ) const;
    bool operator!=( const CString &o ) const;
    bool operator!=( char o ) const;

    friend bool operator!=( const char *a, const CString &b );
    friend bool operator!=( char a, const CString &b );

    CString lstrip( int nb_char_to_remove_at_the_beg ) const; /// String("abcde").lstrip(2) -> cde
    CString rstrip( int nb_char_to_remove_at_the_end ) const; /// String("abcde").rstrip(1) -> abcd

    CString rstrip( char c ) const; /// String("abcdee").rstrip('e') -> abcd

    int rfind( char c ) const;

    bool get_line( int &p, String &line ) const; /// returns false if impossible to get a new_ line (end of string)

    bool starts_with( char v ) const;
    bool ends_with( char v ) const;

    bool starts_with( const char *v ) const;
    bool ends_with( const char *v ) const;

    bool contains( const char *v ) const;

    bool operator<( const CString &s ) const;

    void write_to_stream( class Stream &os ) const;

    virtual void reserve( int new_size );
    virtual void reserve_room_for( int room_size );

    virtual void write( const void *data, int size );
    virtual void write( char data );

    friend class File;
private:
    struct Owning {};
    CString( Owning, int size );

    char *_data;
    int   _size;
    bool  _owne;
};

}

#endif // CSTRING_H
