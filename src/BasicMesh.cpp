#include "Level1/StringHelp.h"
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


static String str_to_next_quote( const char *&c ) {
    const char *o = c;
    while ( *c and *c != '\'' )
        ++c;
    return NewString( o, c );
}

static void go_to_next_line( const char *&c ) {
    while ( *c and *c != '\n' )
        ++c;
}

static bool read_int( int &res, const char *&c ) {
    // skip spaces
    while ( Level1::is_a_space( *c ) )
        ++c;
    if ( not Level1::is_a_number( *c ) )
        return false;
    res = *c - '0';
    while ( Level1::is_a_number( *(++c) ) )
        res = 10 * res + ( *c - '0' );
    return true;
}

void BasicMesh::load_vtu( const String &filename ) {
    typedef enum { None, PointData, CellData, Points, Cells } Mode;
    File file( filename, "r" );

    int nb_nodes, nb_elems;
    int off_Points, off_connectivity, off_offsets;
    String name;
    Mode mode = None;
    BasicVec<int> connectivity, offsets, types;
    for( const char *c = file.c_str(); *c; ++c ) {
        if ( Level1::strncmp( c, "NumberOfPoints='", 16 ) == 0 ) {
            nb_nodes = Val( str_to_next_quote( c += 16 ) );
            pos_nodes.resize( 3 );
            for( int i = 0; i < 3; ++i )
                pos_nodes[ i ].resize( nb_nodes );
            continue;
        }
        if ( Level1::strncmp( c, "NumberOfCells='", 15 ) == 0 ) {
            nb_elems = Val( str_to_next_quote( c += 16 ) );
            continue;
        }
        if ( Level1::strncmp( c, "Name='", 6 ) == 0 ) {
            name = str_to_next_quote( c += 6 );
            continue;
        }

        if ( Level1::strncmp( c, "<Points>"   , 8  ) == 0 ) { mode = Points   ; continue; }
        if ( Level1::strncmp( c, "<Cells>"    , 7  ) == 0 ) { mode = Cells    ; continue; }
        if ( Level1::strncmp( c, "<PointData>", 11 ) == 0 ) { mode = PointData; continue; }
        if ( Level1::strncmp( c, "<CellData>" , 10 ) == 0 ) { mode = CellData ; continue; }

        if ( Level1::strncmp( c, "offset='" , 8 ) == 0 ) {
            int off = Val( str_to_next_quote( c += 8 ) );
            switch ( mode ) {
            case None: break;
            case PointData: break;
            case CellData: break;
            case Points: off_Points = off;
            case Cells: break;
            }
        }

        if ( Level1::strncmp( c, "format='ascii'" , 14 ) == 0 ) {
            go_to_next_line( c += 14 );
            if ( mode == Cells ) {
                int t;
                if ( name == "connectivity" ) {
                    while ( read_int( t, c ) )
                        connectivity << t;
                    continue;
                }
                if ( name == "offsets" ) {
                    while ( read_int( t, c ) )
                        offsets << t;
                    continue;
                }
                if ( name == "types" ) {
                    while ( read_int( t, c ) )
                        types << t;
                    continue;
                }
            }
        }
    }
    PRINT( off_Points );
    PRINT( types.size() );
}

END_METIL_NAMESPACE;


