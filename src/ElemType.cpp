#include "ElemType.h"
#include "String.h"

BEG_METIL_NAMESPACE;

struct ElemTypeTriangle : public ElemType {
    virtual int elem_id() const { return 0; }
    virtual int nvi() const { return 2; }
    virtual void make_rect( const BasicVec<float> &X0, const BasicVec<float> &X1, const BasicVec<int> &Xd, BasicVec<BasicVec<float> > &pos_nodes, BasicVec<BasicVec<int> > &connec ) const {
        // nodes
        if ( pos_nodes.size() < X0.size() )
            pos_nodes.resize( X0.size() );
        ST os = pos_nodes[ 0 ].size();
        for( int y = 0; y < Xd[ 1 ]; ++y ) {
            for( int x = 0; x < Xd[ 0 ]; ++x ) {
                pos_nodes[ 0 ] << X0[ 0 ] + ( X1[ 0 ] - X0[ 0 ] ) * x / ( Xd[ 0 ] - 1 );
                pos_nodes[ 1 ] << X0[ 1 ] + ( X1[ 1 ] - X0[ 1 ] ) * y / ( Xd[ 1 ] - 1 );
                if ( X0.size() >= 3 )
                    pos_nodes[ 2 ] << X0[ 2 ] + ( X1[ 2 ] - X0[ 2 ] ) * y / ( Xd[ 2 ] - 1 );
            }
        }
        // elems
        if ( connec.size() < 3 )
            connec.resize( 3 );
        for( int y = 0; y < Xd[ 1 ] - 1; ++y ) {
            for( int x = 0; x < Xd[ 0 ] - 1; ++x ) {
                connec[ 0 ] << os + Xd[ 0 ] * ( y + 0 ) + ( x + 0 );
                connec[ 1 ] << os + Xd[ 0 ] * ( y + 0 ) + ( x + 1 );
                connec[ 2 ] << os + Xd[ 0 ] * ( y + 1 ) + ( x + 0 );

                connec[ 0 ] << os + Xd[ 0 ] * ( y + 1 ) + ( x + 1 );
                connec[ 2 ] << os + Xd[ 0 ] * ( y + 1 ) + ( x + 0 );
                connec[ 1 ] << os + Xd[ 0 ] * ( y + 0 ) + ( x + 1 );
            }
        }
    }
};

#define IP( E ) \
    ElemType##E inst_elem_type_##E; \
    const ElemType *const elem_type_##E = &inst_elem_type_##E

IP( Triangle );

END_METIL_NAMESPACE;
