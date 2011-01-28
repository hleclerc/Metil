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
    Hdf( const String &filename );
    ~Hdf();

    void open( const String &filename );
    void close();

    // write tensorial data
    template<class T,class TV>
    void write( const String &name, T *data, TV size, TV rese ) {
        check_grp( name );

        int _dim = size.size();
        BasicVec<hsize_t,TV::static_size> _size( Size(), _dim );
        BasicVec<hsize_t,TV::static_size> _rese( Size(), _dim );
        for( int d = 0; d < _dim; ++d ) {
            _size[ _dim - 1 - d ] = size[ d ];
            _rese[ _dim - 1 - d ] = rese[ d ];
        }

        hid_t dataspace = H5Screate_simple( _dim, _size.ptr(), _rese.ptr() );
        hid_t datatype  = H5Tcopy( H5_type<T>::res() ); // H5Tset_order( datatype, H5T_ORDER_LE );
        hid_t dataset   = H5Dcreate( h5_file, name.c_str(), datatype, dataspace, H5P_DEFAULT );

        H5Dwrite( dataset, H5_type<T>::res(), H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

        H5Sclose( dataspace );
        H5Tclose( datatype  );
        H5Dclose( dataset   );
    }

    template<class T,class TV>
    void write( const String &name, T *data, TV size ) {
        write( name, data, size, size );
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
        PRINT( grp );
        if ( not groups.count( grp ) )
            groups[ grp ] = H5Gcreate( h5_file, grp.c_str(), 0 );
    }

    std::map<String,hid_t> groups;
    hid_t h5_file;
};

END_METIL_NAMESPACE;

#endif // HDF_H
