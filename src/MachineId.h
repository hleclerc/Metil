#ifndef MACHINEID_H
#define MACHINEID_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

struct MachineId {
    typedef enum { Cpu, Gpu } Type;

    static const MachineId *cpu( int nb = 0 );
    static const MachineId *gpu( const MachineId *cpu, int nb = 0 );
    static const MachineId *cur(); ///< pointer on current machine (where the code is executed)

    static int simd_alignement( Type );

    virtual void write_str( class String &os ) const = 0;
    virtual const MachineId *gpu( int nb ) const; ///< find associated gpu number
    virtual bool is_a_gpu() const;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_H
