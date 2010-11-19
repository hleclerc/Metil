#include "MachineId_Gpu.h"
#include "DynamicCppLib.h"
#include "BasicVec.h"
#include "System.h"
#include "String.h"

BEG_METIL_NAMESPACE;

const MachineId *MachineId::cpu( int nb ) {
    static BasicVec<MachineId *> res;
    ST os = res.size();
    if ( os <= nb ) {
        res.resize( nb + 1 );
        for( int i = os; i <= nb; ++i )
            res[ i ] = NEW( MachineId_Cpu, i );
    }
    return res[ nb ];
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

END_METIL_NAMESPACE;

