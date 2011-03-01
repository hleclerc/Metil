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
    BasicVec<String> list_dir( const String &dir ) const;

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

    // write tensorial data
    template<class T,class TV>
    void write( const String &name, T *data, TV size ) {
        write( name, data, size, size );
    }

    template<class TS, class TTV>
    void write_tag( const String &name, TS &tag, TTV tag_value ) {
        hid_t dat = H5Gopen  ( h5_file, name.c_str() );
        hid_t aid = H5Screate( H5S_SCALAR );
        hid_t att = H5Acreate( dat, tag, H5_type<TTV>::res(), aid, H5P_DEFAULT );

        H5Awrite( att, H5_type<TTV>::res(), &tag_value );

        H5Sclose( aid );
        H5Aclose( att );
        H5Gclose( dat );
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

    template<class TV>
    typename EnableIf<(TensorOrder<TV>::res==1)>::T read( const String &name, TV &data ) const {
        BasicVec<int,1> size;
        read_size( name, size );
        data.resize( size[ 0 ] );
        read_data( name, data.ptr(), size, size );
    }

    template<class TS, class TTV>
    void read_tag( const String &name, TS &tag, TTV &tag_value ) {
        hid_t dat = H5Gopen( h5_file, name.c_str() );
        hid_t att = H5Aopen_name( dat, tag );

        H5Aread( att, H5_type<TTV>::res(), &tag_value );

        H5Aclose( att );
        H5Gclose( dat );
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
