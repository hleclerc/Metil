#ifndef OPSUB_H
#define OPSUB_H

namespace Metil {

///
class ValItemSub : public ValItemBinary {
public:
    ValItemSub( const ValItem *a, const ValItem *b ) : ValItemBinary( a, b ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemSub"; }
    virtual void get_tiny_repr( Stream &os ) const { os << '-'; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "-"; }
    virtual int priority() const { return 15; }

    virtual void write_to_stream( Stream &os, int priority_parent ) const {
        bool np = priority_parent > priority();
        if ( np )
            os << '(';
        ch[ 0 ]->write_to_stream( os, priority() );
        os << '-';
        ch[ 1 ]->write_to_stream( os, priority() );
        if ( np )
            os << ')';
    }

    virtual void write_tex( Stream &os, int priority_parent ) const {
        ch[ 0 ]->write_tex( os, priority() );
        os << '-';
        ch[ 1 ]->write_tex( os, priority() );
    }

    void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch[ 0 ]->get_diff();
        ch[ 1 ]->get_diff();
        ASSERT( 0, "TODO" );
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
        reinterpret_cast<int &>( op_mp ) = ( p0 == -2 or p1 == -2 ? -2 : max( p0, p1 ) );
    }

    virtual const ValItem *make_operation( const ValItem *a, const ValItem *b ) const { return a->sub( b ); }

};

} // namespace Metil

#endif // OPSUB_H
