#ifndef PIPE_H
#define PIPE_H

namespace Metil {

///
class Pipe : public Stream {
public:
    Pipe( const CString &executable );

    virtual void getline( String &line );
    virtual void write( const void *data, int size ) ;
    virtual void write( char        data           );
    virtual void reserve_room_for( int room_size );
    virtual void flush();
    virtual operator bool() const;

private:
    void *pipe;
};

} // namespace Metil


#endif // PIPE_H
