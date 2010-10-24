#ifndef OPMUL_H
#define OPMUL_H

#include "IncAndDecRef.h"

namespace Metil {

///
class ValItemMul : public ValItemBinary {
public:
    ValItemMul( const ValItem *a, const ValItem *b ) : ValItemBinary( a, b ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemMul"; }
    virtual void get_tiny_repr( Stream &os ) const { os << '*'; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\times"; }
    virtual int priority() const { return 20; }

    virtual void write_to_stream( Stream &os, int priority_parent ) const {
        bool np = priority_parent > priority();
        if ( np )
            os << '(';
        ch[ 0 ]->write_to_stream( os, priority() );
        os << '*';
        ch[ 1 ]->write_to_stream( os, priority() );
        if ( np )
            os << ')';
    }

    virtual void write_tex( Stream &os, int priority_parent ) const {
        ch[ 0 ]->write_tex( os, priority() );
        os << '*';
        ch[ 1 ]->write_tex( os, priority() );
    }

    void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch[ 0 ]->get_diff();
        ch[ 1 ]->get_diff();
        if ( ch[ 0 ]->op_mp ) {
            if ( ch[ 1 ]->op_mp ) {
                AutoDecRef<ValItem> m_0 = ch[ 0 ]->op_mp->add( ch[ 1 ] );
                AutoDecRef<ValItem> m_1 = ch[ 0 ]->add( ch[ 1 ]->op_mp );
                op_mp = m_0.op->add( m_1.op );
            } else
                op_mp = ch[ 0 ]->op_mp->mul( ch[ 1 ] );
        } else {
            if ( ch[ 1 ]->op_mp )
                op_mp = ch[ 1 ]->op_mp->mul( ch[ 0 ] );
            else
                op_mp = 0;
        }
    }

    virtual void poly_deg_rec() const {
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        //
        ch[ 0 ]->poly_deg_rec();
        ch[ 1 ]->poly_deg_rec();
        int p0 = reinterpret_cast<const int &>( ch[ 0 ]->op_mp );
        int p1 = reinterpret_cast<const int &>( ch[ 1 ]->op_mp );
        reinterpret_cast<int &>( op_mp ) = ( p0 == -2 or p1 == -2 ? -2 : p0 + p1 );
    }

    virtual const ValItem *add( const ValItem *op ) const { return op->r_add( this ); }
    virtual const ValItem *mul( const ValItem *op ) const { return op->r_mul( this ); }

    virtual const ValItem *r_add( const ValItemMul *op ) const {
        if ( ch[ 1 ] == op->ch[ 1 ] and ch[ 0 ]->is_a_Number() and op->ch[ 0 ]->is_a_Number() ) { // 2 * a + 3 * a
            // before
            /*const ValItem *a = ch[ 0 ]->add( op->ch[ 0 ] );
            const ValItem *r = a->mul( ch[ 1 ] );
            dec_ref( a );
            return r;*/
            // after
            AutoDecRef<ValItem> a = ch[ 0 ]->add( op->ch[ 0 ] );
            return a->mul( ch[ 1 ] );
        }
        return ValItemBinary::r_add( op );
    }

    virtual const ValItem *make_operation( const ValItem *a, const ValItem *b ) const { return a->mul( b ); }

};

} // namespace Metil

#endif // OPMUL_H
