#ifndef OP_H
#define OP_H

#include "LazyObject.h"
#include "CString.h"
#include "BigRat.h"
#include "Type.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ValItem.cpp
#endif

namespace Metil {

class Stream;
class ValItemAddSeq;
class ValItemMulSeq;
class ValItemMul;
class ValItemNeg;
class ValItemNumberC;
class ValItemNumberI;
class ValItemNumberR;
class ValItemNumberD;

/**
TODO :
    - sqrt( 4 ) -> 2
    - AddSeq, MulSeq, ...
    -

*/
class ValItem : public LazyObject {
public:
    // lazy
    virtual bool done() const;
    virtual void exec_node() const;

    // mathematical properties
    virtual bool get_val( long   &v ) const { return false; } // return true if it is an integer constant that can be stored in a long and copy it in v
    virtual bool get_val( double &v ) const { return false; } // return true if it is an integer constant that can be stored in a long and copy it in v
    virtual bool is_a_Number                () const { return false; }
    virtual bool is_always_an_integer       () const { return false; }
    virtual bool is_always_strictly_positive() const { return false; }
    virtual bool is_always_positive_or_null () const { return false; }
    virtual bool is_always_equal_to_one     () const { return false; }
    virtual bool is_always_equal_to_zero    () const { return false; }
    virtual bool is_always_equal_to_one_half() const { return false; }

    // operations
    virtual void get_subs() const = 0;
    virtual void get_diff() const = 0;
    virtual void dec_ref_op_mp_rec_children() const = 0; // dec_ref( op_mp ) for each child
    virtual void poly_deg_rec() const = 0;
    void dec_ref_op_mp_rec() const; // dec_ref( op_mp ) for this and each child

    // factories
    virtual const ValItem *sin() const;
    virtual const ValItem *cos() const;
    virtual const ValItem *log() const;
    virtual const ValItem *exp() const;
    virtual const ValItem *neg() const;
    virtual const ValItem *inv() const;
    virtual const ValItem *abs() const;

    virtual const ValItem *add( const ValItem *op ) const;
    virtual const ValItem *sub( const ValItem *op ) const;
    virtual const ValItem *mul( const ValItem *op ) const;
    virtual const ValItem *div( const ValItem *op ) const;
    virtual const ValItem *pow( const ValItem *op ) const;

    virtual const ValItem *r_add( const ValItem *op ) const;
    virtual const ValItem *r_sub( const ValItem *op ) const;
    virtual const ValItem *r_mul( const ValItem *op ) const;
    virtual const ValItem *r_div( const ValItem *op ) const;
    virtual const ValItem *r_pow( const ValItem *op ) const;

    virtual const ValItem *r_add( const ValItemNumberC *op ) const;
    virtual const ValItem *r_add( const ValItemNumberI *op ) const;
    virtual const ValItem *r_add( const ValItemNumberR *op ) const;
    virtual const ValItem *r_add( const ValItemNumberD *op ) const;
    virtual const ValItem *r_add( const ValItemMul     *op ) const;

    virtual const ValItem *r_sub( const ValItemNumberC *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberI *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberR *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberD *op ) const;

    virtual const ValItem *r_mul( const ValItemNumberC *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberI *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberR *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberD *op ) const;
    virtual const ValItem *r_mul( const ValItemMul     *op ) const;
    virtual const ValItem *r_mul( const ValItemNeg     *op ) const;

    virtual const ValItem *r_div( const ValItemNumberC *op ) const;
    virtual const ValItem *r_div( const ValItemNumberI *op ) const;
    virtual const ValItem *r_div( const ValItemNumberR *op ) const;
    virtual const ValItem *r_div( const ValItemNumberD *op ) const;

    virtual const ValItem *r_pow( const ValItemNumberC *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberI *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberR *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberD *op ) const;

    virtual const ValItem *as_Number() const; // if number, return this, else, return ValItemNumberC( this ). BEWARE : NO INC_REF OF THIS !!

