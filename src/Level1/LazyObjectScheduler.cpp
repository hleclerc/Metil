#include "LazyObjectScheduler.h"
#include "BasicSplittedVec.h"
#include "String.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;


struct SchedItem {
    MO obj;
    int nb_children;
    int nb_parents;
    SchedItem **children;
    SchedItem **parents;
};

struct SchedItemList {
    SchedItem *new_item( MO obj, int nb_children ) {
        SchedItem *res = items.push_back();
        res->obj = obj;
        res->nb_children = nb_children;
        res->nb_parents = 0;
        res->children = sub_item_lists.get_room( nb_children );
        res->parents = 0;
    }
    BasicSplittedVec<SchedItem,64> items;
    BasicSplittedVec<SchedItem *,64> sub_item_lists;
};



void LazyObjectScheduler::add( MO *o ) {
    roots.push_back_unique( o );
}

static SchedItem *get_leaves_rec( SchedItemList &sched_item_list, MO obj, BasicVec<SchedItem *> &leaves ) {
    if ( CM_1( cur_op_id, obj ) )
        return reinterpret_cast< SchedItem *>( CM_1( get_op_mp, obj ).data );

    ST nb_ch = CM_1( nb_children, obj );
    SchedItem *res = sched_item_list.new_item( obj, nb_ch );
    if ( nb_ch )
        for( ST i = 0; i < nb_ch; ++i )
            res->children[ i ] = get_leaves_rec( sched_item_list, CM_1( get_child, obj, i ), leaves );
    else
        leaves << res;

    CM_1( set_op_mp, obj, res, 0 );
    return res;
}

//static bool all_child_done( MO obj ) {
//    for( ST i = 0, nb_ch = CM_1( nb_children, obj ); i < nb_ch; ++i )
//        if ( not CM_1( cur_op_id, obj ) )
//            return false;
//    return true;
//}

void LazyObjectScheduler::exec() {
    SchedItemList sched_item_list;

    ++current_MO_op_id;
    BasicVec<SchedItem *> leaves;
    for( ST i = 0; i < roots.size(); ++i )
        get_leaves_rec( sched_item_list, *roots[ i ], leaves );

    // ++current_op_id;
    while ( leaves.size() ) {
        SchedItem *l = leaves.pop_back();

        DOUT( l->obj.type->name );
        // CM_1( exec_node );
        //for( ST i = 0; i < leaves.size(); ++i )
        //    DOUT( leaves[ i ].type->name );
        //        for( OwcpChild *p = CM_1( get_parent, l ); p; p = p->next )
        //            if ( all_child_done( p->self ) )
        //                leaves << p->self;
        // DOUT( leaves.size() );
    }
}

END_METIL_LEVEL1_NAMESPACE;
