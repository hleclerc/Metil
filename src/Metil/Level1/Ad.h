#ifndef AD_H
#define AD_H

#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE

/// Auto Del ( call Del during destroy )
struct Ad {
    Ad( MO o ) : o( o ) {}
    ~Ad() { CM_1( del, o ); }
    operator MO() const { return o; }
    MO o;
};

END_METIL_LEVEL1_NAMESPACE

#endif // AD_H
