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

END_METIL_NAMESPACE;

//    // read data and tags
//    template<class T,class TV>
//    void read_data( const String &name, T *data, const TV &size, const TV &rese, BasicVec<String> &tags, BasicVec<String> &tags_value ) const {
//        // filespace
//        hid_t dataset = H5Dopen( h5_file, name.c_str() );
//        hid_t filespace = H5Dget_space( dataset );

//        // memspace
//        int _dim = size.size();
//        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
//        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
//        for( int d = 0; d < _dim; ++d ) {
//            _size[ _dim - 1 - d ] = size[ d ];
//            _rese[ _dim - 1 - d ] = rese[ d ];
//        }
//        hid_t memspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );

//        // read dataset
//        H5Dread( dataset, H5_type<T>::res(), memspace, filespace, H5P_DEFAULT, data );

//        //read attribute string from a vec of tags
//        tags_value.resize( tags.size() );
//        for(unsigned i=0;i<tags.size();i++){
//            char *string_attr[1];
//            hid_t attr = H5Aopen_name(dataset, tags[i].c_str());
//            hid_t ftype = H5Aget_type(attr);
//            // size_t size_string = H5Tget_size( ftype );
//            hid_t atype = H5Tget_native_type( ftype, H5T_DIR_ASCEND);
//            H5Aread( attr, atype, &string_attr );
//            tags_value[ i ] = string_attr[ 0 ];
//            free( string_attr[ 0 ] );
//            H5Aclose( attr  );
//            H5Tclose( atype );
//        }

//        // close
//        H5Sclose( memspace  );
//        H5Sclose( filespace );
//        H5Dclose( dataset   );
//    }

//    template<class T,class TV>
//    void write( const String &name, T *data, TV size, TV rese, BasicVec<String> &tags, BasicVec<String> &tags_value ) {
//        check_grp( name );
//        if ( H5Lexists( h5_file, name.c_str(), H5P_DEFAULT ) )
//            H5Gunlink( h5_file, name.c_str() );

//        int _dim = size.size();
//        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
//        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
//        for( int d = 0; d < _dim; ++d ) {
//            _size[ _dim - 1 - d ] = size[ d ];
//            _rese[ _dim - 1 - d ] = rese[ d ];
//        }

//        hid_t dataspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );
//        hid_t datatype  = H5Tcopy( H5_type<T>::res() );
//        hid_t dataset   = H5Dcreate( h5_file, name.c_str(), datatype, dataspace, H5P_DEFAULT );

//        H5Dwrite( dataset, H5_type<T>::res(), H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

//        // Add tags and corresponding values to a dataset
//        for(unsigned i=0;i<tags_value.size();i++){
//            int dim_tag = tags_value[ i ].size();
//            const char *string_att[ 1 ] = { tags_value[ i ].c_str() };
//            hsize_t dims[ 1 ] = { 1 };
//            hid_t aid   = H5Screate_simple( 1, dims, NULL );
//            hid_t atype = H5Tcopy( H5T_C_S1 );
//            H5Tset_size( atype, H5T_VARIABLE );
//            hid_t attr = H5Acreate( dataset, tags[i].c_str(), atype, aid, H5P_DEFAULT );
//            H5Awrite( attr, atype, &string_att );
//            H5Sclose( aid );
//            H5Aclose( attr );
//        }
//        H5Sclose( dataspace );
//        H5Tclose( datatype  );
//        H5Dclose( dataset   );
//    }
//template<class TS>
//void add_tags( const String &name, TS &tags, TS &tags_value) {
//    hid_t dataset = H5Gopen( h5_file, name.c_str() );

//    //Add tags and corresponding values to a dataset
//    for(unsigned i=0;i<tags_value.size();i++){
//        int dim_tag = tags_value[i].size();
//        const char *string_att[ 1 ]={ tags_value[i].c_str() };
//        hsize_t dims[ 1 ] = { 1 };
//        hid_t aid  = H5Screate_simple( 1, dims, NULL );
//        hid_t atype = H5Tcopy( H5T_C_S1 );
//        H5Tset_size( atype, H5T_VARIABLE );
//        hid_t attr = H5Acreate( dataset, tags[i].c_str(), atype, aid, H5P_DEFAULT );
//        H5Awrite( attr, atype, &string_att );
//        H5Sclose( aid  );
//        H5Aclose( attr );
//    }
//    H5Gclose( dataset );
//}
//    template<class TS>
//    void read_tags( const String &name , TS &tags, TS &tags_value) {
//        hid_t dataset = H5Gopen( h5_file, name.c_str() );

//        //read attribute string from a vec of tags
//        tags_value.resize(tags.size());

//        for(unsigned i=0;i<tags.size();i++){
//            char *string_attr[ 1 ];
//            hid_t attr  = H5Aopen_name( dataset, tags[i].c_str() );
//            hid_t ftype = H5Aget_type( attr  );
//            // size_t size_string = H5Tget_size( ftype );
//            hid_t atype = H5Tget_native_type( ftype, H5T_DIR_ASCEND );
//            H5Aread( attr, atype, &string_attr );
//            tags_value[ i ] = string_attr[0];
//            free( string_attr[ 0 ] );
//            H5Aclose( attr  );
//            H5Tclose( atype );
//        }

//        H5Gclose( dataset );
//    }
//template<class T,class TV>
//void write( const String &name, T *data, TV size , BasicVec<String> &tags, BasicVec<String> &tags_value) {
//    write( name, data, size, size ,tags, tags_value );
//}

//template<class T,class TV>
//void add_tags( const String &name, T *data, TV size, BasicVec<String> &tags, BasicVec<String> &tags_value) {
//    add_tags( name, data, size, size ,tags, tags_value );
//}
