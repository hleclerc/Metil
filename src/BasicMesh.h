#ifndef BASICMESH_H
#define BASICMESH_H

#include "BasicVec.h"
#include "ElemType.h"

BEG_METIL_NAMESPACE;

class DisplayItem;

/**
*/
class BasicMesh {
public:
    typedef float T;
    typedef int I;

    struct ElemGroup {
        ElemGroup( const ElemType *elem_type ) : elem_type( elem_type ), elem_id( elem_type->elem_id() ) {
        }

        template<class TB,class TP>
        void apply_bs( TB &res, TP ) const {
            res.set_type( "ElemGroup" );
            APPLY_WN( res, connec );
            APPLY_WN( res, elem_id );
        }

        BasicVec<BasicVec<I> > connec;
        const ElemType *elem_type;
        I elem_id;
    };

    struct NodeToElemItem {
        template<class TB,class TP>
        void apply_bs( TB &res, TP ) const {
            res.set_type( "NodeToElemItem" );
            APPLY_WN( res, num_group );
            APPLY_WN( res, num_elem );
        }
        I num_group;
        I num_elem;
    };

    template<class TB,class TP>
    void apply_bs( TB &res, TP ) const {
        res.set_type( "BasicMesh_Compacted" );
        APPLY_WN( res, pos_nodes );
        APPLY_WN( res, elem_groups );
        APPLY_WN( res, node_to_elem );
    }

    void add_node( T x, T y );
    void add_node( T x, T y, T z );
    void add_elem( const ElemType *elem_type, I x, I y, I z );
    ST nb_elements() const;
    ElemGroup *find_group( const ElemType *elem_type );
    void make_rect( const ElemType *elem_type, BasicVec<T> X0, BasicVec<T> X1, BasicVec<I> Xd );

    BasicVec<ElemGroup> elem_groups;
    BasicVec<BasicVec<T> > pos_nodes;
    BasicVec<BasicVec<NodeToElemItem> > node_to_elem;
};

END_METIL_NAMESPACE;

#endif // BASICMESH_H
