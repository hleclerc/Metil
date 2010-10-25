#ifndef OPDIV_H
#define OPDIV_H

namespace Metil {

///
class ValItemDiv : public ValItemBinary {
public:
    ValItemDiv( const ValItem *a, const ValItem *b ) : ValItemBinary( a, b ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemDiv"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "/"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\div"; }
    virtual int priority() const { return 25; }

    virtual void write_tex( Stream &os, int priority_parent ) const {
        os << "\\frac{";
        ch[ 0 ]->write_tex( os, priority() );
        os << '}';
        os << "^{";
        ch[ 1 ]->write_tex( os, priority() );
        os << '}';
    }

    virtual void write_to_stream( Stream &os, int priority_parent ) const {
        bool np = priority_parent > priority();
        if ( np )
            os << '(';
        ch[ 0 ]->write_to_stream( os, priority() );
        os << '/';
        ch[ 1 ]->write_to_stream( os, priority() );
        if ( np )
            os << ')';
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
        reinterpret_cast<int &>( op_mp ) = ( p1 != 0 ? -2 : p0 );
    }

    virtual const ValItem *make_operation( const ValItem *a, const ValItem *b ) const { return a->div( b ); }

};

} // namespace Metil

#endif // OPDIV_H
