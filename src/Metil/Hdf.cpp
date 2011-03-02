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
    if ( h5_file )
        H5Fclose( h5_file );
}

void Hdf::open( const String &filename, bool clear_old ) {
    if ( h5_file )
        H5Fclose( h5_file );
    // create or read a previously created file
    if ( clear_old )
        h5_file = H5Fcreate( filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT );
    else
        h5_file = H5Fopen( filename.c_str(), H5F_ACC_RDWR | H5F_ACC_CREAT, H5P_DEFAULT );
}

static herr_t file_info( hid_t, const char *name, void *op_data ) {
    *reinterpret_cast<BasicVec<String> *>( op_data ) << NewString( name );
    return 0;
}

BasicVec<String> Hdf::list_dir( const String &dir ) const {
    BasicVec<String> res;
    H5Giterate( h5_file, dir.c_str(), NULL, file_info, &res );
    return res;
}

void Hdf::read_tag( const String &name, const String &tag, String &tag_value, bool group ) {
    hid_t dataset = group ? H5Gopen( h5_file, name.c_str() ) : H5Dopen( h5_file, name.c_str() );
    hid_t attr    = H5Aopen_name( dataset, tag.c_str() );
    hid_t ftype   = H5Aget_type( attr );
    size_t size   = H5Tget_size( ftype );
    hid_t atype   = H5Tget_native_type( ftype, H5T_DIR_ASCEND );

    char *string_attr = (char *)MALLOC( size );
    H5Aread( attr, atype, string_attr );
    tag_value << string_attr;
    FREE( string_attr, size );

    H5Aclose( attr    );
    H5Tclose( atype   );
    if ( group )
        H5Gclose( dataset );
    else
        H5Dclose( dataset );
}

void Hdf::read_group_size( const String &name, int &size ) const {
    hid_t dataset = H5Gopen( h5_file, name.c_str() );

    H5G_info_t group_info;
    H5Gget_info( dataset, &group_info );
    size = group_info.nlinks;

    H5Gclose(dataset);
}

void Hdf::read_size( const String &name, int &size ) const {
    BasicVec<int> size_vec;
    read_size( name, size_vec );
    size = size_vec[ 0 ];
}

END_METIL_NAMESPACE;
