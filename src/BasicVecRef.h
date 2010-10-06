#ifndef BASICVECREF_H
#define BASICVECREF_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

/**
*/
template<class T>
struct BasicVecRef {
    __inline__ T &operator[]( ST index ) { return data_[ index ]; }
    __inline__ const T &operator[]( ST index ) const { return data_[ index ]; }
    __inline__ ST size() const { return size_; }
    __inline__ ST rese() const { return rese_; }

    template<class TS>
    void write_str( TS &os ) const {
        if ( size() ) {
            os << operator[]( 0 );
            for( ST i = 1; i < size(); ++i ) {
                os.write_separator( 0 );
                os << operator[]( i );
            }
        }
    }

    ST  size_;
    ST  rese_;
    T  *data_;
};

END_METIL_NAMESPACE;

#endif // BASICVECREF_H
