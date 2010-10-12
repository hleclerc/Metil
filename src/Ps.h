#ifndef PS_H
#define PS_H

#include "TypeConfig.h"
#include "MachineId.h"

BEG_METIL_NAMESPACE;

/**
  A pointer, with associated number of items (size) and reserved size in memory
*/
template<class T>
struct Ps {
    Ps() : data( 0 ), size( 1 ), rese( 0 ), pos( MachineId::cpu( 0 ) ) {}
    Ps( T *data, ST size, ST rese, MachineId pos ) : data( data ), size( size ), rese( rese ), pos( pos ) {}

    const T &operator[]( ST i ) const { return data[ i ]; }
    T &operator[]( ST i ) { return data[ i ]; }

    const T &operator*() const { return *data; }
    T &operator*() { return *data; }

    const T *operator->() const { return data; }
    T *operator->() { return data; }

    const T *ptr() const { return data; }
    T *ptr() { return data; }

    ST nb_items() const { return size; }
    ST size_mem() const { return rese; }

    T *data;
    ST size; ///< nb (consecutive) pointed items
    ST rese; ///< in bytes
    MachineId pos; ///< machine id (-1 -> cpu, 0 -> gpu board 0, ...)
};

END_METIL_NAMESPACE;

#endif // PS_H
