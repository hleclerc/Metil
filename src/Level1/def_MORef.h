#define MET_Vo( N )
#define MET_OO( N ) MO  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_BO( N ) bool  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_IO( N ) SI32  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_LO( N ) SI64  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_SO( N ) ST  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_FO( N ) FP32  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_DO( N ) FP64  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_EO( N ) FP80  metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_VOt( N ) void  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, String &b ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o, b ); }
#define MET_pO( N ) void * metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_Vot( N )
#define MET_po( N )
#define MET_VoPS( N )
#define MET_VOpS( N ) void  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, void *b, ST c ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o, b, c ); }
#define MET_OOO( N ) MO  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, MO b ) { Ad v = CM_1( copy, a ); return CM_2( N, v.o, b ); }
#define MET_1_OOO( N ) MO  metil_def_##N##__when__b__isa__MORef__pert__11( MO a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_BOO( N ) bool  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, MO b ) { Ad v = CM_1( copy, a ); return CM_2( N, v.o, b ); }
#define MET_1_BOO( N ) bool  metil_def_##N##__when__b__isa__MORef__pert__11( MO a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_VoO( N )
#define MET_1_VoO( N ) void  metil_def_##N##__when__b__isa__MORef__pert__11( MO &a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_VOO( N ) void  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, MO b ) { Ad v = CM_1( copy, a ); return CM_2( N, v.o, b ); }
#define MET_1_VOO( N ) void  metil_def_##N##__when__b__isa__MORef__pert__11( MO a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_OoO( N )
#define MET_1_OoO( N ) MO  metil_def_##N##__when__b__isa__MORef__pert__11( MO &a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_PoO( N )
#define MET_1_PoO( N ) const void * metil_def_##N##__when__b__isa__MORef__pert__11( MO &a, MO b ) { Ad v = CM_1( copy, b ); return CM_2( N, a, v.o ); }
#define MET_OOS( N ) MO  metil_def_##N##__when__a__isa__MORef__pert__10( MO a, ST b ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o, b ); }
#define MET_VoY( N )
#define MET_YO( N ) struct OwcpChild * metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
#define MET_MO( N ) const MachineId * metil_def_##N##__when__a__isa__MORef__pert__10( MO a ) { Ad v = CM_1( copy, a ); return CM_1( N, v.o ); }
