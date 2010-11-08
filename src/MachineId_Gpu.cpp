#include "MachineId_Gpu.h"
#include "CudaMetil.h"
#include "String.h"

BEG_METIL_NAMESPACE;

MachineId_Gpu::MachineId_Gpu( const MachineId *cpu, int gpu_number ) : cpu( cpu ), gpu_number( gpu_number ) {}

int MachineId_Gpu::simd_alignement() const { return 16 * 4; }
void MachineId_Gpu::write_str( class String &os ) const { os << "GPU(" << gpu_number << ")"; }
void *MachineId_Gpu::alloc( ST &rese ) { void *res; cudaMalloc( &res, rese ); return res; }
void MachineId_Gpu::free( void *data, ST ) { cudaFree( data ); }
bool MachineId_Gpu::is_a_gpu() const { return true; }


extern "C" MachineId *NEW_MachineId_Gpu( const MachineId *cpu, int gpu_number ) {
    return NEW( MachineId_Gpu, cpu, gpu_number );
}


END_METIL_NAMESPACE;

