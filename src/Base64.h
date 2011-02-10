#ifndef BASE64_H
#define BASE64_H

#include "MetilString.h"

BEG_METIL_NAMESPACE;

void base_64_encode( String &os, const void *data, ST size );
void base_64_decode( String &os, const void *data, ST size );

END_METIL_NAMESPACE;

#endif // BASE64_H
