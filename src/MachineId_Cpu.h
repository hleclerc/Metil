#ifndef MACHINEID_CPU_H
#define MACHINEID_CPU_H

#include "MachineId.h"

BEG_METIL_NAMESPACE;

struct MachineId_Cpu : public MachineId {
    MachineId_Cpu( int cpu_number );

    virtual int simd_alignement() const;
    virtual void write_str( class String &os ) const;
    virtual void *alloc( ST &rese );
    virtual void free( void *data, ST rese );

    int cpu_number;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_CPU_H
