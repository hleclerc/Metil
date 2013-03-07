#ifndef MACHINEID_H
#define MACHINEID_H

#include "Malloc.h"

BEG_METIL_NAMESPACE;

struct MachineId {
    CANNOT_BE_DERIVED;
    typedef enum { Cpu, Gpu } Type;

    virtual ~MachineId();
    virtual void write_str( class String &os ) const = 0;
    virtual Type type() const = 0;
    virtual const MachineId *gpu( int nb ) const; ///< find associated gpu number
    virtual bool is_a_gpu() const;

    static const MachineId *cpu( int nb = 0 );
    static const MachineId *gpu( const MachineId *cpu, int nb = 0 );
    static const MachineId *cur(); ///< pointer on current machine (where the code is executed)

    static int simd_alignement( Type );
    static Type type( const class String &name );

};

END_METIL_NAMESPACE;

#endif // MACHINEID_H
