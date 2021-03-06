#ifndef MAT_H
#define MAT_H

#include "Vec.h"

BEG_METIL_NAMESPACE;

/**
*/
class Mat : public Array<Val> {
public:
    Mat();
    Mat( ST r, ST c, Level1::Type *base_type = 0 );

    // specialisation for 2 args -> ( row, col ) which is inverted / Arrays
    Val operator()( const Val &a, const Val &b ) const { return Array<Val>::operator()( b, a ); }
    Val operator()( const Val &a, const Val &b ) { return Array<Val>::operator()( b, a ); }

    Val nb_rows() const { return size( 1 ); }
    Val nb_cols() const { return size( 0 ); }
};

END_METIL_NAMESPACE;

#endif // MAT_H
