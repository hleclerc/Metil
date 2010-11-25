#ifndef LAZYOBJECTDATA_H
#define LAZYOBJECTDATA_H

#include "MachineId.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct LazyObjectData {
    LazyObjectData() : machine( 0 ) {
    }
    ~LazyObjectData() {
    }
    const MachineId *machine;
};

// template<class nb_children>
// struct LazyObjectHeader : public Owcp<nb_children,LazyObjectData> {
// };

END_METIL_LEVEL1_NAMESPACE;

#endif // LAZYOBJECTDATA_H
