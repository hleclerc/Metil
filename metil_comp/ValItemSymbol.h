#ifndef OPSYMBOL_H
#define OPSYMBOL_H

namespace Metil {

class ValItemSymbol : public ValItem {
public:
    ValItemSymbol( const CString &cpp, const CString &tex ) : cpp( cpp ), tex( tex ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemSymbol"; }
    virtual void get_tiny_repr( Stream &os ) const { os << cpp; }
    virtual void write_to_stream( Stream &os, int priority_parent ) const { os << cpp; }
    virtual void write_tex      ( Stream &os, int priority_parent ) const { os << tex; }
    virtual int priority() const { return 0; }

    virtual int nb_children() const { return 0; }
    virtual const ValItem *child( int i ) const { return 0; }

    virtual void get_diff() const {
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        op_mp = 0;
    }

    virtual void get_subs() const {
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        op_mp = 0;
    }

    virtual void dec_ref_op_mp_rec_children() const {}

    virtual void poly_deg_rec() const {
        if ( op_id == current_op_id ) return; op_id = ValItem::current_op_id;
        reinterpret_cast<int &>( op_mp ) = 0;
    }

    CString cpp;
    CString tex;
};

inline const ValItem *new_symbol( const CString &cpp, const CString &tex ) {
    return new ValItemSymbol( cpp, tex.empty() ? cpp : tex );
}

} // namespace

#endif // OPSYMBOL_H
