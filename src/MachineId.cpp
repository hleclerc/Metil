#include "MachineId_Gpu.h"
#include "DynamicCppLib.h"
#include "BasicVec.h"
#include "System.h"

BEG_METIL_NAMESPACE;

MachineId::~MachineId() {
}

const MachineId *MachineId::cpu( int nb ) {
    static BasicVec<MachineId_Cpu> res;
    while ( res.size() <= nb )
        res.push_back( res.size() );
    return &res[ nb ];
}

const MachineId *MachineId::gpu( const MachineId *cpu, int nb ) {
    return cpu->gpu( nb );
}

int MachineId::simd_alignement( Type type ) {
    return type == Gpu ? 16 * 4 : 4 * 4;
}

const MachineId *MachineId::cur() {
    return cpu( 0 ); /// @todo MPI_...
}

bool MachineId::is_a_gpu() const {
    return false;
}

const MachineId *MachineId::gpu( int nb ) const { ///< @todo cpu != cur
    ASSERT( 0, "Machine do not has any Gpu" );
    return 0;
}

MachineId_Cpu::Type MachineId::type( const String &name ) {
    if ( name == "Cpu" ) return Cpu;
    if ( name == "Gpu" ) return Gpu;
    ERROR( "type %s not known", name.c_str() );
    return Cpu;
}

END_METIL_NAMESPACE;

