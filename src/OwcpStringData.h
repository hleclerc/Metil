#ifndef OWCPSTRINGDATA_H
#define OWCPSTRINGDATA_H

#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct OwcpStringAdditionalData {
    ST size;
    ST rese;
};

struct OwcpStringData : public Owcp<0,OwcpStringAdditionalData> {
    char *ptr() { return reinterpret_cast<char *>( this + 1 ); }
    char &val( ST i ) { return ptr()[ i ]; }
    ST size() const { return data.size; }
    ST rese() const { return data.rese; }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // OWCPSTRINGDATA_H
