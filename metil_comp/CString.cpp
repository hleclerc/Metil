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

#include "CString.h"
#include "String.h"
#include "Stream.h"

#include <string.h> // C std
#include <stdlib.h> // C std

namespace Metil {

CString::CString() : _data( const_cast<char *>( "" ) ), _size( 0 ), _owne( false ) {
}

CString::CString( const char *c ) : _data( const_cast<char *>( c ) ), _size( strlen( c ) ), _owne( false ) {
}

struct CharPtr {
    CharPtr() {
        for(int i=0;i<256;++i) {
            d[ 2 * i + 0 ] = i;
            d[ 2 * i + 1 ] = 0;
        }
    }
    const char *operator()( char c ) const {
        return d + 2 * c;
    }
    char d[ 256 * 2 ];
};

CString::CString( char c ) : _size( 1 ), _owne( false ) {
    static CharPtr cp;
    _data = const_cast<char *>( cp( c ) );
}

CString::CString( const char *beg, const char *end ) : _owne( true ) {
    if ( beg >= end ) {
        _data = const_cast<char *>( "" );
        _size = 0;
        return;
    }
    _size = end - beg;
    _data = (char *)malloc( _size + 1 );
    strncpy( _data, beg, _size );
    _data[ _size ] = 0;
}

CString::CString( const CString &c ) : _size( c._size ), _owne( c._owne ) {
    if ( _owne ) {
        _data = (char *)malloc( _size + 1 );
        strncpy( _data, c._data, _size + 1 );
    } else
        _data = c._data;
}

CString &CString::operator=( const CString &c ) {
    if ( _owne )
        free( _data );
    //
    _owne = c._owne;
    _size = c._size;
    if ( _owne ) {
        _data = (char *)malloc( _size + 1 );
        strncpy( _data, c._data, _size + 1 );
    } else
        _data = c._data;
    return *this;
}

CString::CString( Owning, int size ) : _data( (char *)malloc( size + 1 ) ), _size( size ), _owne( true ) {
    _data[ size ] = 0;
}

CString::~CString() {
    if ( _owne )
        free( _data );
}

int CString::size() const {
    return _size;
}

CString &CString::operator+=( const char *o ) {
    write( o, strlen( o ) );
    return *this;
}

CString &CString::operator+=( const CString &o ) {
    write( o._data, o.size() );
    return *this;
}

CString &CString::operator+=( char o ) {
    write( o );
    return *this;
}

void CString::write_to_stream( class Stream &os ) const {
    os.write( _data, _size );
}

bool CString::empty() const {
    return not _size;
}

CString CString::operator+( const char *o ) const {
    int os = _size, ns = strlen( o );
    CString res( Owning(), os + ns );
    strncpy( res._data +  0, _data, os );
    strncpy( res._data + os,     o, ns );
    return res;
}

CString CString::operator+( const CString &o ) const {
    int os = _size, ns = o.size();
    CString res( Owning(), os + ns );
    strncpy( res._data +  0,   _data, os );
    strncpy( res._data + os, o._data, ns );
    return res;
}

CString CString::operator+( char o ) const {
    int os = _size;
    CString res( Owning(), os + 1 );
    strncpy( res._data, _data, os );
    res._data[ os + 0 ] = o;
    return res;
}

CString operator+( const char *a, const CString &b ) {
    int a_s = strlen( a ), b_s = b.size();
    CString res( CString::Owning(), a_s + b_s );
    strncpy( res._data + 0  ,       a, a_s );
    strncpy( res._data + a_s, b._data, b_s );
    res._data[ a_s + b_s ] = 0;
    return res;
}

CString operator+( char a, const CString &b ) {
    int b_s = b.size();
    CString res( CString::Owning(), 1 + b_s );
    res._data[ 0 ] = a;
    strncpy( res._data + 1, b._data, b_s );
    return res;
}

bool CString::operator==( const char *o ) const {
    return strcmp( _data, o ) == 0;
}

bool CString::operator==( const CString &o ) const {
    return _size == o._size and strncmp( _data, o._data, _size ) == 0;
}

bool CString::operator==( char o ) const {
    return _data[ 0 ] == o and _data[ 1 ] == 0;
}

bool operator==( const char *a, const CString &b ) {
    return strcmp( a, b._data ) == 0;
}

bool operator==( char a, const CString &b ) {
    return b._data[ 0 ] == a and b._data[ 1 ] == 0;
}

bool CString::operator!=( const char *o ) const {
    return strcmp( _data, o );
}

bool CString::operator!=( const CString &o ) const {
    return _size != o._size or strncmp( _data, o._data, _size );
}

bool CString::operator!=( char o ) const {
    return _data[ 0 ] != o or _data[ 1 ];
}

bool operator!=( const char *a, const CString &b ) {
    return strcmp( a, b._data );
}

bool operator!=( char a, const CString &b ) {
    return b._data[ 0 ] != a or b._data[ 1 ];
}

CString CString::lstrip( int nb_char_to_remove_at_the_beg ) const {
    return CString( _data + nb_char_to_remove_at_the_beg, _data + _size );
}

CString CString::rstrip( int nb_char_to_remove_at_the_end ) const {
    return CString( _data, _data + _size - nb_char_to_remove_at_the_end );
}

int CString::rfind( char c ) const {
    int i = _size;
    while ( --i >= 0 )
        if ( _data[ i ] == c )
            return i;
    return i;
}

bool CString::operator<( const CString &o ) const {
    return strcmp( _data, o._data ) < 0;
}

bool CString::starts_with( char v ) const {
    return _data[ 0 ] == v;
}

bool CString::starts_with( const char *v ) const {
    return strncmp( _data, v, strlen( v ) ) == 0;
}

bool CString::ends_with( char v ) const {
    return _size and _data[ _size - 1 ] == v;
}

bool CString::ends_with( const char *v ) const {
    int v_size = strlen( v );
    return _size >= v_size and strncmp( _data + _size - v_size, v, v_size ) == 0;
}

bool CString::contains( const char *v ) const {
    for(const char *b=_data;*b;++b) {
        for(const char *p=v,*c=b;;++p,++c) {
            if ( not *p )
                return true;
            if ( *p != *c )
                break;
        }
    }
    return false;
}

CString::operator bool() const {
    return not empty();
}

void CString::write( const void *o, int ns ) {
    int os = _size;
    if ( _owne )
        _data = (char *)realloc( _data, os + ns + 1 );
    else {
        char *od = _data;
        _data = (char *)malloc( os + ns + 1 );
        strncpy( _data, od, os );
        _owne = true;
    }
    strncpy( _data + os, (const char *)o, ns );
    _data[ os + ns ] = 0;
    _size += ns;
}

void CString::write( char o ) {
    int os = _size;
    if ( _owne )
        _data = (char *)realloc( _data, os + 2 );
    else {
        char *od = _data;
        _data = (char *)malloc( os + 2 );
        strncpy( _data, od, os );
        _owne = true;
    }
    _data[ os + 0 ] = o;
    _data[ os + 1 ] = 0;
    _size += 1;
}

bool CString::get_line( int &p, String &line ) const {
    if ( not _data[ p ] )
        return false;
    int op = p;
    while ( _data[ p ] != 0 and _data[ p ] != '\n' )
        ++p;
    line.resize( p - op );
    strncpy( line.d, _data + op, p - op );
    p += ( _data[ p ] == '\n' );
    return true;
}

void CString::reserve( int new_size ) {
    if ( _owne )
        _data = (char *)realloc( _data, new_size + 1 );
    else {
        char *od = _data;
        _data = (char *)malloc( new_size + 1 );
        strncpy( _data, od, _size + 1 );
        _owne = true;
    }
}

void CString::reserve_room_for( int room_size ) {
    reserve( _size + room_size );
}

}
