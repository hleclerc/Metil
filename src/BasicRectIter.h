#ifndef BASICRECTITER_H
#define BASICRECTITER_H

#include "BasicVec.h"

BEG_METIL_NAMESPACE;

/// allows to sweep a multidimensional box, Pt \in [beg,end[
template<class T,int dim>
class BasicRectIter {
public:
    typedef BasicVec<T,dim> TV;

    BasicRectIter( TV beg, TV end, TV increment = T( 1 ) ) : pos( beg ), beg( beg ), end( end ), inc( increment ) {
    }

    operator bool() const { return ( inc[ dim - 1 ] > 0 ? pos[ dim - 1 ] < end[ dim - 1 ] : pos[ dim - 1 ] > end[ dim - 1 ] ); }

    BasicRectIter &operator++() {
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

    T sum_pos() const { ///< pos[0] + pos[1] + ...
        T res = 0;
        for( int i = 0; i < dim; ++i )
            res += pos[i];
        return res;
    }

    int index( TV p ) const {
        int res = 0;
        for( int d = 0, c = 1; d < dim; ++d ) {
            res += c * p[ d ];
            c *= ( end[ d ] - beg[ d ] ) / inc[ d ];
        }
        return res;
    }


    TV pos; ///< position
    TV beg; ///< first corner of the box
    TV end; ///< second corner of the box
    TV inc; ///< increment
};

END_METIL_NAMESPACE;

#endif // BASICRECTITER_H
