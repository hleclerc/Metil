#include "MachineId_Cpu.h"
#include "String.h"

BEG_METIL_NAMESPACE;

MachineId_Cpu::MachineId_Cpu( int cpu_number ) : cpu_number( cpu_number ) {}

int MachineId_Cpu::simd_alignement() const { return 4 * 4; }
void MachineId_Cpu::write_str( class String &os ) const { os << "CPU(" << cpu_number << ")"; }
void *MachineId_Cpu::alloc( ST &rese ) { return MALLOC( rese ); }
void MachineId_Cpu::free( void *data, ST rese ) { FREE( data, rese ); }


END_METIL_NAMESPACE;

