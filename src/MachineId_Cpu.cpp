#include "MachineId_Gpu.h"
#include "String.h"

BEG_METIL_NAMESPACE;

MachineId_Cpu::MachineId_Cpu( int cpu_number ) : cpu_number( cpu_number ) {}

void MachineId_Cpu::write_str( class String &os ) const { os << "CPU(" << cpu_number << ")"; }

const MachineId *MachineId_Cpu::gpu( int nb ) const { ///< @todo cpu != cur
    ST os = gpus.size();
    if ( os <= nb ) {
        gpus.resize( nb + 1 );
        for( int i = os; i <= nb; ++i )
            gpus[ i ] = NEW( MachineId_Gpu, this, i );
    }
    return gpus[ nb ];
}


END_METIL_NAMESPACE;

