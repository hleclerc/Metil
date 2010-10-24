#include "matlab.h"
#include "String.h"

namespace Metil {

///
struct MatlabStream : public Stream {
    virtual void get_line( String &line ) {}

    virtual void write( const void *data_, int size ) {
        const char *data = reinterpret_cast<const char *>( data_ );
        String s( data, data + size );
        mexPrintf( "%s", s.data() );
    }

    virtual void write( char data ) {
        mexPrintf( "%c", data );
    }

    virtual void reserve_room_for( int room_size ) {}

    virtual void flush() {}

    virtual operator bool() const { return true; }

};

MatlabStream matlab_output_inst;
Stream &matlab_output = matlab_output_inst;

}
