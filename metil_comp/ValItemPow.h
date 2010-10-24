#ifndef OPPOW_H
#define OPPOW_H

namespace Metil {

///  a ^ b
class ValItemPow : public ValItemBinary {
public:
    ValItemPow( const ValItem *a, const ValItem *b ) : ValItemBinary( a, b ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemPow"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "pow"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "pow"; }
    virtual int priority() const { return 30; }

    virtual void write_to_stream( Stream &os, int priority_parent ) const {
        if ( ch[ 1 ]->is_always_equal_to_one_half() ) {
            os << "sqrt(";
            ch[ 0 ]->write_tex( os, 0 );
            os << ')';
        } else
            ValItemBinary::write_to_stream( os, priority_parent );
    }

    virtual void write_tex( Stream &os, int priority_parent ) const {
        if ( ch[ 1 ]->is_always_equal_to_one_half() ) {
            os << "\\sqrt{";
            ch[ 0 ]->write_tex( os, 0 );
            os << '}';
        } else {
            os << '{';
            ch[ 0 ]->write_tex( os, priority() );
            os << '}';
            os << "^{";
            ch[ 1 ]->write_tex( os, priority() );
            os << '}';
        }
    }

    const ValItem *diff_ch_0() const { // a' * b * a ^ ( b - 1 )
        const ValItem *bm1 = ch[ 1 ]->add( number_m1 );      // b - 1
        const ValItem *abm = ch[ 0 ]->pow( bm1 );            // a ^ ( b - 1 )
        const ValItem *apb = ch[ 0 ]->op_mp->mul( ch[ 1 ] ); // a' * b
        const ValItem *m_0 = apb->mul( abm );         // a' * b * a ^ ( b - 1 )
        dec_ref( apb );
        dec_ref( abm );
        dec_ref( bm1 );
        return m_0;
    }

    const ValItem *diff_ch_1() const { // b' * log( a ) * a ^ b
        const ValItem *lga = ch[ 0 ]->log();             // log( a )
        const ValItem *bpl = ch[ 1 ]->op_mp->mul( lga ); // b' * log( a )
        const ValItem *m_1 = bpl->mul( this );           // b' * log( a ) * a ^ b
        dec_ref( bpl );
        dec_ref( lga );
        return m_1;
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
                const ValItem *m_0 = diff_ch_0();
                const ValItem *m_1 = diff_ch_1();
                op_mp = m_0->add( m_1 );
                dec_ref( m_1 );
                dec_ref( m_0 );
            } else
                op_mp = diff_ch_0();
        } else {
            if ( ch[ 1 ]->op_mp )
                op_mp = diff_ch_1();
            else
                op_mp = 0;
        }
    }

    virtual void poly_deg_rec() const {
        if ( op_id == current_op_id ) return; op_id = ValItem::current_op_id;
        ch[ 0 ]->poly_deg_rec();
        int deg_a = reinterpret_cast<const int &>( ch[ 0 ]->op_mp );
        if ( deg_a == -2 )
            reinterpret_cast<int &>( op_mp ) = -2;
        else {
            long val;
            if ( ch[ 1 ]->get_val( val ) and val > 0 ) {
                reinterpret_cast<int &>( op_mp ) = deg_a * val;
            } else
                reinterpret_cast<int &>( op_mp ) = -2;
        }
    }

    virtual const ValItem *make_operation( const ValItem *a, const ValItem *b ) const { return a->pow( b ); }
};

} // namespace Metil

#endif // OPPOW_H
