#ifndef HDF_H
#define HDF_H

#include "BasicVec.h"
#include "String.h"

#include <hdf5.h>
#include <map>

BEG_METIL_NAMESPACE;

template<class T> struct H5_type {};

template<> struct H5_type<  signed char > { static hid_t res() { return H5T_NATIVE_SCHAR  ; } };
template<> struct H5_type<unsigned char > { static hid_t res() { return H5T_NATIVE_UCHAR  ; } };
template<> struct H5_type<  signed short> { static hid_t res() { return H5T_NATIVE_SHORT  ; } };
template<> struct H5_type<unsigned short> { static hid_t res() { return H5T_NATIVE_USHORT ; } };
template<> struct H5_type<  signed   int> { static hid_t res() { return H5T_NATIVE_INT    ; } };
template<> struct H5_type<unsigned   int> { static hid_t res() { return H5T_NATIVE_UINT   ; } };
template<> struct H5_type<  signed  long> { static hid_t res() { return H5T_NATIVE_LONG   ; } };
template<> struct H5_type<unsigned  long> { static hid_t res() { return H5T_NATIVE_ULONG  ; } };
template<> struct H5_type<     long long> { static hid_t res() { return H5T_NATIVE_LLONG  ; } };
template<> struct H5_type<         float> { static hid_t res() { return H5T_NATIVE_FLOAT  ; } };
template<> struct H5_type<        double> { static hid_t res() { return H5T_NATIVE_DOUBLE ; } };
template<> struct H5_type<   long double> { static hid_t res() { return H5T_NATIVE_LDOUBLE; } };


/**

*/
class Hdf {
public:
    Hdf();
    Hdf( const String &filename, bool clear_old = false );
    ~Hdf();

    void open( const String &filename, bool clear_old = false );
    void close();

    // write tensorial data
    template<class T,class TV>
    void write( const String &name, const T *data, TV size, TV rese ) {
        check_grp( name );
        if ( H5Lexists( h5_file, name.c_str(), H5P_DEFAULT ) )
            H5Gunlink( h5_file, name.c_str() );

        int _dim = size.size();
        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
        for( int d = 0; d < _dim; ++d ) {
            _size[ _dim - 1 - d ] = size[ d ];
            _rese[ _dim - 1 - d ] = rese[ d ];
        }

        hid_t dataspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );
        hid_t datatype  = H5Tcopy( H5_type<T>::res() );
        hid_t dataset   = H5Dcreate( h5_file, name.c_str(), datatype, dataspace, H5P_DEFAULT );

        H5Dwrite( dataset, H5_type<T>::res(), H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

        H5Sclose( dataspace );
        H5Tclose( datatype  );
        H5Dclose( dataset   );
    }

    template<class T,class TV>
    void write( const String &name, T *data, TV size, TV rese, BasicVec<String> &tags, BasicVec<String> &tags_value ) {
        check_grp( name );
        if ( H5Lexists( h5_file, name.c_str(), H5P_DEFAULT ) )
            H5Gunlink( h5_file, name.c_str() );

        int _dim = size.size();
        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
        for( int d = 0; d < _dim; ++d ) {
            _size[ _dim - 1 - d ] = size[ d ];
            _rese[ _dim - 1 - d ] = rese[ d ];
        }

        hid_t dataspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );
        hid_t datatype  = H5Tcopy( H5_type<T>::res() );
        hid_t dataset   = H5Dcreate( h5_file, name.c_str(), datatype, dataspace, H5P_DEFAULT );

        H5Dwrite( dataset, H5_type<T>::res(), H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

        // Add tags and corresponding values to a dataset
        for(unsigned i=0;i<tags_value.size();i++){
            int dim_tag = tags_value[ i ].size();
            const char *string_att[ 1 ] = { tags_value[ i ].c_str() };
            hsize_t dims[ 1 ] = { 1 };
            hid_t aid   = H5Screate_simple( 1, dims, NULL );
            hid_t atype = H5Tcopy( H5T_C_S1 );
            H5Tset_size( atype, H5T_VARIABLE );
            hid_t attr = H5Acreate( dataset, tags[i].c_str(), atype, aid, H5P_DEFAULT );
            H5Awrite( attr, atype, &string_att );
            H5Sclose( aid );
            H5Aclose( attr );
        } 
        H5Sclose( dataspace );
        H5Tclose( datatype  );
        H5Dclose( dataset   );
    }

    template<class TS, class TTV>
    void add_tag( const String &name, TS &tag, TTV tag_value ) {
        hid_t dataset = H5Gopen( h5_file, name.c_str() );
        hid_t aid     = H5Screate( H5S_SCALAR );
        hid_t attr    = H5Acreate( dataset, tag, H5_type<TTV>::res(), aid, H5P_DEFAULT );

        H5Awrite( attr, H5_type<TTV>::res(), &tag_value );

        H5Sclose( aid     );
        H5Aclose( attr    );
        H5Gclose( dataset );
    }

    template<class TS, class TTV>
    void read_tag( const String &name, TS &tag, TTV &tag_value ) {
        hid_t dataset = H5Gopen( h5_file, name.c_str() );
        hid_t attr    = H5Aopen_name(dataset,tag);

        H5Aread ( attr, H5_type<TTV>::res(), &tag_value );

        H5Aclose( attr    );
        H5Gclose( dataset );
    }


