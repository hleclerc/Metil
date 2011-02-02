#include "Hdf.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name hdf5
#endif

BEG_METIL_NAMESPACE;

Hdf::Hdf() : h5_file( 0 ) {
}

Hdf::Hdf( const String &filename ) : h5_file( 0 ) {
    open( filename );
}

Hdf::~Hdf() {
}

void Hdf::open( const String &filename ) {
    if ( h5_file )
        H5Fclose( h5_file );
    h5_file = H5Fcreate( filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT );
}

END_METIL_NAMESPACE;
