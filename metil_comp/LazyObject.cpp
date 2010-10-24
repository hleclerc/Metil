#include "LazyObject.h"
#include "LazyScheduler.h"

namespace Metil {

// static objects
int LazyObject::current_op_id = 0;
BasicVec<const LazyObject *> todo_lazy_objects;


LazyObject::LazyObject() : cpt_use( 1 ), op_id( 0 ) {
}

LazyObject::~LazyObject() {
}

void LazyObject::add_parent( const LazyObject *p ) const {
    parents << p;
}

void LazyObject::rem_parent( const LazyObject *p ) const {
    parents.remove_first_unordered( p );
    if ( cpt_use + parents.size() <= 0 )
        delete this;
}

bool LazyObject::all_children_are_done() const {
    for(int i=0;i<nb_children();++i)
        if ( not child( i )->done() )
            return false;
    return true;
}

void get_leaves_rec( const LazyObject *obj, BasicVec<const LazyObject *> &leaves ) {
    if ( obj->op_id == LazyObject::current_op_id )
        return;
    obj->op_id = LazyObject::current_op_id;
    //
    if ( obj->all_children_are_done() )
        leaves << obj;
    else {
        for(int i=0;i<obj->nb_children();++i)
            if ( not obj->child( i )->done() )
                get_leaves_rec( obj->child( i ), leaves );
    }
}

void LazyObject::get_not_done_leaves( BasicVec<const LazyObject *> &leaves ) const {
    if ( done() )
        return;
    //
    ++current_op_id;
    get_leaves_rec( this, leaves );
}



void LazyObject::write_to_stream( Stream &os, int priority_parent ) const {
    write_cpp( os, priority_parent );
}

void LazyObject::write_dot( Stream &os, bool want_parents ) const {
    if ( op_id == current_op_id ) // already done ?
        return;
    op_id = LazyObject::current_op_id;

    //
    os << "    node" << this << " [label=\"";
    get_tiny_repr( os );
    os << "\"];\n";
    for(int i=0;i<nb_children();++i)
        os << "    node" << this << " -> node" << child( i ) << ";\n";
    if ( want_parents )
        for(int i=0;i<parents.size();++i)
            if ( parents[ i ]->op_id == current_op_id )
                os << "    node" << this << " -> node" << parents[ i ] << " [color=red];\n";
    for(int i=0;i<nb_children();++i)
        child( i )->write_dot( os, want_parents );
}

void LazyObject::write_tex( Stream &os, int priority_parent ) const {
    get_type_name( os );
}

void LazyObject::write_cpp( Stream &os, int priority_parent ) const {
    get_type_name( os );
}

int LazyObject::priority() const {
    return -1;
}

void LazyObject::add_todo( const LazyObject *obj ) {
    todo_lazy_objects << obj;
}

void exec_todo_lazy_objects() {
    LazyScheduler ls;
    for(int i=0;i<todo_lazy_objects.size();++i)
        ls << todo_lazy_objects[ i ];
    ls.execute();

    for(int i=0;i<todo_lazy_objects.size();++i)
        dec_ref( todo_lazy_objects[ i ] );
    todo_lazy_objects.resize( 0 );
}

}
