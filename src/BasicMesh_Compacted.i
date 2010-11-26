%{
    #include "BasicMesh_Compacted.h"
    #include "CudaMetil.h"
    #include "BasicMesh.h"
    namespace Metil {
        inline Ps<BasicMesh_Compacted> make_cs( const BasicMesh &l, const MachineId *machine ) {
            return make_cs( &l, 1, machine );
        }
    }
%}

%include "Ps.i"
%include "BasicMesh.i" 
%include "BasicVecRef.i"

namespace Metil {
    class BasicMesh_Compacted {
    public:
    };

    %extend BasicMesh_Compacted {
        Metil_ST nb_nodes() const { return self->pos_nodes.size() ? self->pos_nodes[ 0 ].size() : 0; }
    };

    %template(Ps_BasicMesh_Compacted) Ps<BasicMesh_Compacted>;
    Ps<BasicMesh_Compacted> make_cs( const BasicMesh &l, const MachineId *machine );
    Ps<BasicMesh_Compacted> strdup( const Ps<BasicMesh_Compacted> &src, const MachineId *machine );
    void memcpy( Ps<BasicMesh_Compacted> &dst, const Ps<BasicMesh_Compacted> &src );

    // #include "CudaMetil.h"

}
