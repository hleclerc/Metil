#ifndef MACHINEID_H
#define MACHINEID_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

struct MachineId {
    static const MachineId *cpu( int nb = 0 );
    static const MachineId *gpu( const MachineId *cpu, int nb = 0 );
    static const MachineId *cur(); ///< pointer on current machine (where the code is executed)

    virtual int simd_alignement() const = 0;
    virtual void write_str( class String &os ) const = 0;
    virtual void *alloc( ST &rese ) = 0;
    virtual void free( void *data, ST rese ) = 0;
    virtual bool is_a_gpu() const;
};

END_METIL_NAMESPACE;

#endif // MACHINEID_H
