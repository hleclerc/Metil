#include <Mat.h>
#include <MachineId.h>
#include <CudaMetil.h>
using namespace Metil;
using namespace Level1;

int main() {
//    Vec sst( 1, 2, 3 );
//    Vec voisin( MachineId::cpu( ... ) );
//    Vec res = sst + voisin;
//    res.exec_on_machine( ... );
//    PRINT( res );

//    Vec<sst> ssts;
//    for (i=1;) {
//        ssts[i].assign_to_cpu(i);
//        ssts[i].read_mesh("");
//        ssts[i].compute_stiffness();

//        noeud_commun = map_cond( m.noeud, n.noeud, _1.number, _1 == _2 );
//    }


    // Array<Val> a( 2 );
    //    PRINT( Val(1.5) );
    Mat a( 5, 6, type_ptr<float>() );
    a.set_values( 10 );
    //    for( int r = 0; r < a.nb_rows(); ++r )
    //        for( int c = 0; c < a.nb_cols(); ++c )
    //            a( r, c ) = r + c;
    PRINTN( a );

    //    PRINTN( a );
    //    PRINT( a( 0, 0 ) );
//    PRINT( a.size() );
//    PRINT( a.sizes() );
    //    m( 1, 0 ) = 666;
    //    m( 1, 2 ) = 666;
    //    PRINT( m( 1, 0 ) );
    //    PRINT( m );
    // Vec a( 5, 6 );
    // Val a( 10 ), b( 24 );
    // PRINT( a( 0 ) );
    // PRINT( a( 1 ) );
}
