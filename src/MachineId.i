%{
    #include "MachineId.h"
    namespace Metil {
        const MachineId *cpu( int nb = 0 ) { return MachineId::cpu( nb ); }
        const MachineId *gpu( const MachineId *cpu = MachineId::cpu( 0 ), int nb = 0 ) { return cpu->gpu( nb ); }
    };
%}

namespace Metil {
    struct MachineId {
        typedef enum { Cpu, Gpu } Type;
        virtual Type type() const = 0;
    };
    const MachineId *cpu( int nb = 0 );
    const MachineId *gpu( const MachineId *cpu = MachineId::cpu( 0 ), int nb = 0 );
}
