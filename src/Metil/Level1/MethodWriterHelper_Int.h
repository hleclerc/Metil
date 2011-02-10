#ifndef METHODWRITERHELPER_INT_H
#define METHODWRITERHELPER_INT_H

#include "../Config.h"

BEG_METIL_LEVEL1_NAMESPACE;

class MethodWriterHelper_Int {
public:
    MethodWriterHelper_Int( int len = 0, int sgn = 1, int off = 0 );

    int len; ///< totol length (in bits)
    int sgn; ///< -1, 0 or 1
    int off; ///< offset (in bits)
};

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODWRITERHELPER_INT_H
