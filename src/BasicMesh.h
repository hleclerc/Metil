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

    template<class TB,class TP>
    void apply_bs( TB &res, TP ) const {
        res.set_type( "BasicMesh_Compacted" );
        APPLY_WN( res, pos_nodes );
        APPLY_WN( res, elem_groups );
    }

    void add_node( T x, T y, T z );
    void add_elem( const ElemType *elem_type, T x, T y, T z );
    ElemGroup *find_group( const ElemType *elem_type );

    BasicVec<BasicVec<T> > pos_nodes;
    BasicVec<ElemGroup> elem_groups;
};

END_METIL_NAMESPACE;

#endif // BASICMESH_H
