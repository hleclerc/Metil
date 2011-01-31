#include "Hdf.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name hdf5
#endif

BEG_METIL_NAMESPACE;

Hdf::Hdf() : h5_file( 0 ) {
}

Hdf::Hdf( const String &filename, bool clear_old ) : h5_file( 0 ) {
    open( filename, clear_old );
}

Hdf::~Hdf() {
}

void Hdf::open( const String &filename, bool clear_old ) {
    if ( h5_file )
        H5Fclose( h5_file );
    if ( clear_old )
        h5_file = H5Fcreate( filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT );
    else
        h5_file = H5Fopen( filename.c_str(), H5F_ACC_RDWR | H5F_ACC_CREAT, H5P_DEFAULT );
}

END_METIL_NAMESPACE;
