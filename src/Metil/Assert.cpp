#include "Assert.h"

#include <cstdlib>
#include <cstdio>
#include <cstdarg>

BEG_METIL_NAMESPACE

void abort_or_throw() {
    #ifdef TESTING
    throw Abort();
    #else
    abort();
    #endif
}

bool __disp_and_abort_if_not_cond__( bool cond, const char *txt, ... ) {
    if ( not cond ) {
        va_list argp;
        va_start( argp, txt );
        vfprintf( stderr, txt, argp );
        va_end( argp );
        abort_or_throw();
    }
    return true;
}

bool __do_nothing__() {
    return true;
}

END_METIL_NAMESPACE
