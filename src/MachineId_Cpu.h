#ifndef MACHINEID_CPU_H
#define MACHINEID_CPU_H

#include "MachineId.h"
#include "BasicVec.h"

BEG_METIL_NAMESPACE;

struct MachineId_Cpu : public MachineId {
    MachineId_Cpu( int cpu_number );

    virtual void write_str( class String &os ) const;
    virtual const MachineId *gpu( int nb ) const;

    int cpu_number;
    mutable BasicVec<const MachineId *> gpus;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_CPU_H
