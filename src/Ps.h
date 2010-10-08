#ifndef PS_H
#define PS_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

/**
  A pointer, with associated number of items (size) and reserved size in memory
*/
template<class T>
struct Ps {
    Ps() : data( 0 ), size( 0 ), rese( 0 ) {}
    Ps( T *data, ST size, ST rese ) : data( data ), size( size ), rese( rese ) {}

    const T &operator[]( ST i ) const { return data[ i ]; }
    T &operator[]( ST i ) { return data[ i ]; }

    const T &operator*() const { return *data; }
    T &operator*() { return *data; }

    const T *operator->() const { return data; }
    T *operator->() { return data; }

    T *data;
    ST size; ///< nb (consecutive) pointed items
    ST rese; ///< in bytes
};

END_METIL_NAMESPACE;

#endif // PS_H
