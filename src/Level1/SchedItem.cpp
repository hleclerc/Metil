#include "SchedItem.h"
#include "Type.h"

BEG_METIL_LEVEL1_NAMESPACE;

SchedItem::SchedItem( MO obj ) : obj( obj ), op_id( 0 ) {
    mid = CM_1( machine_id, obj );
}

SI64 SchedItem::current_op_id = 0;

void SchedItem::update_nb_parents_rec() {
    if ( op_id == current_op_id ) return;
    op_id = current_op_id;

    for( int i = 0; i < nb_children; ++i ) {
        ++children[ i ]->nb_parents;
        children[ i ]->update_nb_parents_rec();
    }
}

void SchedItem::update_parents_rec() {
    if ( op_id == current_op_id ) return;
    op_id = current_op_id;

    for( int i = 0; i < nb_children; ++i ) {
        children[ i ]->parents[ children[ i ]->nb_parents++ ] = this;
        children[ i ]->update_parents_rec();
    }
}

bool SchedItem::all_children_have_current_op_id() const {
    for( int i = 0; i < nb_children; ++i )
        if ( children[ i ]->op_id != current_op_id )
            return false;
    return true;
}

END_METIL_LEVEL1_NAMESPACE;
