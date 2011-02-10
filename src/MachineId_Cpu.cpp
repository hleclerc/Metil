#include "MachineId_Gpu.h"
#include "MetilString.h"

BEG_METIL_NAMESPACE;


MachineId_Cpu::MachineId_Cpu( int cpu_number ) : cpu_number( cpu_number ) {}

MachineId_Cpu::~MachineId_Cpu() {
    for( int i = 0; i < gpus.size(); ++i )
        DEL( gpus[ i ] );
}

void MachineId_Cpu::write_str( class String &os ) const { os << "CPU(" << cpu_number << ")"; }

const MachineId *MachineId_Cpu::gpu( int nb ) const { ///< @todo cpu != cur
    while ( gpus.size() <= nb )
        gpus << NEW( MachineId_Gpu, this, gpus.size() );
    return gpus[ nb ];
}

MachineId_Cpu::Type MachineId_Cpu::type() const {
    return Cpu;
}

END_METIL_NAMESPACE;

