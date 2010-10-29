#include "NewString.h"
#include "Level1/StringHelp.h"
#include "Level1/OwcpStringData.h"

BEG_METIL_NAMESPACE;

NewString::NewString( ST size, ST rese ) {
    rese += sizeof( Level1::OwcpStringData ) + 1;
    Level1::OwcpStringData *res = new( MALLOC( rese ) ) Level1::OwcpStringData;
    res->data.size = size;
    res->data.rese = rese;
    data = res;
    res->val( size ) = 0;
}

NewString::NewString( ST size ) {
    ST rese = sizeof( Level1::OwcpStringData ) + size + 1;
    Level1::OwcpStringData *res = new( MALLOC( rese ) ) Level1::OwcpStringData;
    res->data.size = size;
    res->data.rese = rese;
    data = res;
    res->val( size ) = 0;
}

NewString::NewString( const char *beg, const char *end ) {
    if ( end < beg )
        end = beg;
    ST size = end - beg;
    ST rese = sizeof( Level1::OwcpStringData ) + size + 1;
    Level1::OwcpStringData *res = new( MALLOC( rese ) ) Level1::OwcpStringData;
    res->data.size = size;
    res->data.rese = rese;
    data = res;
    Level1::memcpy( res->ptr(), beg, size );
    res->val( size ) = 0;
}

NewString::NewString( const char *str ) {
    new( this ) NewString( str, str + Level1::strlen( str ) );
}

char *NewString::ptr() {
    return reinterpret_cast<Level1::OwcpStringData *>( data )->ptr();
}

void NewString::set_size( ST size ) {
    reinterpret_cast<Level1::OwcpStringData *>( data )->data.size = size;
}

void NewString::del() {
    Level1::OwcpStringData *o = reinterpret_cast<Level1::OwcpStringData *>( data );
    FREE( o, o->rese() );
}

END_METIL_NAMESPACE;