    // attributes
    mutable const ValItem *op_mp;
};

// --------------------------------------------------------------------------------
//struct Bp : public ValItem {
//    Bp();
//    virtual ~Bp();
//
//    void push_pos_op( const ValItem *op );
//    void push_neg_op( const ValItem *op );
//    void push_pex_op( const Bp *op );
//    void push_nex_op( const Bp *op );
//
//    virtual void push_or_fact_Bp_to_this( const ValItem *op ) = 0;
//
//    template<class TV>
//    void replace_in_lst( TV &vec, int i, const ValItem *new_op ) { /// helper
//        const ValItem *old_ch = vec[ i ];
//        vec.remove_unordered( i );
//        push_or_fact_Bp_to_this( new_op );
//        old_ch->rem_parent( this );
//    }
//
//    void push_or_fact_pos_op( const ValItem *op );
//    void push_or_fact_neg_op( const ValItem *op );
//    void push_or_fact_pex_op( const Bp *op );
//    void push_or_fact_nex_op( const Bp *op );
//
//    virtual void push_number( const ValItemNumber *op ) = 0;
//    virtual void push_or_fact_number( const ValItemNumber *op ) = 0;
//
//    virtual const ValItem *bp_op    ( const ValItem *a, const ValItem *b ) const = 0;
//    virtual const ValItem *bp_sup_op( const ValItem *a, const ValItem *b ) const = 0;
//
//    virtual int nb_children() const;
//
//    virtual const ValItem *child( int i ) const;
//
//    virtual const ValItem *neutral() const = 0;
//
//    void write_to_stream_pn( Stream &os, char p, char n, int priority_parent ) const;
//    void write_tex_pn      ( Stream &os, char p, char n, int priority_parent ) const;
//
//    bool equal_Bp( const Bp *op ) const;
//
//    const ValItem *get_child_with_parents() const;
//    virtual void dec_ref_op_mp_rec_children() const;
//
//    BasicVec<const ValItem *,-1,2> pos_children; /// a
//    BasicVec<const ValItem *,-1,2> neg_children; /// -a       or 1/a
//    BasicVec<const Bp *,-1,2> pex_children; /// a*b*...  or a^b
//    BasicVec<const Bp *,-1,2> nex_children; /// -a*b*... or a^{-b}
//    const ValItemNumber *nb; /// 10
//};
//
//// --------------------------------------------------------------------------------
//struct Add : public Bp {
//    virtual void push_or_fact_number( const ValItemNumber *op );
//    virtual void push_number( const ValItemNumber *op );
//    virtual void push_or_fact_Bp_to_this( const ValItem *op );
//    virtual void get_graphviz_sym( Stream &os ) const;
//    virtual void write_to_stream( Stream &os, int priority_parent ) const;
//    virtual void write_tex( Stream &os, int priority_parent ) const;
//    virtual const ValItem *bp_op    ( const ValItem *a, const ValItem *b ) const;
//    virtual const ValItem *bp_sup_op( const ValItem *a, const ValItem *b ) const;
//    virtual void push_this_to_Add( Add *res ) const;
//    virtual void push_neg_this_to_Add( Add *res ) const;
//    virtual void push_or_fact_this_to_Add( Add *res ) const;
//    virtual void push_or_fact_neg_this_to_Add( Add *res ) const;
//    virtual int priority() const;
//    virtual CString type_node() const;
//    virtual void get_diff() const;
//    virtual void get_subs() const;
//    virtual const ValItem *neutral() const;
//    virtual void poly_deg_rec() const;
//};
//
//// --------------------------------------------------------------------------------
//struct Mul : public Bp {
//    virtual void push_or_fact_number( const ValItemNumber *op );
//    virtual void push_number( const ValItemNumber *op );
//    virtual void push_or_fact_Bp_to_this( const ValItem *op );
//    virtual void get_graphviz_sym( Stream &os ) const;
//    virtual void write_to_stream( Stream &os, int priority_parent ) const;
//    virtual void write_tex( Stream &os, int priority_parent ) const;
//    virtual const ValItem *bp_op    ( const ValItem *a, const ValItem *b ) const;
//    virtual const ValItem *bp_sup_op( const ValItem *a, const ValItem *b ) const;
//    virtual void push_this_to_Add( Add *res ) const;
//    virtual void push_or_fact_this_to_Add( Add *res ) const;
//    virtual void push_this_to_Mul( Mul *res ) const;
//    virtual void push_or_fact_this_to_Mul( Mul *res ) const;
//    virtual void push_or_fact_inv_this_to_Add( Add *res ) const;
//    virtual int priority() const;
//    virtual CString type_node() const;
//    virtual void get_diff() const;
//    virtual void get_subs() const;
//    virtual const ValItem *neutral() const;
//    virtual void poly_deg_rec() const;
//};

} // namespace

#include "ValItemNumber.h"
#include "ValItemSymbol.h"
#include "ValItemAddSeq.h"
#include "ValItemMulSeq.h"
#include "ValItemUnary.h"
#include "ValItemBinary.h"

#endif // OP_H
