#include "Level1/StringHelp.h"
#include "BasicMesh.h"
#include "MathBasicVec.h"
#include "Base64.h"

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

struct LField {
    String name;
    int offset;
    int nb_comp;
};

void BasicMesh::load_vtu( const String &filename ) {
    typedef enum { None, PointData, CellData, Points, Cells } Mode;
    File file( filename, "r" );

    // basic init
    pos_nodes.resize( 3 );

    // load data
    int nb_nodes, nb_elems, nb_comp;
    int off_Points = -1, off_connectivity = -1, off_offsets = -1;
    String name;
    Mode mode = None;
    BasicVec<int> connectivity, offsets, types;
    String binary_data;
    BasicVec<LField> l_nodal_fields;
    BasicVec<LField> l_elementary_fields;
    for( const char *c = file.c_str(); *c; ++c ) {
        if ( Level1::strncmp( c, "NumberOfPoints='", 16 ) == 0 ) {
            nb_nodes = Val( str_to_next_quote( c += 16 ) );
            for( int i = 0; i < 3; ++i )
                pos_nodes[ i ].resize( nb_nodes );
            continue;
        }
        if ( Level1::strncmp( c, "NumberOfCells='", 15 ) == 0 ) {
            nb_elems = Val( str_to_next_quote( c += 15 ) );
            continue;
        }
        if ( Level1::strncmp( c, "NumberOfComponents='", 20 ) == 0 ) {
            nb_comp = Val( str_to_next_quote( c += 20 ) );
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
            case None:
                break;
            case PointData: {
                LField *f = l_nodal_fields.push_back();
                f->name = name;
                f->offset = off * 3 / 4;
                f->nb_comp = nb_comp;
                break;
            } case CellData: {
                LField *f = l_elementary_fields.push_back();
                f->name = name;
                f->offset = off * 3 / 4;
                f->nb_comp = nb_comp;
                break;
            } case Points:
                off_Points = off * 3 / 4;
                break;
            case Cells:
                break;
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
        if ( Level1::strncmp( c, "encoding='base64'" , 17 ) == 0 ) {
            while( *c and *c != '_' )
                ++c;
            const char *b = ++c;
            while ( not Level1::is_a_space( *c ) )
                ++c;
            base_64_decode( binary_data, b, c - b );
        }
    }
    const unsigned char *bd = (unsigned char *)binary_data.c_str();

    // pos_nodes
    ASSERT( off_Points >= 0, "..." );
    const double *d_pos_nodes = (const double *)( bd + off_Points + 4 );
    for( int n = 0; n < nb_nodes; ++n )
        for( int d = 0; d < 3; ++d )
            pos_nodes[ d ][ n ] = d_pos_nodes[ 3 * n + d ];

    // nodal fields
    for( int i = 0; i < l_nodal_fields.size(); ++i ) {
        Field *field = nodal_fields.push_back();
        for( int j = 0; j < l_nodal_fields[ i ].name.size(); ++j )
            field->name << l_nodal_fields[ i ].name[ j ];
        PRINT( l_nodal_fields[ i ].name );
        field->data.resize( l_nodal_fields[ i ].nb_comp );
        const double *d_field = (const double *)( bd + l_nodal_fields[ i ].offset + 4 );
        for( int d = 0; d < l_nodal_fields[ i ].nb_comp; ++d ) {
            field->data[ d ].resize( nb_nodes );
            for( int n = 0; n < nb_nodes; ++n )
                field->data[ d ][ n ] = d_field[ l_nodal_fields[ i ].nb_comp * n + d ];
        }
    }

    // elements
    for( int i = 0; i < nb_elems; ++i ) {
        int b = i > 0 ? offsets[ i - 1 ] : 0;
        if ( types[ i ] == 5 ) { // triangle
            add_elem( elem_type_Triangle, connectivity[ b + 0 ], connectivity[ b + 1 ], connectivity[ b + 2 ] );
        }
    }

    // elementary fields
    for( int i = 0; i < l_elementary_fields.size(); ++i ) {
        Field *field = elem_groups[ 0 ].fields.push_back();
        for( int j = 0; j < l_elementary_fields[ i ].name.size(); ++j )
            field->name << l_elementary_fields[ i ].name[ j ];
        PRINT( l_elementary_fields[ i ].name );
        field->data.resize( l_elementary_fields[ i ].nb_comp );
        const double *d_field = (const double *)( bd + l_elementary_fields[ i ].offset + 4 );
        for( int d = 0; d < l_elementary_fields[ i ].nb_comp; ++d ) {
            field->data[ d ].resize( nb_elems );
            for( int n = 0; n < nb_elems; ++n )
                field->data[ d ][ n ] = d_field[ l_elementary_fields[ i ].nb_comp * n + d ];
        }
    }
}

END_METIL_NAMESPACE;


