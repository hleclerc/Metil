#ifndef MACHINEID_H
#define MACHINEID_H

#include "Config.h"

BEG_METIL_NAMESPACE;

struct MachineId {
    static MachineId cpu( int nb = 0 ) { MachineId res; res.id = -1 - nb; return res; }
    static MachineId gpu( int nb = 0 ) { MachineId res; res.id =      nb; return res; }

    bool is_a_gpu() const { return id >= 0; }
    bool is_a_cpu() const { return id <  0; }

    int id;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_H
