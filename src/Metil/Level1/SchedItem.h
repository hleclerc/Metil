#ifndef SCHEDITEM_H
#define SCHEDITEM_H

#include "../MO.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct SchedItem {
    SchedItem( MO obj );
    void update_nb_parents_rec();
    void update_parents_rec();
    bool all_children_have_current_op_id() const;

    MO obj;
    int nb_children;
    int nb_parents;
    SchedItem **children;
    SchedItem **parents;
    const MachineId *mid;

    SI64 op_id;
    SchedItem *res; /// res of op_id operation
    static SI64 current_op_id;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // SCHEDITEM_H
