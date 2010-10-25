#ifndef METIL_STRING_STREAM_H
#define METIL_STRING_STREAM_H

#include "Stream.h"
#include "StdOp.h"

namespace Metil {

/**
    StringStream<String> s;
    s << 10+2;
    PRINT( s.str ); // -> "12"
*/
template<class S>
struct StringStream : public Stream {
    StringStream() : p( 0 ) {}
    StringStream( const S &s ) : p( 0 ), str( s ) {}

    virtual bool get_char( char   &data ) { data = str[ p++ ]; return p <= str.size(); }
    virtual bool get_line( String &line ) { return str.get_line( p, line ); }
    // virtual bool get_word( String &word ) { return str.get_word( p, word ); }

    virtual Int64 tell() { return p; }
    virtual Int64 size() { return str.size(); }
    virtual void seek( Int64 pos ) { p = max( Int64(0), min( pos, Int64(str.size()) ) ); }

    virtual void write( const void *data, int size ) { str.write( data, size ); }
    virtual void write( char        data           ) { str.write( data ); }

    virtual void flush() {}
    virtual void reserve_room_for( int room_size ) { str.reserve_room_for( room_size ); }

    virtual bool eof() const { return p == str.size(); }
    virtual operator bool() const { return not eof(); }

    int p;
    S str;
};

}

#endif // METIL_STRING_STREAM_H
