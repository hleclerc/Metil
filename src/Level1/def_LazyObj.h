#define MET_DO( N )
#define MET_YO( N )
#define MET_OoO( N ) \
    MO  metil_def_##N##__when__a__isa__LazyObject__pert__10( MO &a, MO b ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<2,LazyObjectOperationData_OoO> TR; \
        TR *data = NEW( TR, type, a, b ); \
        return MO( data, type ); \
    }
#define MET_1_OoO( N ) \
    MO  metil_def_##N##__when__b__isa__LazyObject__pert__10( MO &a, MO b ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<2,LazyObjectOperationData_OoO> TR; \
        TR *data = NEW( TR, type, a, b ); \
        return MO( data, type ); \
    }
#define MET_BO( N )
#define MET_VOpS( N )
#define MET_BOO( N )
#define MET_1_BOO( N )
#define MET_pO( N )
#define MET_FO( N )
#define MET_LO( N )
#define MET_poO( N )
#define MET_1_poO( N )
#define MET_po( N )
#define MET_EO( N )
#define MET_VoO( N )
#define MET_1_VoO( N )
#define MET_Vopp( N )
#define MET_IO( N )
#define MET_XOO( N )
#define MET_1_XOO( N )
#define MET_VoY( N )
#define MET_OO( N ) \
    MO  metil_def_##N##__when__a__isa__LazyObject__pert__10( MO a ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<1,LazyObjectOperationData_OO> TR; \
        TR *data = NEW( TR, type, a ); \
        return MO( data, type ); \
    }
#define MET_OOO( N ) \
    MO  metil_def_##N##__when__a__isa__LazyObject__pert__10( MO a, MO b ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<2,LazyObjectOperationData_OOO> TR; \
        TR *data = NEW( TR, type, a, b ); \
        return MO( data, type ); \
    }
#define MET_1_OOO( N ) \
    MO  metil_def_##N##__when__b__isa__LazyObject__pert__10( MO a, MO b ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<2,LazyObjectOperationData_OOO> TR; \
        TR *data = NEW( TR, type, a, b ); \
        return MO( data, type ); \
    }
#define MET_VOO( N )
#define MET_1_VOO( N )
#define MET_VoPS( N )
#define MET_Vo( N )
#define MET_SO( N )
#define MET_OOS( N ) \
    MO  metil_def_##N##__when__a__isa__LazyObject__pert__10( MO a, ST b ) { \
        Type *type = &metil_type_bas_LazyOperation_##N; \
        typedef Owcp<1,LazyObjectOperationData_OOS> TR; \
        TR *data = NEW( TR, type, a ); \
        data->data.b = b; \
        return MO( data, type ); \
    }
#define MET_MO( N )
