#ifndef S_H
#define S_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

/**

*/
template<class T_>
struct S {
    typedef T_ T;
};

#define ST( T ) extern S<T> T_##T;
ST( SI8  );
ST( SI16 );
ST( SI32 );
ST( SI64 );
ST( PI8  );
ST( PI16 );
ST( PI32 );
ST( PI64 );
ST( FP32 );
ST( FP64 );
ST( FP80 );
#undef ST

END_METIL_NAMESPACE;

#endif // S_H
