#include "BasicMesh.h"
#include "String.h"

BEG_METIL_NAMESPACE;

void BasicMesh::add_node( T x, T y, T z ) {
    if ( pos_nodes.size() < 3 )
        pos_nodes.resize( 3 );
    pos_nodes[ 0 ] << x;
    pos_nodes[ 1 ] << y;
    pos_nodes[ 2 ] << z;
}

void BasicMesh::add_node( T x, T y ) {
    if ( pos_nodes.size() < 2 )
        pos_nodes.resize( 2 );
    pos_nodes[ 0 ] << x;
    pos_nodes[ 1 ] << y;
}

void BasicMesh::add_elem( const ElemType *elem_type, I x, I y, I z ) {
    ElemGroup *eg = find_group( elem_type );
    eg->connec.resize( 3 );
    eg->connec[ 0 ] << x;
    eg->connec[ 1 ] << y;
    eg->connec[ 2 ] << z;
}

ST BasicMesh::nb_elements() const {
    ST res = 0;
    for( ST i = 0; i < elem_groups.size(); ++i )
        res += elem_groups[ i ].connec[ 0 ].size();
    return res;
}

BasicMesh::ElemGroup *BasicMesh::find_group( const ElemType *elem_type ) {
    for( ST i = 0; i < elem_groups.size(); ++i )
        if ( elem_groups[ i ].elem_type == elem_type )
            return &elem_groups[ i ];
    return elem_groups.push_back( elem_type );
}

void BasicMesh::make_rect( const ElemType *elem_type, BasicVec<T> X0, BasicVec<T> X1, BasicVec<I> Xd ) {
    while ( X0.size() < elem_type->nvi() ) X0 << T( X0[ 0 ] );
    while ( X1.size() < elem_type->nvi() ) X1 << T( X1[ 0 ] );
    while ( Xd.size() < elem_type->nvi() ) Xd << I( Xd[ 0 ] );

    ElemGroup *eg = find_group( elem_type );
    elem_type->make_rect( X0, X1, Xd, pos_nodes, eg->connec );
}

ST BasicMesh::nb_nodes() const {
    return pos_nodes.size() ? pos_nodes[ 0 ].size() : 0;
}

void BasicMesh::update_node_to_elem() {
    node_to_elem.resize( nb_nodes() );
    for( ST i = 0; i < node_to_elem.size(); ++i )
        node_to_elem[ i ].resize( 0 );
    //
    for( ST i = 0; i < elem_groups.size(); ++i )
        for( ST j = 0; j < elem_groups[ i ].nb_elements(); ++j )
            for( ST k = 0; k < elem_groups[ i ].connec.size(); ++k )
                node_to_elem[ elem_groups[ i ].connec[ k ][ j ] ].push_back( i, j, k );
}

END_METIL_NAMESPACE;

