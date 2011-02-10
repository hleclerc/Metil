#include "SchedItemList.h"
#include "../MetilSystem.h"

BEG_METIL_LEVEL1_NAMESPACE;

SchedItem *SchedItemList::new_item( MO obj, int nb_children ) {
    SchedItem *res = items.push_back( obj );
    res->nb_children = nb_children;
    res->nb_parents = 0;
    res->children = sub_item_lists.get_room( nb_children );
    res->parents = 0;
    return res;
}

void SchedItemList::write_dot( String &os, bool want_parents ) {
    for( ST i = 0; i < items.size(); ++i ) {
        os << "node" << &items[ i ] << " [label=\"" << items[ i ].obj.type->name << "\"];\n";
        for( int c = 0; c < items[ i ].nb_children; ++c )
            os << "node" << &items[ i ] << " -> node" << items[ i ].children[ c ] << ";\n";
        if ( want_parents )
            for( int p = 0; p < items[ i ].nb_parents; ++p )
                os << "node" << items[ i ].parents[ p ] << " -> node" << &items[ i ] << " [color=\"red\"];\n";
    }
}

void SchedItemList::display_dot( bool want_parents, String base_filename ) {
    String dot_file = base_filename + ".dot";
    File fout( dot_file, "w" );
    fout << "digraph my_graph {\n";
    fout << "    ordering = \"out\"\n";
    write_dot( fout, want_parents );
    fout << "};\n";
    fout.flush();

    exec_cmd( "dot -Tpdf " + base_filename + ".dot > " + base_filename + ".pdf && okular " + base_filename + ".pdf" );
}

END_METIL_LEVEL1_NAMESPACE;
