// #include <Img.h>
#include <Vec.h>
using namespace Metil;
using namespace Level1;

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_path grototo
#endif

int main() {
    // Img img( "/home/leclerc/Data/plateblanche/plateblanche001_0008.tif", MachineId::gpu( MachineId::cur(), 1 ) );
    Vec vec( Size(), 5 );
    for( ST i = 0; i < vec.size(); ++i )
        vec[ i ] = i;
    PRINT( vec );
    Vec s = vec.sizes();
    PRINT( s );
    Vec t = s;
    PRINT( t );
    PRINT( s.type->name );

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