    template<class TS>
    void add_tags( const String &name, TS &tags, TS &tags_value) {
        hid_t dataset = H5Gopen( h5_file, name.c_str() );

        //Add tags and corresponding values to a dataset
        for(unsigned i=0;i<tags_value.size();i++){
            int dim_tag = tags_value[i].size();
            const char *string_att[ 1 ]={ tags_value[i].c_str() };
            hsize_t dims[ 1 ] = { 1 };
            hid_t aid  = H5Screate_simple( 1, dims, NULL );
            hid_t atype = H5Tcopy( H5T_C_S1 );
            H5Tset_size( atype, H5T_VARIABLE );
            hid_t attr = H5Acreate( dataset, tags[i].c_str(), atype, aid, H5P_DEFAULT );
            H5Awrite( attr, atype, &string_att );
            H5Sclose( aid  );
            H5Aclose( attr );
        } 
        H5Gclose( dataset );
    }
    

    template<class TS>
    void read_tags( const String &name , TS &tags, TS &tags_value) {
        hid_t dataset = H5Gopen( h5_file, name.c_str() );

        //read attribute string from a vec of tags
        tags_value.resize(tags.size()); 
        
        for(unsigned i=0;i<tags.size();i++){
            char *string_attr[ 1 ];
            hid_t attr  = H5Aopen_name( dataset, tags[i].c_str() );
            hid_t ftype = H5Aget_type( attr  );
            // size_t size_string = H5Tget_size( ftype );
            hid_t atype = H5Tget_native_type( ftype, H5T_DIR_ASCEND );
            H5Aread( attr, atype, &string_attr );
            tags_value[ i ] = string_attr[0];
            free( string_attr[ 0 ] );
            H5Aclose( attr  );
            H5Tclose( atype );
        }

        H5Gclose( dataset );
    }

    // write tensorial data
    template<class T,class TV>
    void write( const String &name, T *data, TV size ) {
        write( name, data, size, size );
    }
    
    template<class T,class TV>
    void write( const String &name, T *data, TV size , BasicVec<String> &tags, BasicVec<String> &tags_value) {
        write( name, data, size, size ,tags, tags_value );
    }
    
    template<class T,class TV>
    void add_tags( const String &name, T *data, TV size, BasicVec<String> &tags, BasicVec<String> &tags_value) {
        add_tags( name, data, size, size ,tags, tags_value );
    }

    template<class TV>
    void read_size( const String &name, TV &size ) const {
        hid_t dataset = H5Dopen( h5_file, name.c_str() );
        hid_t dataspace = H5Dget_space( dataset );
        //
        BasicVec<hsize_t> tmp( Size(), H5Sget_simple_extent_ndims( dataspace ) );
        H5Sget_simple_extent_dims( dataspace, tmp.ptr(), NULL );
        size.resize( tmp.size() );
        for( int d = 0; d < tmp.size(); ++d )
            size[ tmp.size() - 1 - d ] = tmp[ d ];
        //
        H5Dclose(dataset);
        H5Sclose(dataspace);
    }

    template<class T,class TV>
    void read_data( const String &name, T *data, const TV &size, const TV &rese ) const {
        // filespace
        hid_t dataset = H5Dopen( h5_file, name.c_str() );
        hid_t filespace = H5Dget_space( dataset );

        // memspace
        int _dim = size.size();
        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
        for( int d = 0; d < _dim; ++d ) {
            _size[ _dim - 1 - d ] = size[ d ];
            _rese[ _dim - 1 - d ] = rese[ d ];
        }
        hid_t memspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );

        // read
        H5Dread( dataset, H5_type<T>::res(), memspace, filespace, H5P_DEFAULT, data );

        // close
        H5Sclose( memspace );
        H5Sclose( filespace );
        H5Dclose( dataset );
    }
    
    //read data and tags
    template<class T,class TV>
    void read_data( const String &name, T *data, const TV &size, const TV &rese, BasicVec<String> &tags, BasicVec<String> &tags_value ) const {
        // filespace
        hid_t dataset = H5Dopen( h5_file, name.c_str() );
        hid_t filespace = H5Dget_space( dataset );

        // memspace
        int _dim = size.size();
        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
        for( int d = 0; d < _dim; ++d ) {
            _size[ _dim - 1 - d ] = size[ d ];
            _rese[ _dim - 1 - d ] = rese[ d ];
        }
        hid_t memspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );

        // read dataset
        H5Dread( dataset, H5_type<T>::res(), memspace, filespace, H5P_DEFAULT, data );

        //read attribute string from a vec of tags
        tags_value.resize( tags.size() );
        for(unsigned i=0;i<tags.size();i++){
            char *string_attr[1];
            hid_t attr = H5Aopen_name(dataset, tags[i].c_str());
            hid_t ftype = H5Aget_type(attr);
            // size_t size_string = H5Tget_size( ftype );
            hid_t atype = H5Tget_native_type( ftype, H5T_DIR_ASCEND);
            H5Aread( attr, atype, &string_attr );
            tags_value[ i ] = string_attr[ 0 ];
            free( string_attr[ 0 ] );
            H5Aclose( attr  );
            H5Tclose( atype );
        }

        // close
        H5Sclose( memspace  );
        H5Sclose( filespace );
        H5Dclose( dataset   );
    }

private:
    void check_grp( const String &name ) {
        // find grp
        int off = name.rfind( '/' );
        if ( off <= 0 )
            return;
        const String &grp = name.beg_upto( off );
        check_grp( grp );
        //
        if ( not H5Lexists( h5_file, grp.c_str(), H5P_DEFAULT ) )
            H5Gclose( H5Gcreate( h5_file, grp.c_str(), 0 ) );
    }

    hid_t h5_file;
};

END_METIL_NAMESPACE;

#endif // HDF_H