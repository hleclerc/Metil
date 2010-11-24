#ifndef LAZYOBJECTDATA_H
#define LAZYOBJECTDATA_H

#include "MachineId.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct LazyObjectData {
    LazyObjectData() : machine( 0 ), op_mp( 0 ) {
    }
    ~LazyObjectData() {
        if ( op_mp.type )
            CM_1( del, op_mp );
    }
    const MachineId *machine;
    MO op_mp;
};

// template<class nb_children>
// struct LazyObjectHeader : public Owcp<nb_children,LazyObjectData> {
// };

END_METIL_LEVEL1_NAMESPACE;

#endif // LAZYOBJECTDATA_H
