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
    Array( Level1::MO mo ) : MO( mo ) {}

    ~Array() { CM_1( del, *this ); }

    Val size() const { return type->size( *this ); }
    Val size( int i ) const { return sizes()[ i ]; }
    Array<Val> sizes() const { return type->sizes( *this ); }

    // 1 arg
    T operator[]( const Val &a ) const { return CM_2( select_C, *this, a ); }
    T operator()( const Val &a ) const { return CM_2( select_C, *this, a ); }

    T operator[]( const Val &a ) { return CM_2( select, *this, a ); }
    T operator()( const Val &a ) { return CM_2( select, *this, a ); }

    // 2 args
    T operator()( const Val &a, const Val &b ) const {
        Level1::MO data[] = { a, b };
        return CM_2( select_C, *this, MO( data, &Level1::metil_type_ref_Array_4NULL_1_2_2 ) );
    }

    T operator()( const Val &a, const Val &b ) {
        Level1::MO data[] = { a, b };
        return CM_2( select, *this, MO( data, &Level1::metil_type_ref_Array_4NULL_1_2_2 ) );
    }

    /// obj[ ... ] = val
    void set_values( const Val &val ) { CM_2( set_values, *this, val ); }

    T min() const { return CM_1( min_1, *this ); }
    T max() const { return CM_1( max_1, *this ); }

protected:
    Array() {}
};

END_METIL_NAMESPACE;

#endif // ARRAY_H
