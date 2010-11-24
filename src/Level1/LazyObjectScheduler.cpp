#include "LazyObjectScheduler.h"
#include "SchedItemList.h"
#include "String.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

void LazyObjectScheduler::add( MO *o ) {
    roots.push_back_unique( o );
}

static SchedItem *get_leaves_rec( SchedItemList &sched_item_list, MO obj, BasicVec<SchedItem *,-1,8> &leaves ) {
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

struct AllocateParents {
    void operator()( SchedItem &item ) {
        item.parents = sched_item_list.sub_item_lists.get_room( item.nb_parents );
        item.nb_parents = 0;
    }
    SchedItemList &sched_item_list;
};

void LazyObjectScheduler::exec() {
    SchedItemList sched_item_list;

    // make items and get leaves
    ++current_MO_op_id;
    BasicVec<SchedItem *,-1,8> leaves;
    BasicVec<SchedItem *,-1,8> s_root;
    for( ST i = 0; i < roots.size(); ++i )
        s_root << get_leaves_rec( sched_item_list, *roots[ i ], leaves );

    // update nb parents, allocate parent lists
    ++SchedItem::current_op_id;
    for( ST i = 0; i < s_root.size(); ++i )
        s_root[ i ]->update_nb_parents_rec();
    AllocateParents allocate_parents = { sched_item_list };
    sched_item_list.items.apply( allocate_parents );

    // update parents
    ++SchedItem::current_op_id;
    for( ST i = 0; i < s_root.size(); ++i )
        s_root[ i ]->update_parents_rec();

    // go
    ++SchedItem::current_op_id;
    while ( leaves.size() ) {
        SchedItem *l = leaves.pop_back();
        l->op_id = SchedItem::current_op_id;

        DOUT( l->obj.type->name );
        // MachineId *mid = ;
        if ( l->mid == 0 or l->mid->type() == MachineId::Cpu )
            CM_1( exec_node_cpu, l->obj );
        else
            CM_1( exec_node_gpu, l->obj );

        // add _ready to go_ parent items
        for( int p = 0; p < l->nb_parents; ++p )
            if ( l->parents[ p ]->all_children_have_current_op_id() )
                leaves << l->parents[ p ];
    }
}

END_METIL_LEVEL1_NAMESPACE;
