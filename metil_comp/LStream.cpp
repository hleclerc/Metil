#include "LStream.h"
#include "LStreamItem.h"
#include "LazyScheduler.h"

namespace Metil {

LStream::LStream( Stream *os ) : os( os ), item( 0 ) {
}

LStream::~LStream() {
    flush();
}

void LStream::get_line( String &line ) {
    ASSERT( 0, "TODO" );
}

void LStream::write( const void *data, int size ) {
}

void LStream::write( char data ) {
}

void LStream::reserve_room_for( int room_size ) {
}

void LStream::flush() {
    execute();
    dec_ref( item );
    item = 0;
}

LStream::operator bool() const {
    return true;
}

void LStream::execute() {
    schedule_and_execute( item );
}

void LStream::append( const LazyObject *val ) {
    const LStreamItem *old_item = item;
    item = new LStreamItemFromLazyObject( old_item, os, val );
    if ( old_item )
        dec_ref( old_item );
}

void LStream::shift_left_( const String &val ) {
    const LStreamItem *old_item = item;
    item = new_LStreamItemString( old_item, os, String( val ) );
    if ( old_item )
        dec_ref( old_item );
}

}
