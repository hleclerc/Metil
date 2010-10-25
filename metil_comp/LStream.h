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

#ifndef METIL_LSTREAM_H
#define METIL_LSTREAM_H

#include "LazyObject.h"
#include "Stream.h"
#include "String.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LStream.cpp
#endif

namespace Metil {

class LStreamItem;

const LStreamItem *new_LStreamItemString( const LStreamItem *old_item, Stream *os, const String &str );

/**

*/
class LStream : public Stream {
public:
    LStream( Stream *os );
    ~LStream();

    void append( const LazyObject *val );

    virtual void get_line( String &line );
    virtual void write( const void *data, int size );
    virtual void write( char data );
    virtual void reserve_room_for( int room_size );
    virtual void flush();

    virtual operator bool() const;

    void execute();

    template<class T>
    LStream &operator<<( const T &val ) {
        shift_left_( val );
        return *this;
    }

private:
    void shift_left_( const String &val );

    Stream *os;
    const LStreamItem *item;
};




}


#endif // METIL_LSTREAM_H
