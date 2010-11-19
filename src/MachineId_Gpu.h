#ifndef MACHINEID_GPU_H
#define MACHINEID_GPU_H

#include "MachineId_Cpu.h"

BEG_METIL_NAMESPACE;

struct MachineId_Gpu : public MachineId {
    MachineId_Gpu( const MachineId *cpu, int gpu_number );

    virtual void write_str( class String &os ) const;
    virtual bool is_a_gpu() const;

    const MachineId *cpu;
    int gpu_number;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_GPU_H
