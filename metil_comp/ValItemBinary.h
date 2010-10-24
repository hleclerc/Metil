#ifndef OPBINARY_H
#define OPBINARY_H

namespace Metil {

///
struct ValItemBinary : public ValItem {
    ValItemBinary( const ValItem *a, const ValItem *b ) {
        ch[ 0 ] = a;
        ch[ 1 ] = b;
        a->add_parent( this );
        b->add_parent( this );
    }
    virtual ~ValItemBinary() {
        ch[ 0 ]->rem_parent( this );
        ch[ 1 ]->rem_parent( this );
    }
    virtual void write_to_stream( Stream &os, int priority_parent ) const {
        get_tiny_repr( os );
        os << '(';
        ch[ 0 ]->write_to_stream( os, 0 );
        os << ',';
        ch[ 1 ]->write_to_stream( os, 0 );
        os << ')';
    }
    virtual void write_tex( Stream &os, int priority_parent ) const {
        get_tex_sym( os );
        os << '(';
        ch[ 0 ]->write_tex( os, 0 );
        os << ',';
        ch[ 1 ]->write_tex( os, 0 );
        os << ')';
    }
    virtual void get_tex_sym( Stream &os ) const = 0;
    virtual int priority() const { return 0; }

    virtual int nb_children() const { return 2; }
    virtual const ValItem *child( int i ) const { return ch[ i ]; }

    virtual void dec_ref_op_mp_rec_children() const {
        ch[ 0 ]->dec_ref_op_mp_rec();
        ch[ 1 ]->dec_ref_op_mp_rec();
    }

    virtual void get_subs() const {
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        ch[ 0 ]->get_subs();
        ch[ 1 ]->get_subs();
        if ( ch[ 0 ]->op_mp == 0 and ch[ 1 ]->op_mp == 0 ) {
            op_mp = 0;
            return;
        }
        op_mp = make_operation( ch[ 0 ]->op_mp ? ch[ 0 ]->op_mp : ch[ 0 ], ch[ 1 ]->op_mp ? ch[ 1 ]->op_mp : ch[ 1 ] );
    }

    virtual const ValItem *make_operation( const ValItem *a, const ValItem *b ) const = 0;

    const ValItem *ch[ 2 ];
};


///
template<class T>
const ValItem *new_binary_op( StructForType<T>, const ValItem *a, const ValItem *b ) {
    const ValItem *ch = ( a->is_a_Number() ? b : a );
    for(int i=0;i<ch->parents.size();++i) {
        const T *p = dynamic_cast<const T *>( ch->parents[ i ] );
        if ( p and p->ch[ 0 ] == a and p->ch[ 1 ] == b )
            return inc_ref( p );
    }
    return new T( a, b );
}

///
template<class T>
const ValItem *new_binary_op_com( StructForType<T> s, const ValItem *a, const ValItem *b ) {
    if ( a > b )
        return new_binary_op( s, b, a );
    return new_binary_op( s, a, b );
}

} // namespace

#include "ValItemPow.h"
#include "ValItemAdd.h"
#include "ValItemSub.h"
#include "ValItemMul.h"
#include "ValItemDiv.h"

#endif // OPBINARY_H
