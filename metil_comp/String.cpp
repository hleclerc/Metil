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

#include <string.h> // C std
#include <stdlib.h> // C std

#include "String.h"
#include "Stream.h"

namespace Metil {

String::String() : d( NULL ), s( 0 ), r( 0 ) {
}

String::String( Size, int new_size ) : s( new_size ), r( s ) {
    d = (char *)malloc( new_size + 1 );
    d[ s ] = 0;
}

String::String( const char *c ) : s( strlen( c ) ), r( s ) {
    d = (char *)malloc( s + 1 );
    strncpy( d, c, s + 1 );
}

String::String( char c ) : s( 1 ), r( 1 ) {
    d = (char *)malloc( 2 );
    d[ 0 ] = c;
    d[ 1 ] = 0;
}

String::String( const char *beg, const char *end ) : s( end - beg ), r( s ) {
    d = (char *)malloc( s + 1 );
    strncpy( d, beg, s );
    d[ s ] = 0;
}

String::String( const String &c ) : s( c.s ), r( s ) {
    if ( c.s ) {
        d = (char *)malloc( s + 1 );
        strncpy( d, c.d, s + 1 );
    } else
        d = NULL;
}

String &String::operator=( const String &c ) {
    if ( c.s ) {
        resize( c.s );
        strncpy( d, c.d, s + 1 );
    } else
        s = 0;
    return *this;
}

String &String::operator=( const char *c ) {
    resize( strlen( c ) );
    strncpy( d, c, s );
    return *this;
}

String &String::operator=( char c ) {
    resize( 1 );
    d[ 0 ] = c;
    return *this;
}

String::~String() {
    if ( d )
        free( d );
}

void String::reserve( int new_resa ) {
    if ( new_resa <= r )
        return;
    r = new_resa;
    if ( r )
        d = (char *)realloc( d, r + 1 );
}

void String::resize( int new_size ) {
    reserve( new_size );
    s = new_size;
    if ( d )
        d[ new_size ] = 0;
}

void String::reserve_room_for( int room_size ) {
    reserve( size() + room_size );
}

String::operator bool() const {
    return s;
}


String &String::operator+=( const char *o ) {
    int o_s = strlen( o );
    reserve( s + o_s );
    for(int i=s,j=0;j<=o_s;++i,++j)
        d[ i ] = o[ j ];
    s += o_s;
    return *this;
}

String &String::operator+=( const String &o ) {
    reserve( s + o.s );
    for(int i=s,j=0;j<=o.s;++i,++j)
        d[ i ] = o.d[ j ];
    s += o.s;
    return *this;
}

String &String::operator+=( char o ) {
    if ( s >= r ) // no room ?
        reserve( 2 * ( s + 1 ) );
    d[ s + 0 ] = o;
    d[ s + 1 ] = 0;
    ++s;
    return *this;
}

void String::write_to_stream( class Stream &os ) const {
    os.write( d, s );
}

String String::operator+( const char *o ) const {
    int o_s = strlen( o );
    String res( Size(), s + o_s );
    strncpy( res.d + 0, d, s   );
    strncpy( res.d + s, o, o_s );
    return res;
}

String String::operator+( const String &o ) const {
    String res( Size(), s + o.s );
    strncpy( res.d + 0, d  , s   );
    strncpy( res.d + s, o.d, o.s );
    return res;
}

String String::operator+( char o ) const {
    String res( Size(), s + 1 );
    strncpy( res.d, d, s );
    res.d[ s ] = o;
    return res;
}

String operator+( const char *a, const String &b ) {
    int a_s = strlen( a );
    String res( String::Size(), a_s + b.s );
    strncpy( res.d + 0  , a  , a_s );
    strncpy( res.d + a_s, b.d, b.s );
    return res;
}

String operator+( char a, const String &b ) {
    String res( String::Size(), b.s + 1 );
    res.d[ 0 ] = a;
    strncpy( res.d + 1, b.d, b.s );
    return res;
}

bool String::operator==( const char *o ) const {
    return s == (int)strlen( o ) and strncmp( d, o, s ) == 0;
}

bool String::operator==( const String &o ) const {
    return s == o.s and strncmp( d, o.d, s ) == 0;
}

bool String::operator==( char o ) const {
    return s == 1 and d[ 0 ] == o;
}

bool operator==( const char *a, const String &b ) {
    return b.s == (int)strlen( a ) and strncmp( b.d, a, b.s ) == 0;
}

bool operator==( char a, const String &b ) {
    return b.s == 1 and b.d[ 0 ] == a;
}

bool String::operator!=( const char *o ) const {
    return s != (int)strlen( o ) or strncmp( d, o, s );
}

bool String::operator!=( const String &o ) const {
    return s != o.s or strncmp( d, o.d, s );
}

bool String::operator!=( char o ) const {
    return s != 1 or d[ 0 ] != o;
}

bool operator!=( const char *a, const String &b ) {
    return b.s != (int)strlen( a ) or strncmp( b.d, a, b.s );
}

bool operator!=( char a, const String &b ) {
    return b.s != 1 and b.d[ 0 ] != a;
}

String String::lstrip( int nb_char_to_remove_at_the_beg ) const {
    if ( nb_char_to_remove_at_the_beg >= s )
        return String();
    return String( d + nb_char_to_remove_at_the_beg, d + s );
}

String String::rstrip( int nb_char_to_remove_at_the_end ) const {
    if ( nb_char_to_remove_at_the_end >= s )
        return String();
    return String( d, d + s - nb_char_to_remove_at_the_end );
}

String String::rstrip( char c ) const {
    String res = *this;
    res.rstrip_inplace( c );
    return res;
}

void String::rstrip_inplace( char c ) {
    while ( s and d[ s - 1 ] == c ) --s;
}


int String::rfind( char c ) const {
    int i = s;
    while ( --i >= 0 )
        if ( d[ i ] == c )
            return i;
    return i;
}

bool String::operator<( const String &o ) const {
    if ( s < o.s )
        return true;
    if ( s > o.s )
        return false;
    for(int i=0;i<s;++i) {
        if ( d[ i ] < o.d[ i ] )
            return true;
        else if ( d[ i ] > o.d[ i ] )
            return false;
    }
    return false; // because ==
}

void String::reset( char *data, int size, int rese ) {
    s = ( size ? size : strlen( data ) );
    r = ( rese ? rese : s              );
    d = data;
}

int String::strlen( const char *a ) {
    return ::strlen( a );
}

int String::strcmp( const char *a, const char *b ) {
    return ::strcmp( a, b );
}

int String::strncmp( const char *a, const char *b, int n ) {
    return ::strncmp( a, b, n );
}

bool String::starts_with( char v ) const {
    return s and d[ 0 ] == v;
}

bool String::starts_with( const char *v ) const {
    return strncmp( d, v, strlen( v ) ) == 0;
}

bool String::ends_with( char v ) const {
    return s and d[ s-1 ] == v;
}

bool String::ends_with( const char *v ) const {
    int l = strlen( v );
    return s >= l and strncmp( d + s - l, v, l ) == 0;
}

bool String::get_line( int &p, String &line ) const {
    if ( not d[ p ] )
        return false;
    int op = p;
    while ( d[ p ] != 0 and d[ p ] != '\n' )
        ++p;
    line.resize( p - op );
    strncpy( line.d, d + op, p - op );
    p += ( d[ p ] == '\n' );
    return true;
}

bool String::contains( const char *v ) const {
    for(const char *b=d;*b;++b) {
        for(const char *p=v,*c=b;;++p,++c) {
            if ( not *p )
                return true;
            if ( *p != *c )
                break;
        }
    }
    return false;
}

void String::write( const void *data, int size ) {
    int old_size = s;
    resize( old_size + size );
    strncpy( d + old_size, (const char *)data, size );
}

void String::write( char data ) {
    int os = s;
    resize( os + 1 );
    d[ os ] = data;
}

bool String::read_from_stream( class Stream &os ) {
    return os.get_word( *this );
}

}
