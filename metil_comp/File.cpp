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

#include "File.h"
#include "String.h"
#include "StdOp.h"
#include <stdlib.h>
#include <stdio.h>

namespace Metil {

File cout( (void *)stdout );
File cerr( (void *)stderr );
File cin ( (void *)stdin  );

StreamWithEndlBeforeDestroyMaker coutn( cout );
StreamWithEndlBeforeDestroyMaker cerrn( cerr );

File::File( const char *filename, const char *mode ) {
    f = fopen( filename, mode );
}

File::File( void *file ) {
    f = file;
}

File::~File() {
    close();
}

void File::close() {
    if ( f )
        fclose( (FILE *)f );
    f = NULL;
}

char   File::get_char() { return  getc( (FILE *)f ); }
String File::get_word() { return Stream::get_word(); }
String File::get_line() { return Stream::get_line(); }
String File::get_left() { return Stream::get_left(); }

bool File::get_char( char &data ) {
    if ( f == 0 or feof( (FILE *)f ) )
        return false;
    data = ::getc( (FILE *)f );
    return true;
}


bool File::get_line( String &line ) {
    if ( not f ) {
        line.resize( 0 );
        return false;
    }
    size_t rese = line.r + 1;
    ssize_t size = ::getline( &line.d, &rese, (FILE *)f ); // getline uses realloc if necessary...
    if ( size < 0 ) {
        line.resize( 0 );
        return false;
    }
    line.r = rese - 1;
    line.s = max( size, 0 );
    return true;
}

bool File::get_left( String &res ) {
    if ( not f )
        return false;
    Int64 o = ftell( (FILE *)f );
    fseek( (FILE *)f, 0, SEEK_END );
    res.resize( ftell( (FILE *)f ) - o );

    fseek( (FILE *)f, 0, SEEK_SET );
    Int64 tmp = fread( res.data(), 1, res.size(), (FILE *)f );
    ASSERT( tmp == res.size(), "unable to read file..." );
    return true;
}


void File::clear_err() {
    clearerr( (FILE *)f );
}

Int64 File::tell() {
    return ftell( (FILE *)f );
}

Int64 File::size() {
    Int64 old_pos = tell();

    fseek( (FILE *)f, 0, SEEK_END );
    Int64 res = tell();

    seek( old_pos );
    return res;
}

void File::seek( Int64 pos ) {
    fseek( (FILE *)f, pos, SEEK_SET );
}

File::operator bool() const {
    return f and not feof( (FILE *)f );
}
bool File::eof() const {
    return feof( (FILE *)f );
}

void File::write( const void *data, int size ) {
    fwrite( data, size, 1, (FILE *)f );
}

void File::write( char data ) {
    fwrite( &data, 1, 1, (FILE *)f );
}

void File::flush() {
    fflush( (FILE *)f );
}

void File::reserve_room_for( int room_size ) {
}

}

