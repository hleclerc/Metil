#include "MachineId_Gpu.h"
#include "String.h"

BEG_METIL_NAMESPACE;

MachineId_Gpu::MachineId_Gpu( const MachineId *cpu, int gpu_number ) : cpu( cpu ), gpu_number( gpu_number ) {}

void MachineId_Gpu::write_str( class String &os ) const { os << "GPU(" << gpu_number << ")"; }
bool MachineId_Gpu::is_a_gpu() const { return true; }


END_METIL_NAMESPACE;

