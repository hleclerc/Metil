#ifndef BASE64_H
#define BASE64_H

#include "String.h"

BEG_METIL_NAMESPACE;

void to_base_64( String &os, const void *data, ST size );

END_METIL_NAMESPACE;

#endif // BASE64_H