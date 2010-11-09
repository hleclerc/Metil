#include "MachineId_Cpu.h"
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

const MachineId *MachineId::gpu( const MachineId *cpu, int nb ) { ///< @todo cpu != cur
    static DynamicCppLib dl( directory_of( __FILE__ ) + "/MachineId_Gpu.cpp" );
    typedef MachineId *NEW_MachineId_Gpu( const MachineId *cpu, int gpu_number );
    static NEW_MachineId_Gpu *func = reinterpret_cast<NEW_MachineId_Gpu *>( dl.get_sym( "NEW_MachineId_Gpu" ) );

    static BasicVec<MachineId *> res;
    ST os = res.size();
    if ( os <= nb ) {
        res.resize( nb + 1 );
        for( int i = os; i <= nb; ++i )
            res[ i ] = func( cpu, i );
    }
    return res[ nb ];
}

const MachineId *MachineId::cur() {
    return cpu( 0 ); /// @todo MPI_...
}

bool MachineId::is_a_gpu() const {
    return false;
}


END_METIL_NAMESPACE;

