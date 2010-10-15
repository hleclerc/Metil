%{
    #include "Ps.h"
%}

%include "TypeConfig.i"
%include "MachineId.i"

namespace Metil {
    template<class T>
    struct Ps {
        Metil_ST nb_items();
        Metil_ST size_mem();
        void free();
        T *ptr();

        MachineId pos; ///< machine id (-1 -> cpu, 0 -> gpu board 0, ...)
    };

    %extend Ps {
         void free() {
             if ( self->pos.is_a_gpu() )
                 cudaFree( self->ptr() );
             else
                 FREE( self->ptr(), self->size_mem() );
         }
    }
}
