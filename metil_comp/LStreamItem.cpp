#include "LStreamItem.h"

namespace Metil {

LStreamItem::LStreamItem( const LStreamItem *old_stream_item, Stream *os ) : old_stream_item( old_stream_item ), os( os ), _done( false ) {
    if ( old_stream_item )
        add_child( old_stream_item );
}

LStreamItem::~LStreamItem() {
}

bool LStreamItem::done() const {
    return _done;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
LStreamItemFromLazyObject::LStreamItemFromLazyObject( const LStreamItem *old_stream_item, Stream *os, const LazyObject *obj ) : LStreamItem( old_stream_item, os ), obj( obj ) {
    add_child( obj );
}

LStreamItemFromLazyObject::~LStreamItemFromLazyObject() {
}

void LStreamItemFromLazyObject::exec_node() const {
    obj->write_to_stream( *os );
    _done = true;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------

LStreamItemString::LStreamItemString( const LStreamItem *old_stream_item, Stream *os, const String &str ) : LStreamItem( old_stream_item, os ), str( str ) {
}

void LStreamItemString::exec_node() const {
    str.write_to_stream( *os );
    _done = true;
}

const LStreamItem *new_LStreamItemString( const LStreamItem *old_item, Stream *os, const String &str ) {
    return new LStreamItemString( old_item, os, str );
}

}
