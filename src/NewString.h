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
    NewString( const char *beg, const char *end ); ///< make a copy
    NewString( const char *str ); ///< make a copy

    char *ptr();
    void set_size( ST size );
    void del();

    void *data;
};

END_METIL_NAMESPACE;

#endif // NewStringW_H
