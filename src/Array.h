#ifndef ARRAY_H
#define ARRAY_H

#include "String.h"

BEG_METIL_NAMESPACE;

class Vec;

/**
  multidimensionnal array

*/
template<class T>
struct Array : public Level1::MO {
    Array( ST dim ) {
        static Level1::Type *lst[] = {
            &Level1::metil_type_cst_Array_4NULL_0,
            &Level1::metil_type_cst_Array_4NULL_1_0_0,
            &Level1::metil_type_cst_Array_4NULL_2_0_0_0_0,
            &Level1::metil_type_cst_Array_4NULL_3_0_0_0_0_0_0,
            &Level1::metil_type_cst_Array_4NULL_4_0_0_0_0_0_0_0_0,
            &Level1::metil_type_cst_Array_4NULL_5_0_0_0_0_0_0_0_0_0_0,
        };
        ASSERT( dim < 6, "TODO" );
        type = lst[ dim ];
    }
    Array( const Array &a ) : MO( CM_1( copy, a ) ) {}
    Array &operator=( const Array &a ) { CM_2( reassign, *this, a ); return *this; }

    ~Array() { CM_1( del, *this ); }

    Level1::Type *base_type() const { MO res = CM_1( base_type, *this ); return res.type; }

    Val dim() const { return CM_1( dim, *this ); }
    Val size() const { return CM_1( size, *this ); }
    // Val size( int i ) const { return sizes()[ i ]; }
    Vec sizes() const;

    // 1 arg
    T operator[]( const Val &a ) const { return CM_2( select_C, *this, a ); }
    T operator()( const Val &a ) const { return CM_2( select_C, *this, a ); }

    T operator[]( const Val &a ) { return CM_2( select, *this, a ); }
    T operator()( const Val &a ) { return CM_2( select, *this, a ); }

    // 2 args
    T operator()( const Val &a, const Val &b ) const {
        Level1::MO data[] = { a, b };
        return CM_2( select_C, *this, MO( data, &Level1::metil_type_cst_Array_4NULL_1_2_2 ) );
    }

    T operator()( const Val &a, const Val &b ) {
        Level1::MO data[] = { a, b };
        return CM_2( select, *this, MO( data, &Level1::metil_type_cst_Array_4NULL_1_2_2 ) );
    }


    /// obj[ ... ] = val
    void set_values( const Val &val ) { CM_2( set_values, *this, val ); }

protected:
    Array() {}
    Array( Level1::MO mo ) : MO( mo ) {}
};

template<class T> T min( const Array<T> &a ) { return CM_1( min_1, a ); }
template<class T> T max( const Array<T> &a ) { return CM_1( max_1, a ); }
template<class T> T sum( const Array<T> &a ) { return CM_1( add_1, a ); }

template<class T> T product( const Array<T> &a ) { return CM_1( mul_1, a ); }

END_METIL_NAMESPACE;

#include "Vec.h"

BEG_METIL_NAMESPACE;
template<class T>
Vec Array<T>::sizes() const { return type->sizes( *this ); }
END_METIL_NAMESPACE;

#endif // ARRAY_H
