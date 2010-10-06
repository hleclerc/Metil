#ifndef NewString_H
#define NewString_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

/**
    Used to make new contiguous String.
*/
class NewString {
public:
    NewString( ST size ); ///< will reserve 1 additional byte for \0
    NewString( ST rese, ST size ); ///< will reserve 1 additional byte for \0
    char *ptr();
    void *data;
};

END_METIL_NAMESPACE;

#endif // NewStringW_H
