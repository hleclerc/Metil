#ifndef LAZYOBJECT_HEADER_H
#define LAZYOBJECT_HEADER_H

#include "MachineId.h"
#include "Malloc.h"
#include "MO.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct LazyObject_Header {
    CANNOT_BE_DERIVED;

    const MachineId *machine;
    MO object;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // LAZYOBJECT_HEADER_H
