#ifndef SCHEDITEMLIST_H
#define SCHEDITEMLIST_H

#include "BasicSplittedVec.h"
#include "SchedItem.h"
#include "String.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct SchedItemList {
    SchedItem *new_item( MO obj, int nb_children );
    void write_dot( String &os, bool want_parents = false );
    void display_dot( bool want_parents = false, String base_filename = "compilations/tmp" );

    BasicSplittedVec<SchedItem,64> items;
    BasicSplittedVec<SchedItem *,64> sub_item_lists;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // SCHEDITEMLIST_H
