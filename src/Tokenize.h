#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "BasicVec.h"
#include "String.h"

BEG_METIL_NAMESPACE;

/** TODO: optimize */
inline BasicVec<String> tokenize( const String &str, const String &sep ) {
    BasicVec<String> res;
    String tmp = str;
    while ( true ) {
        int n = tmp.find( sep );
        if ( n < 0 ) {
            res.push_back( tmp );
            return res;
        }
        res.push_back( tmp.beg_upto( n ) );
        tmp = tmp.end_from( n + sep.size() );
    }
}


END_METIL_NAMESPACE;

#endif // TOKENIZE_H
