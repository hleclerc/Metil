#ifndef METIL_LAZYOBJECT_H
#define METIL_LAZYOBJECT_H

#include "BasicVec.h"
#include "IncAndDecRef.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LazyObject.cpp
#endif

namespace Metil {

/**
*/
class LazyObject {
public:
    LazyObject();
    virtual ~LazyObject();

    // children, parents
    virtual void add_parent( const LazyObject *parent ) const;
    virtual void rem_parent( const LazyObject *parent ) const;
    virtual int nb_children() const = 0;
    virtual const LazyObject *child( int i ) const = 0;

    // graph execution
    virtual void exec_node() const = 0;
    virtual bool done() const = 0;

    bool all_children_are_done() const;
    void get_not_done_leaves( BasicVec<const LazyObject *> &leaves ) const;

    // display
    virtual void write_to_stream( Stream &os, int priority_parent = 0 ) const; // -> write_cpp by default

    virtual void write_dot( Stream &os, bool want_parents = false ) const; // graphviz
    virtual void write_tex( Stream &os, int priority_parent = 0 ) const;
    virtual void write_cpp( Stream &os, int priority_parent = 0 ) const;

    virtual void get_type_name( Stream &os ) const = 0; // full class name
    virtual void get_tiny_repr( Stream &os ) const = 0; // text that appears in graphviz for example (small type representation like '+', ...)
    virtual int priority() const;

    // helpers
    static void add_todo( const LazyObject *obj ); // inc_ref on obj must be done before

    // attributes
    mutable BasicVec<const LazyObject *,-1,4> parents;
    mutable int cpt_use;
    mutable int op_id;
    static int current_op_id;
};

void exec_todo_lazy_objects();

}

#endif // METIL_LAZYOBJECT_H
