#include "LazyScheduler.h"

namespace Metil {

LazyScheduler::LazyScheduler() {
}

LazyScheduler &LazyScheduler::operator<<( const LazyObject *obj ) {
    roots << obj;
    return *this;
}

void LazyScheduler::execute() {
    ++LazyObject::current_op_id;

    BasicVec<const LazyObject *> front;
    for(int i=0;i<roots.size();++i)
        roots[ i ]->get_not_done_leaves( front );

    while( front.size() ) {
        const LazyObject *obj = front.back();
        front.pop_back();

        obj->exec_node();

        for(int num_p=0;num_p<obj->parents.size();++num_p) {
            const LazyObject *par = obj->parents[ num_p ];
            if ( par->all_children_are_done() )
                front << par;
        }
    }
}

void schedule_and_execute( const LazyObject *obj ) {
    LazyScheduler ls;
    ls << obj;
    ls.execute();
}


} // namespace Metil
