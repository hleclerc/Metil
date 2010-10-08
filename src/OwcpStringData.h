#ifndef OWCPSTRINGDATA_H
#define OWCPSTRINGDATA_H

#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct OwcpStringAdditionalData {
    ST size;
    ST rese;
};

struct OwcpStringData : public Owcp<0,OwcpStringAdditionalData> {
    OwcpStringData() : Owcp<0,OwcpStringAdditionalData>( &metil_type_bas_OwcpString ) {}
    char *ptr() { return reinterpret_cast<char *>( this + 1 ); }
    char &val( ST i ) { return ptr()[ i ]; }
    ST size() const { return data.size; }
    ST rese() const { return data.rese; }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // OWCPSTRINGDATA_H
