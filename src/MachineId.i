namespace Metil {
    struct MachineId {
        static MachineId cpu( int nb = 0 );
        static MachineId gpu( int nb = 0 );

        bool is_a_gpu() const;
        bool is_a_cpu() const;
    };
}
