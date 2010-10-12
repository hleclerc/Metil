#include "BasicMesh.h"

BEG_METIL_NAMESPACE;

void BasicMesh::add_node( T x, T y, T z ) {
    if ( pos_nodes.size() < 3 )
        pos_nodes.resize( 3 );
    pos_nodes[ 0 ] << x;
    pos_nodes[ 1 ] << y;
    pos_nodes[ 2 ] << z;
}

void BasicMesh::add_elem( const ElemType *elem_type, T x, T y, T z ) {
    ElemGroup *eg = find_group( elem_type );
    eg->connec.resize( 3 );
    eg->connec[ 0 ] << x;
    eg->connec[ 1 ] << y;
    eg->connec[ 2 ] << z;
}

BasicMesh::ElemGroup *BasicMesh::find_group( const ElemType *elem_type ) {
    for( ST i = 0; i < elem_groups.size(); ++i )
        if ( elem_groups[ i ].elem_type == elem_type )
            return &elem_groups[ i ];
    return elem_groups.push_back( elem_type );
}

END_METIL_NAMESPACE;
