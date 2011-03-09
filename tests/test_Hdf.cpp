#include <Metil/Hdf.h>
using namespace Metil;

void create() {
    Hdf hdf( "res.h5" );

    BasicVec<int> v;
    v << 10;
    v.write_to( hdf, "/g/v" );

    hdf.add_tag( "/g"  , "tag", "tata" );
    // hdf.add_tag( "/g/v", "tag", "toto" );
}

void read() {
    Hdf hdf( "res.h5" );

    //    BasicVec<int> v;
    //    hdf.read_size( "/g/v", v );
    //    PRINT( v );

    String tag;
    hdf.read_tag( "/g", "tag", tag, true );
    PRINT( tag );

    hdf.read_tag( "/g", "yop", tag );
    PRINT( tag );

    //hdf.read_tag( "/g/v", "tag", tag, true  );
    //PRINT( tag );
}

int main() {
    //system( "rm res.h5" );
    //create();
    read();
}


