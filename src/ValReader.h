#ifndef VALREADER_H
#define VALREADER_H

#include "BasicVec.h"
#include "MetilString.h"

BEG_METIL_LEVEL1_NAMESPACE;

class ValReader {
public:
    ValReader( String str, BasicVec<String> &symbols );

    BasicVec<String> &symbols;
    Val res;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // VALREADER_H
