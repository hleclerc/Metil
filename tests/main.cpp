// #include <Img.h>
#include <Array.h>
#include <Level1/TypeConstructor_Array.h>
using namespace Metil;
using namespace Level1;

DECL_TYPE( Array_8Int_s_64_1_1_1 );
DEFI_TYPE( Array, Array_8Int_s_64_1_1_1 );

int main() {
    SI64 v[] = {2,3};
    MO a( v, &metil_type_cst_Array_8Int_s_64_1_1_1 );
    // PRINT( a[ 0 ] );
    PRINT( a );
    // Img img( "/home/leclerc/Data/plateblanche/plateblanche001_0008.tif", MachineId::gpu( MachineId::cur(), 1 ) );
    //    Vec vec( Size(), 5 );
    //    for( ST i = 0; i < vec.size(); ++i )
    //        vec[ i ] = i;
    //    PRINT( vec );
    //    Vec s = vec.sizes();
    //    PRINT( s[ 0 ] );
    //    PRINT( s.type->name );
    //    PRINT( s.data );
    //    PRINT( s );

    //    Img img( 256, 256, type_ptr<float>() );

    //    PRINT( img.w() );
    //    PRINT( img.h() );
    //    for( int y = 0; y < img.h(); ++y )
    //        for( int x = 0; x < img.w(); ++x )
    //            img( x, y ) = float( x + y );

    //    PRINT( img.min() );
    //    PRINT( img.max() );

    // Img img( "/home/leclerc/Dic/Croix/toto000.tif" );
    // Vec v( T_FP64, 1, 7 );
    // Vec v( 1, 5 );
    // PRINT( v );


}
