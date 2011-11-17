#ifndef RECTITER_H
#define RECTITER_H

#include "BasicVec.h"

BEG_METIL_NAMESPACE;

/// allows to sweep a multidimensional box, Pt \in [beg,end[
template<class T,int dim>
class RectIter {
public:
    typedef BasicVec<T,dim> TV;

    __inline__ RectIter( TV beg, TV end, TV increment = T( 1 ) ) : pos( beg ), beg( beg ), end( end ), inc( increment ) {
    }

    __inline__ RectIter( TV end ) : pos( 0 ), beg( 0 ), end( end ), inc( 1 ) {
    }

    __inline__ operator bool() const { return ( inc[ dim - 1 ] > 0 ? pos[ dim - 1 ] < end[ dim - 1 ] : pos[ dim - 1 ] > end[ dim - 1 ] ); }

    __inline__ RectIter &operator++() {
        pos[0] += inc[0];
        for( int d = 0; d < dim - 1; d++ ) {
            if ( inc[ d ] > 0 ? pos[ d ] >= end[ d ] : pos[ d ] <= end[ d ] ) {
                pos[ d ] = beg[ d ];
                pos[ d + 1 ] += inc[ d + 1 ];
            } else
                return *this;
        }
        return *this;
    }

    __inline__ T sum_pos() const { ///< pos[0] + pos[1] + ...
        T res = 0;
        for( int i = 0; i < dim; ++i )
            res += pos[i];
        return res;
    }

    __inline__ int index( TV p ) const {
        int res = 0;
        for( int d = 0, c = 1; d < dim; ++d ) {
            res += c * p[ d ];
            c *= ( end[ d ] - beg[ d ] ) / inc[ d ];
        }
        return res;
    }

    __inline__ int index() const {
        return index( pos );
    }
    
    static __inline__ TV _reverse_index( T index, TV size, N<1> ) { return index; }
    static __inline__ TV _reverse_index( T index, TV size, N<2> ) { return TV( index % size[ 0 ], index / size[ 0 ] ); }
    static __inline__ TV _reverse_index( T index, TV size, N<3> ) { return TV( index % size[ 0 ], index / size[ 0 ] % size[ 1 ], index / size[ 0 ] / size[ 1 ] ); }
    
    static __inline__ TV reverse_index( T index, TV size ) {
        return _reverse_index( index, size, N<dim>() );
    }

    static __inline__ int index( TV p, TV rese ) {
        int res = 0;
        for( int d = 0, c = 1; d < dim; ++d ) {
            res += c * p[ d ];
            c *= rese[ d ];
        }
        return res;
    }
    
    TV pos; ///< position
    TV beg; ///< first corner of the box
    TV end; ///< second corner of the box
    TV inc; ///< increment
};

END_METIL_NAMESPACE;

#endif // RECTITER_H
