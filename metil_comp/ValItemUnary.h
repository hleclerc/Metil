#ifndef OPUNARY_H
#define OPUNARY_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ValItemUnary.cpp
#endif

namespace Metil {

/**
*/
struct ValItemUnary : public ValItem {
    ValItemUnary( const ValItem *ch ) : ch( ch ) {
        ch->add_parent( this );
    }
    virtual ~ValItemUnary() {
        ch->rem_parent( this );
    }
    virtual void write_to_stream( Stream &os, int priority_parent ) const { get_tiny_repr( os ); os << '('; ch->write_to_stream( os, priority() ); os << ')'; }
    virtual void write_tex      ( Stream &os, int priority_parent ) const { get_tex_sym  ( os ); os << '('; ch->write_tex      ( os, priority() ); os << ')'; }
    virtual void get_tex_sym( Stream &os ) const = 0;
    virtual int priority() const { return 0; }

    virtual int nb_children() const { return 1; }
    virtual const ValItem *child( int i ) const { return ch; }
    virtual void dec_ref_op_mp_rec_children() const { ch->dec_ref_op_mp_rec(); }

    virtual void poly_deg_rec() const { // not polynomial by default
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        ch->poly_deg_rec();
        reinterpret_cast<int &>( op_mp ) = reinterpret_cast<int &>( ch->op_mp ) == 0 ? 0 : -2;
    }

    virtual void get_subs() const {
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        ch->get_subs();
        if ( not ch->op_mp ) {
            op_mp = 0;
            return;
        }
        op_mp = make_operation( ch->op_mp );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const = 0;

    const ValItem *ch;
};

///
template<class T>
const ValItem *new_unary_op( StructForType<T>, const ValItem *ch ) {
    for(int i=0;i<ch->parents.size();++i) {
        const T *p = dynamic_cast<const T *>( ch->parents[ i ] );
        if ( p and p->ch == ch )
            return inc_ref( p );
    }
    return new T( ch );
}

///
struct ValItemSin : public ValItemUnary {
    ValItemSin( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemSin"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "sin"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\sin"; }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        ch->get_diff();
        if ( not ch->op_mp ) {
            op_mp = 0;
            return;
        }
        //
        const ValItem *c = ch->cos();
        op_mp = ch->op_mp->mul( c );
        dec_ref( c );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->sin(); }
};

///
struct ValItemCos : public ValItemUnary {
    ValItemCos( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemCos"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "cos"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\cos"; }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        ch->get_diff();
        if ( not ch->op_mp ) {
            op_mp = 0;
            return;
        }
        //
        const ValItem *s = ch->sin();
        const ValItem *n = s->neg();
        op_mp = ch->op_mp->mul( n );
        dec_ref( n );
        dec_ref( s );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->cos(); }
};

///
struct ValItemLog : public ValItemUnary {
    ValItemLog( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemLog"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "log"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\log"; }

    virtual const ValItem *exp() const { return inc_ref( ch ); }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch->get_diff();
        if ( not ch->op_mp )
            op_mp = 0;
        else
            ASSERT( 0, "TODO" );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->log(); }
};

///
struct ValItemExp : public ValItemUnary {
    ValItemExp( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemExp"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "exp"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\exp"; }

    virtual const ValItem *log() const { return inc_ref( ch ); }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch->get_diff();
        ASSERT( 0, "TODO" );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->exp(); }
};

///
struct ValItemNeg : public ValItemUnary {
    ValItemNeg( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemNeg"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "neg"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\neg"; }

    virtual void poly_deg_rec() const { // by default
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        ch->poly_deg_rec();
        reinterpret_cast<int &>( op_mp ) = reinterpret_cast<const int &>( ch->op_mp ); // same degree
    }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch->get_diff();
        if ( not ch->op_mp )
            op_mp = 0;
        else
            ASSERT( 0, "TODO" );
    }

    virtual const ValItem *add( const ValItem *op ) const { return op->sub( ch ); }
    virtual const ValItem *mul( const ValItem *op ) const { return op->r_mul( this ); }

    virtual const ValItem *r_add( const ValItem *op ) const { return op->sub( ch ); }
    virtual const ValItem *r_add( const ValItemMul *op ) const;

    virtual const ValItem *r_mul( const ValItem *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberC *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberI *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberR *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberD *op ) const;

    virtual const ValItem *inv() const;
    virtual const ValItem *neg() const;

    virtual const ValItem *r_div( const ValItem *op ) const { return op->div( ch ); }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->neg(); }
};

///
struct ValItemInv : public ValItemUnary {
    ValItemInv( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemInv"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "inv"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\inv"; }

    virtual void poly_deg_rec() const { // by default
        if ( op_id == current_op_id )
            return;
        op_id = ValItem::current_op_id;
        ch->poly_deg_rec();
        reinterpret_cast<int &>( op_mp ) = reinterpret_cast<const int &>( ch->op_mp ) > 0 ? -2 : 0;
    }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch->get_diff();
        if ( not ch->op_mp )
            op_mp = 0;
        else
            ASSERT( 0, "TODO" );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->inv(); }
};

///
struct ValItemAbs : public ValItemUnary {
    ValItemAbs( const ValItem *ch ) : ValItemUnary( ch ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemAbs"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "abs"; }
    virtual void get_tex_sym  ( Stream &os ) const { os << "\\abs"; } /// TODO

    virtual const ValItem *abs() const { return inc_ref( ch ); }

    virtual void get_diff() const {
        if ( op_id == current_op_id ) // already done ?
            return;
        op_id = ValItem::current_op_id;
        //
        ch->get_diff();
        ASSERT( 0, "TODO" );
    }

    virtual const ValItem *make_operation( const ValItem *a ) const { return a->abs(); }
};

}

#endif // OPUNARY_H
