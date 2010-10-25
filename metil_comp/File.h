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

#ifndef METIL_FILE_H
#define METIL_FILE_H

#include "StreamWithEndlBeforeDestroy.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file File.cpp
#endif

namespace Metil {

/**

*/
class File : public Stream {
public:
    File( void *file ); // FILE *
    File( const char *filename, const char *mode = "r" );
    virtual ~File();
    
    void close();


    virtual char   get_char();
    virtual String get_word();
    virtual String get_line();
    virtual String get_left();

    virtual bool get_char( char   &data );
    virtual bool get_line( String &line );
    virtual bool get_left( String &left );

    virtual Int64 tell();
    virtual Int64 size();
    virtual void seek( Int64 pos );

    void clear_err();

    virtual void write( const void *data, int size );
    virtual void write( char        data           );
    
    virtual void reserve_room_for( int room_size );
    virtual void flush();

    virtual operator bool() const;
    virtual bool eof() const;

private:
    void *f;
};

extern File cout; /// as in std::
extern File cerr; /// as in std::
extern File cin;  /// as in std::

extern StreamWithEndlBeforeDestroyMaker coutn; /// as in std:: but with endl when << chain is finished
extern StreamWithEndlBeforeDestroyMaker cerrn; /// as in std:: but with endl when << chain is finished

}

#endif // METIL_FILE_H
