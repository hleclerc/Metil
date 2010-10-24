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

#ifndef METIL_STREAM_H
#define METIL_STREAM_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Stream.cpp
#endif

#include "TypeConfig.h"

namespace Metil {

class String;

/**

*/
class Stream {
public:
    /// @see endl
    struct Endl { void write_to_stream( Stream &os ) const; };
    /// @see flush
    struct Flsh { void write_to_stream( Stream &os ) const; };
    /**
        Example : \code cout << Stream::Spaces( 8 )
        -> push 8 spaces in Stream cout
    */
    struct Spaces { Spaces(int n):n(n) {} void write_to_stream( Stream &os ) const; int n; };
    
    Stream();
    virtual ~Stream();

    virtual char   get_char();
    virtual String get_word();
    virtual String get_line();
    virtual String get_left();

    virtual bool get_char( char   &data ) = 0;
    virtual bool get_word( String &word );
    virtual bool get_line( String &line );
    virtual bool get_left( String &left ); // whole remaining data (starting from tell)

    virtual Int64 tell() = 0; // position from the beginning
    virtual Int64 size() = 0; // size of the data in bytes
    virtual void seek( Int64 pos ) = 0; // change position in the file
    
    virtual void write( const void *data, int size ) = 0; // size in bytes
    virtual void write( char        data           ) = 0;

    virtual void write( Int8          data );
    virtual void write( Int16         data );
    virtual void write( Int32         data );
    virtual void write( Int64         data );
    virtual void write( Unsigned8     data );
    virtual void write( Unsigned16    data );
    virtual void write( Unsigned32    data );
    virtual void write( Unsigned64    data );
    virtual void write( Float32       data );
    virtual void write( Float64       data );
    virtual void write( Float96       data );
    virtual void write( const void   *data );

    virtual bool read( char          &data );
    virtual bool read( bool          &data );
    virtual bool read( Int8          &data );
    virtual bool read( Int16         &data );
    virtual bool read( Int32         &data );
    virtual bool read( Int64         &data );
    virtual bool read( Unsigned8     &data );
    virtual bool read( Unsigned16    &data );
    virtual bool read( Unsigned32    &data );
    virtual bool read( Unsigned64    &data );
    virtual bool read( Float32       &data );
    virtual bool read( Float64       &data );
    virtual bool read( Float96       &data );

    
    virtual void reserve_room_for( int room_size ) = 0;
    virtual void flush() = 0;

    virtual operator bool() const = 0;
    virtual bool eof() const = 0;

    static Endl endl;
    static Flsh flsh;

    int nb_digits; // for floating point numbers
};

// <<
template<class T> Stream &operator<<( Stream &os, const T &val ) { val.write_to_stream( os ); return os; }
template<class T> Stream &operator<<( Stream &os,       T *val ) { os.write( reinterpret_cast<const void *>( val ) ); return os; }
template<class T> Stream &operator<<( Stream &os, const T *val ) { os.write( reinterpret_cast<const void *>( val ) ); return os; }
Stream &operator<<( Stream &os, bool          val );
Stream &operator<<( Stream &os, const char   *val );
Stream &operator<<( Stream &os, char         *val );
Stream &operator<<( Stream &os, char          val );
Stream &operator<<( Stream &os, Int8          val );
Stream &operator<<( Stream &os, Int16         val );
Stream &operator<<( Stream &os, Int32         val );
Stream &operator<<( Stream &os, Int64         val );
Stream &operator<<( Stream &os, Unsigned8     val );
Stream &operator<<( Stream &os, Unsigned16    val );
Stream &operator<<( Stream &os, Unsigned32    val );
Stream &operator<<( Stream &os, Unsigned64    val );
Stream &operator<<( Stream &os, Float32       val );
Stream &operator<<( Stream &os, Float64       val );
Stream &operator<<( Stream &os, Float96       val );
Stream &operator<<( Stream &os, void         *val );

// >>
template<class T> Stream &operator>>( Stream &os, T &val ) { val.read_from_stream( os ); return os; }
Stream &operator>>( Stream &os, bool          &val );
Stream &operator>>( Stream &os, char          &val );
Stream &operator>>( Stream &os, Int8          &val );
Stream &operator>>( Stream &os, Int16         &val );
Stream &operator>>( Stream &os, Int32         &val );
Stream &operator>>( Stream &os, Int64         &val );
Stream &operator>>( Stream &os, Unsigned8     &val );
Stream &operator>>( Stream &os, Unsigned16    &val );
Stream &operator>>( Stream &os, Unsigned32    &val );
Stream &operator>>( Stream &os, Unsigned64    &val );
Stream &operator>>( Stream &os, Float32       &val );
Stream &operator>>( Stream &os, Float64       &val );
Stream &operator>>( Stream &os, Float96       &val );

/// \relates apply
struct WriteToStream {
    WriteToStream( Stream &os ) : os( os ), first( true ) {}
    template<class T> void operator()( const T &v ) {
        if ( not first )
            os << ' ';
        os << v;
        first = false;
    }
    Stream &os;
    bool first;
};

}

#endif // METIL_STREAM_H
