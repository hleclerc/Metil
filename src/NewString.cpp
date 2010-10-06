#include "NewString.h"
#include "OwcpStringData.h"

BEG_METIL_NAMESPACE;

NewString::NewString( ST size, ST rese ) {
    rese += sizeof( Level1::OwcpStringData ) + 1;
    Level1::OwcpStringData *res = reinterpret_cast<Level1::OwcpStringData *>( MALLOC( rese ) );
    res->data.size = size;
    res->data.rese = rese;
    data = res;
    res->val( size ) = 0;
}

NewString::NewString( ST size ) {
    ST rese = sizeof( Level1::OwcpStringData ) + size + 1;
    Level1::OwcpStringData *res = reinterpret_cast<Level1::OwcpStringData *>( MALLOC( rese ) );
    res->data.size = size;
    res->data.rese = rese;
    data = res;
    res->val( size ) = 0;
}

char *NewString::ptr() {
    return reinterpret_cast<Level1::OwcpStringData *>( data )->ptr();
}

END_METIL_NAMESPACE;
