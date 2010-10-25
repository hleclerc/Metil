#include "ValItem.h"
#include "Stream.h"
#include "Operation.h"
#include "Type.h"
#include <limits>

namespace Metil {
 
bool ValItem::done() const {
    return false;
}

void ValItem::exec_node() const {
    ASSERT( 0, "cannot exec a symbolic function" );
}

void ValItem::dec_ref_op_mp_rec() const {
    if ( op_id == current_op_id ) // already done ?
        return;
    op_id = ValItem::current_op_id;
    //
    dec_ref_op_mp_rec_children();
    if ( op_mp )
        dec_ref( op_mp );
}


const ValItem *ValItem::add( const ValItem *op ) const { return op->r_add( this ); }
const ValItem *ValItem::sub( const ValItem *op ) const { return op->r_sub( this ); }
const ValItem *ValItem::mul( const ValItem *op ) const { return op->r_mul( this ); }
const ValItem *ValItem::div( const ValItem *op ) const { return op->r_div( this ); }
const ValItem *ValItem::pow( const ValItem *op ) const { return op->r_pow( this ); }

const ValItem *ValItem::r_add( const ValItem *op ) const {
    if(  this == op )
        return number_2->mul( this );
    return new_binary_op( StructForType<ValItemAdd>(), op, this );
}
const ValItem *ValItem::r_sub( const ValItem *op ) const {
    if( this == op )
        return inc_ref( number_0 );
    return new_binary_op( StructForType<ValItemSub>(), op, this );
}
const ValItem *ValItem::r_mul( const ValItem        *op ) const { return new_binary_op_com( StructForType<ValItemMul>(), op, this ); }
const ValItem *ValItem::r_div( const ValItem        *op ) const { return new_binary_op    ( StructForType<ValItemDiv>(), op, this ); }
const ValItem *ValItem::r_pow( const ValItem        *op ) const { return new_binary_op    ( StructForType<ValItemPow>(), op, this ); }

const ValItem *ValItem::r_add( const ValItemNumberC *op ) const { return new_binary_op    ( StructForType<ValItemAdd>(), op, this ); }
const ValItem *ValItem::r_add( const ValItemNumberI *op ) const { return new_binary_op    ( StructForType<ValItemAdd>(), op, this ); }
const ValItem *ValItem::r_add( const ValItemNumberR *op ) const { return new_binary_op    ( StructForType<ValItemAdd>(), op, this ); }
const ValItem *ValItem::r_add( const ValItemNumberD *op ) const { return new_binary_op    ( StructForType<ValItemAdd>(), op, this ); }
const ValItem *ValItem::r_add( const ValItemMul     *op ) const { return new_binary_op_com( StructForType<ValItemAdd>(), op, this ); }

const ValItem *ValItem::r_sub( const ValItemNumberC *op ) const { return new_binary_op    ( StructForType<ValItemSub>(), op, this ); }
const ValItem *ValItem::r_sub( const ValItemNumberI *op ) const { return new_binary_op    ( StructForType<ValItemSub>(), op, this ); }
const ValItem *ValItem::r_sub( const ValItemNumberR *op ) const { return new_binary_op    ( StructForType<ValItemSub>(), op, this ); }
const ValItem *ValItem::r_sub( const ValItemNumberD *op ) const { return new_binary_op    ( StructForType<ValItemSub>(), op, this ); }

const ValItem *ValItem::r_mul( const ValItemNumberC *op ) const { return new_binary_op    ( StructForType<ValItemMul>(), op, this ); }
const ValItem *ValItem::r_mul( const ValItemNumberI *op ) const { return new_binary_op    ( StructForType<ValItemMul>(), op, this ); }
const ValItem *ValItem::r_mul( const ValItemNumberR *op ) const { return new_binary_op    ( StructForType<ValItemMul>(), op, this ); }
const ValItem *ValItem::r_mul( const ValItemNumberD *op ) const { return new_binary_op    ( StructForType<ValItemMul>(), op, this ); }

const ValItem *ValItem::r_mul( const ValItemMul     *op ) const {
    if ( this == op->ch[ 0 ] ) { // ( a * b ) * a -> a² * b
        const ValItem *a_2 = this->pow( number_2 );
        const ValItem *res = a_2->mul( op->ch[ 1 ] );
        dec_ref( a_2 );
        return res;
    }
    if ( this == op->ch[ 1 ] ) { // ( b * a ) * a -> a² * b
        const ValItem *a_2 = this->pow( number_2 );
        const ValItem *res = a_2->mul( op->ch[ 0 ] );
        dec_ref( a_2 );
        return res;
    }
    return new_binary_op_com( StructForType<ValItemMul>(), op, this );
}

const ValItem *ValItem::r_mul( const ValItemNeg     *op ) const { /// simplification of (-a)*b
    const ValItem *prod = this->mul( op->ch );
    const ValItem *ret  = prod->neg();
    dec_ref( prod );
    return ret; /// -(a*b)
}

const ValItem *ValItem::r_div( const ValItemNumberC *op ) const { return new_binary_op( StructForType<ValItemDiv>(), op, this ); }
const ValItem *ValItem::r_div( const ValItemNumberI *op ) const { return new_binary_op( StructForType<ValItemDiv>(), op, this ); }
const ValItem *ValItem::r_div( const ValItemNumberR *op ) const { return new_binary_op( StructForType<ValItemDiv>(), op, this ); }
const ValItem *ValItem::r_div( const ValItemNumberD *op ) const { return new_binary_op( StructForType<ValItemDiv>(), op, this ); }

const ValItem *ValItem::r_pow( const ValItemNumberC *op ) const { return new_binary_op( StructForType<ValItemPow>(), op, this ); }
const ValItem *ValItem::r_pow( const ValItemNumberI *op ) const { return new_binary_op( StructForType<ValItemPow>(), op, this ); }
const ValItem *ValItem::r_pow( const ValItemNumberR *op ) const { return new_binary_op( StructForType<ValItemPow>(), op, this ); }
const ValItem *ValItem::r_pow( const ValItemNumberD *op ) const { return new_binary_op( StructForType<ValItemPow>(), op, this ); }

const ValItem *ValItem::sin() const { return new_unary_op( StructForType<ValItemSin>(), this ); }
const ValItem *ValItem::cos() const { return new_unary_op( StructForType<ValItemCos>(), this ); }
const ValItem *ValItem::log() const { return new_unary_op( StructForType<ValItemLog>(), this ); }
const ValItem *ValItem::exp() const { return new_unary_op( StructForType<ValItemExp>(), this ); }
const ValItem *ValItem::neg() const { return new_unary_op( StructForType<ValItemNeg>(), this ); }
const ValItem *ValItem::inv() const { return new_unary_op( StructForType<ValItemInv>(), this ); }
const ValItem *ValItem::abs() const { return new_unary_op( StructForType<ValItemAbs>(), this ); }

const ValItem *ValItem::as_Number() const {
    const ValItem *res = new ValItemNumberC( this );
    dec_ref( this );
    return res;
}

//template<class T>
//const ValItem *bp_op_or_similar( const T *res ) {
//    // similar somewhere ?
//    const ValItem *ch = res->get_child_with_parents();
//    if ( ch ) {
//        for(int i=0;i<ch->parents.size();++i) {
//            const T *p = dynamic_cast<const T *>( ch->parents[ i ] );
//            if ( p and p != res and p->equal_Bp( res ) ) {
//                delete res;
//                return inc_ref( p );
//            }
//        }
//    }
//
//    // a + 0, ...
//    if ( not res->nb ) {
//        if ( res->pos_children.size() == 1 and res->neg_children.size() == 0 and res->pex_children.size() == 0 and res->nex_children.size() == 0 ) { // +a
//            const ValItem *p = res->pos_children[ 0 ]; ++p->cpt_use; delete res; return p;
//        } else if ( res->pos_children.size() == 0 and res->neg_children.size() == 0 and res->pex_children.size() == 1 and res->nex_children.size() == 0 ) { // +a*b
//            const ValItem *p = res->pex_children[ 0 ]; ++p->cpt_use; delete res; return p;
//        } else if ( res->pos_children.size() == 0 and res->neg_children.size() == 1 and res->pex_children.size() == 0 and res->nex_children.size() == 0 ) { // -a
//            const ValItem *p = res->neg_children[ 0 ]->neg(); delete res; return p;
//        } else if ( res->pos_children.size() == 0 and res->neg_children.size() == 0 and res->pex_children.size() == 0 and res->nex_children.size() == 1 ) { // -a*b
//            const ValItem *p = res->nex_children[ 0 ]->neg(); delete res; return p;
//        } else if ( res->pos_children.size() == 0 and res->neg_children.size() == 0 and res->pex_children.size() == 0 and res->nex_children.size() == 0 ) { // 0
//            return inc_ref( res->neutral() );
//        }
//    } else {
//        if ( res->pos_children.size() == 0 and res->neg_children.size() == 0 and res->pex_children.size() == 0 and res->nex_children.size() == 0 ) { // 10
//            const ValItem *p = res->nb; ++p->cpt_use; delete res; return p;
//        }
//    }
//
//    //
//    return res;
//}// --------------------------------------------------------------------------------
//Bp::Bp() : nb( 0 ) {}
//
//Bp::~Bp() {
//    for(int i=0;i<pos_children.size();++i) pos_children[ i ]->rem_parent( this );
//    for(int i=0;i<neg_children.size();++i) neg_children[ i ]->rem_parent( this );
//    for(int i=0;i<pex_children.size();++i) pex_children[ i ]->rem_parent( this );
//    for(int i=0;i<nex_children.size();++i) nex_children[ i ]->rem_parent( this );
//    if ( nb ) dec_ref( nb );
//}
//
//
//void Bp::push_pos_op( const ValItem *op ) { pos_children << op; op->add_parent( this ); }
//void Bp::push_neg_op( const ValItem *op ) { neg_children << op; op->add_parent( this ); }
//void Bp::push_pex_op( const Bp *op ) { pex_children << op; op->add_parent( this ); }
//void Bp::push_nex_op( const Bp *op ) { nex_children << op; op->add_parent( this ); }
//
//void Bp::push_or_fact_pos_op( const ValItem *op ) {
//    for(int i=0;i<pos_children.size();++i) {
//        if ( pos_children[ i ] == op ) {
//            replace_in_lst( pos_children, i, bp_sup_op( op, number_2 ) );
//            return;
//        }
//    }
//    // else
//    pos_children << op;
//    op->add_parent( this );
//}
//
//void Bp::push_or_fact_neg_op( const ValItem *op ) {
//    for(int i=0;i<neg_children.size();++i) {
//        if ( neg_children[ i ] == op ) {
//            replace_in_lst( neg_children, i, bp_sup_op( op, number_2 ) );
//            return;
//        }
//    }
//    // else
//    neg_children << op;
//    op->add_parent( this );
//}
//
//void Bp::push_or_fact_pex_op( const Bp *op ) {
//    for(int i=0;i<pex_children.size();++i) {
//        if ( pex_children[ i ] == op ) {
//            replace_in_lst( pex_children, i, bp_sup_op( op, number_2 ) );
//            return;
//        }
//    }
//    // else
//    pex_children << op;
//    op->add_parent( this );
//}
//
//void Bp::push_or_fact_nex_op( const Bp *op ) {
//    nex_children << op;
//    op->add_parent( this );
//}
//
//int Bp::nb_children() const {
//    return pos_children.size() + neg_children.size() + pex_children.size() + nex_children.size() + bool( nb );
//}
//
//const ValItem *Bp::child( int i ) const {
//    if ( i < pos_children.size() ) return pos_children[ i ]; i -= pos_children.size();
//    if ( i < neg_children.size() ) return neg_children[ i ]; i -= neg_children.size();
//    if ( i < pex_children.size() ) return pex_children[ i ]; i -= pex_children.size();
//    if ( i < nex_children.size() ) return nex_children[ i ]; i -= nex_children.size();
//    return nb;
//}
//
//void Bp::write_to_stream_pn( Stream &os, char p, char n, int priority_parent ) const { /// helper for Add and Mul
//    if ( nb )
//        nb->write_to_stream( os, priority() );
//    // a
//    if ( pos_children.size() )
//        pos_children[ 0 ]->write_to_stream( nb ? os << p : os, priority() );
//    for(int i=1;i<pos_children.size();++i)
//        pos_children[ i ]->write_to_stream( os << p, priority() );
//    // a*b
//    if ( pex_children.size() )
//        pex_children[ 0 ]->write_to_stream( nb or pos_children.size() ? os << p : os, priority() );
//    for(int i=1;i<pex_children.size();++i)
//        pex_children[ i ]->write_to_stream( os << p, priority() );
//    // -a
//    for(int i=0;i<neg_children.size();++i)
//        neg_children[ i ]->write_to_stream( os << n, priority() );
//    // -a*b
//    for(int i=0;i<nex_children.size();++i)
//        nex_children[ i ]->write_to_stream( os << n, priority() );
//
//}
//
//void Bp::write_tex_pn( Stream &os, char p, char n, int priority_parent ) const { /// helper for Add and Mul
//    bool np = priority_parent > priority();
//    if ( np )
//        os << "(";
//
//    if ( nb )
//        nb->write_tex( os, priority() );
//    // a
//    if ( pos_children.size() )
//        pos_children[ 0 ]->write_tex( nb ? os << p : os, priority() );
//    for(int i=1;i<pos_children.size();++i)
//        pos_children[ i ]->write_tex( os << p, priority() );
//    // -a
//    for(int i=0;i<neg_children.size();++i)
//        neg_children[ i ]->write_tex( os << n, priority() );
//    // a*b
//    if ( pex_children.size() )
//        pex_children[ 0 ]->write_tex( nb or pos_children.size() or neg_children.size() ? os << p : os, priority() );
//    for(int i=1;i<pex_children.size();++i)
//        pex_children[ i ]->write_tex( os << p, priority() );
//    // -a*b
//    for(int i=0;i<nex_children.size();++i)
//        nex_children[ i ]->write_tex( os << n, priority() );
//
//    if ( np )
//        os << ")";
//}
//
//bool Bp::equal_Bp( const Bp *op ) const {
//    return nb == op->nb and pos_children == op->pos_children and neg_children == op->neg_children and pex_children == op->pex_children and nex_children == op->nex_children;
//}
//
//const ValItem *Bp::get_child_with_parents() const {
//    if ( pos_children.size() ) return pos_children[ 0 ];
//    if ( neg_children.size() ) return neg_children[ 0 ];
//    if ( pex_children.size() ) return pex_children[ 0 ];
//    if ( nex_children.size() ) return nex_children[ 0 ];
//    return 0;
//}
//void Bp::dec_ref_op_mp_rec_children() const {
//    for(int i=0;i<pos_children.size();++i) pos_children[ i ]->dec_ref_op_mp_rec();
//    for(int i=0;i<neg_children.size();++i) neg_children[ i ]->dec_ref_op_mp_rec();
//    for(int i=0;i<pex_children.size();++i) pex_children[ i ]->dec_ref_op_mp_rec();
//    for(int i=0;i<nex_children.size();++i) nex_children[ i ]->dec_ref_op_mp_rec();
//}


// --------------------------------------------------------------------------------
//CString Add::type_node() const { return "Add"; }
//
//void Add::push_or_fact_number( const NumberAncestor *op ) {
//    if ( nb ) {
//        const NumberAncestor *old_nb = nb;
//        nb = nb->add_number( op );
//        if ( nb->is_always_equal_to_zero() ) { dec_ref( nb ); nb = 0; }
//        dec_ref( old_nb );
//    } else if ( not op->is_always_equal_to_zero() )
//        nb = inc_ref( op );
//}
//void Add::push_number( const NumberAncestor *op ) {
//    if ( not op->is_always_equal_to_zero() )
//        nb = inc_ref( op );
//}
//
//void Add::push_or_fact_Bp_to_this( const ValItem *op ) { op->push_or_fact_this_to_Add( this ); }
//
//void Add::get_graphviz_sym( Stream &os ) const {
//    if ( nb ) os << '+';
//    for(int i=0;i<pos_children.size();++i) os << '+';
//    for(int i=0;i<neg_children.size();++i) os << '-';
//    for(int i=0;i<pex_children.size();++i) os << '+';
//    for(int i=0;i<nex_children.size();++i) os << '-';
//}
//
//void Add::write_to_stream( Stream &os, int priority_parent ) const {
//    write_to_stream_pn( os, '+', '-', priority_parent );
//}
//
//void Add::write_tex( Stream &os, int priority_parent ) const {
//    write_tex_pn( os, '+', '-', priority_parent );
//}
//
//const ValItem *Add::bp_op    ( const ValItem *a, const ValItem *b ) const { return a->add( b ); }
//const ValItem *Add::bp_sup_op( const ValItem *a, const ValItem *b ) const { return a->mul( b ); }
//
//void Add::push_this_to_Add( Add *res ) const {
//    if ( nb )                              res->push_number( nb );
//    for(int i=0;i<pos_children.size();++i) res->push_pos_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_neg_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_pex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_nex_op( nex_children[ i ] );
//}
//
//void Add::push_neg_this_to_Add( Add *res ) const {
//    if ( nb )                              res->push_number( static_cast<const NumberAncestor *>( nb->neg() ) );
//    for(int i=0;i<pos_children.size();++i) res->push_neg_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_pos_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_nex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_pex_op( nex_children[ i ] );
//}
//
//void Add::push_or_fact_this_to_Add( Add *res ) const {
//    if ( nb )                              res->push_or_fact_number( nb );
//    for(int i=0;i<pos_children.size();++i) res->push_or_fact_pos_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_or_fact_neg_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_or_fact_pex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_or_fact_nex_op( nex_children[ i ] );
//}
//
//void Add::push_or_fact_neg_this_to_Add( Add *res ) const {
//    if ( nb )                              res->push_or_fact_number( static_cast<const NumberAncestor *>( nb->neg() ) );
//    for(int i=0;i<pos_children.size();++i) res->push_or_fact_neg_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_or_fact_pos_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_or_fact_nex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_or_fact_pex_op( nex_children[ i ] );
//}
//
//int Add::priority() const { return 10; }
//
//const ValItem *Add::neutral() const {
//    return number_0;
//}
//
//void Add::get_diff() const {
//    if ( op_id == current_op_id ) // already done ?
//        return;
//    op_id = ValItem::current_op_id;
//    op_mp = 0;
//    //
//    Add *res = new Add;
//    for(int i=0;i<pos_children.size();++i) { pos_children[ i ]->get_diff(); if ( pos_children[ i ]->op_mp ) pos_children[ i ]->op_mp->push_or_fact_this_to_Add    ( res ); }
//    for(int i=0;i<neg_children.size();++i) { neg_children[ i ]->get_diff(); if ( neg_children[ i ]->op_mp ) neg_children[ i ]->op_mp->push_or_fact_neg_this_to_Add( res ); }
//    for(int i=0;i<pex_children.size();++i) { pex_children[ i ]->get_diff(); if ( pex_children[ i ]->op_mp ) pex_children[ i ]->op_mp->push_or_fact_this_to_Add    ( res ); }
//    for(int i=0;i<nex_children.size();++i) { nex_children[ i ]->get_diff(); if ( nex_children[ i ]->op_mp ) nex_children[ i ]->op_mp->push_or_fact_neg_this_to_Add( res ); }
//    op_mp = bp_op_or_similar( res );
//}
//
//void Add::get_subs() const {
//    if ( op_id == current_op_id ) // already done ?
//        return;
//    op_id = ValItem::current_op_id;
//    //
//    bool changed = false;
//    for(int i=0;i<pos_children.size();++i) { pos_children[ i ]->get_subs(); changed |= bool( pos_children[ i ]->op_mp ); }
//    for(int i=0;i<neg_children.size();++i) { neg_children[ i ]->get_subs(); changed |= bool( neg_children[ i ]->op_mp ); }
//    for(int i=0;i<pex_children.size();++i) { pex_children[ i ]->get_subs(); changed |= bool( pex_children[ i ]->op_mp ); }
//    for(int i=0;i<nex_children.size();++i) { nex_children[ i ]->get_subs(); changed |= bool( nex_children[ i ]->op_mp ); }
//    if ( not changed ) {
//        op_mp = 0;
//        return;
//    }
//    //
//    Add *res = new Add;
//    if ( nb ) nb->push_this_to_Add( res );
//    for(int i=0;i<pos_children.size();++i) { ( pos_children[ i ]->op_mp ? pos_children[ i ]->op_mp : pos_children[ i ] )->push_or_fact_this_to_Add    ( res ); }
//    for(int i=0;i<neg_children.size();++i) { ( neg_children[ i ]->op_mp ? neg_children[ i ]->op_mp : neg_children[ i ] )->push_or_fact_neg_this_to_Add( res ); }
//    for(int i=0;i<pex_children.size();++i) { ( pex_children[ i ]->op_mp ? pex_children[ i ]->op_mp : pex_children[ i ] )->push_or_fact_this_to_Add    ( res ); }
//    for(int i=0;i<nex_children.size();++i) { ( nex_children[ i ]->op_mp ? nex_children[ i ]->op_mp : nex_children[ i ] )->push_or_fact_neg_this_to_Add( res ); }
//    op_mp = bp_op_or_similar( res );
//}
//
//void Add::poly_deg_rec() const {
//    if ( op_id == current_op_id ) return; op_id = ValItem::current_op_id;
//    int &res = reinterpret_cast<int &>( op_mp );
//    res = nb ? 0 : -1;
//    for(int i=0;i<pos_children.size();++i) { pos_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( pos_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res = max( res, v ); }
//    for(int i=0;i<neg_children.size();++i) { neg_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( neg_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res = max( res, v ); }
//    for(int i=0;i<pex_children.size();++i) { pex_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( pex_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res = max( res, v ); }
//    for(int i=0;i<nex_children.size();++i) { nex_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( nex_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res = max( res, v ); }
//}

// --------------------------------------------------------------------------------
//CString Mul::type_node() const { return "Mul"; }
//
//void Mul::push_or_fact_number( const NumberAncestor *op ) {
//    if ( nb ) {
//        const NumberAncestor *old_nb = nb;
//        nb = nb->mul_number( op );
//        if ( nb->is_always_equal_to_one() ) { dec_ref( nb ); nb = 0; }
//        dec_ref( old_nb );
//    } else if ( not op->is_always_equal_to_one() )
//        nb = inc_ref( op );
//}
//
//void Mul::push_number( const NumberAncestor *op ) {
//    if ( not op->is_always_equal_to_one() )
//        nb = inc_ref( op );
//}
//
//void Mul::push_or_fact_Bp_to_this( const ValItem *op ) { op->push_or_fact_this_to_Mul( this ); }
//
//void Mul::get_graphviz_sym( Stream &os ) const {
//    if ( nb ) os << '*';
//    for(int i=0;i<pos_children.size();++i) os << '*';
//    for(int i=0;i<neg_children.size();++i) os << '/';
//    for(int i=0;i<pex_children.size();++i) os << '*';
//    for(int i=0;i<nex_children.size();++i) os << '/';
//}
//
//
//void Mul::write_to_stream( Stream &os, int priority_parent ) const {
//    write_to_stream_pn( os, '*', '/', priority_parent );
//}
//
//void Mul::write_tex( Stream &os, int priority_parent ) const {
//    write_tex_pn( os, ' ', '/', priority_parent );
//}
//
//const ValItem *Mul::bp_op    ( const ValItem *a, const ValItem *b ) const { return a->mul( b ); }
//const ValItem *Mul::bp_sup_op( const ValItem *a, const ValItem *b ) const { return a->pow( b ); }
//
//void Mul::push_this_to_Add( Add *res ) const {
//    res->push_pex_op( this );
//}
//
//void Mul::push_or_fact_this_to_Add( Add *res ) const {
//    res->push_or_fact_pex_op( this );
//}
//
//void Mul::push_this_to_Mul( Mul *res ) const {
//    if ( nb )                              res->push_number( nb );
//    for(int i=0;i<pos_children.size();++i) res->push_pos_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_neg_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_pex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_nex_op( nex_children[ i ] );
//}
//
//void Mul::push_or_fact_this_to_Mul( Mul *res ) const {
//    if ( nb )                              res->push_or_fact_number( nb );
//    for(int i=0;i<pos_children.size();++i) res->push_or_fact_pos_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_or_fact_neg_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_or_fact_pex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_or_fact_nex_op( nex_children[ i ] );
//}
//
//void Mul::push_or_fact_inv_this_to_Add( Add *res ) const {
//    if ( nb )                              res->push_or_fact_number( static_cast<const NumberAncestor *>( nb->neg() ) );
//    for(int i=0;i<pos_children.size();++i) res->push_or_fact_neg_op( pos_children[ i ] );
//    for(int i=0;i<neg_children.size();++i) res->push_or_fact_pos_op( neg_children[ i ] );
//    for(int i=0;i<pex_children.size();++i) res->push_or_fact_nex_op( pex_children[ i ] );
//    for(int i=0;i<nex_children.size();++i) res->push_or_fact_pex_op( nex_children[ i ] );
//}
//
//int Mul::priority() const { return 20; }
//
//const ValItem *Mul::neutral() const {
//    return number_1;
//}
//
//void Mul::get_diff() const {
//    if ( op_id == current_op_id ) // already done ?
//        return;
//    op_id = ValItem::current_op_id;
//    op_mp = 0;
//    //
//    Add *res = new Add;
//
//    //
//    for(int i=0;i<pos_children.size();++i) {
//        pos_children[ i ]->get_diff();
//        if ( pos_children[ i ]->op_mp ) {
//            Mul *par = new Mul;
//            if ( nb )                                            par->push_number( nb                );
//            for(int j=0;j<pos_children.size();++j) if ( j != i ) par->push_pos_op( pos_children[ j ] );
//            for(int j=0;j<neg_children.size();++j)               par->push_neg_op( neg_children[ j ] );
//            for(int j=0;j<pex_children.size();++j)               par->push_pex_op( pex_children[ j ] );
//            for(int j=0;j<nex_children.size();++j)               par->push_nex_op( nex_children[ j ] );
//            pos_children[ i ]->op_mp->push_or_fact_this_to_Mul( par );
//
//            const ValItem *re = bp_op_or_similar( par );
//            re->push_or_fact_this_to_Add( res );
//            dec_ref( re );
//        }
//    }
//    for(int i=0;i<neg_children.size();++i) {
//        neg_children[ i ]->get_diff();
//        if ( neg_children[ i ]->op_mp ) { // a / b
//            Mul *par = new Mul;
//            if ( nb )                                            par->push_number( nb                );
//            for(int j=0;j<pos_children.size();++j)               par->push_pos_op( pos_children[ j ] );
//            for(int j=0;j<neg_children.size();++j) if ( i != j ) par->push_neg_op( neg_children[ j ] );
//            for(int j=0;j<pex_children.size();++j)               par->push_pex_op( pex_children[ j ] );
//            for(int j=0;j<nex_children.size();++j)               par->push_nex_op( nex_children[ j ] );
//            const ValItem *bp2 = neg_children[ i ]->pow( number_2 );
//            bp2->push_or_fact_inv_this_to_Mul( par ); // / b²
//            dec_ref( bp2 );
//            neg_children[ i ]->op_mp->push_or_fact_this_to_Mul( par ); // * b'
//
//            const ValItem *re = bp_op_or_similar( par );
//            re->push_or_fact_neg_this_to_Add( res );
//            dec_ref( re );
//        }
//    }
//    for(int i=0;i<pex_children.size();++i) {
//        pex_children[ i ]->get_diff();
//        if ( pex_children[ i ]->op_mp ) {
//            Mul *par = new Mul;
//            if ( nb )                                            par->push_number( nb                );
//            for(int j=0;j<pos_children.size();++j)               par->push_pos_op( pos_children[ j ] );
//            for(int j=0;j<neg_children.size();++j)               par->push_neg_op( neg_children[ j ] );
//            for(int j=0;j<pex_children.size();++j) if ( j != i ) par->push_pex_op( pex_children[ j ] );
//            for(int j=0;j<nex_children.size();++j)               par->push_nex_op( nex_children[ j ] );
//            pex_children[ i ]->op_mp->push_or_fact_this_to_Mul( par );
//
//            const ValItem *re = bp_op_or_similar( par );
//            re->push_or_fact_this_to_Add( res );
//            dec_ref( re );
//        }
//
//    }
//    for(int i=0;i<nex_children.size();++i) {
//        nex_children[ i ]->get_diff();
//        if ( nex_children[ i ]->op_mp ) { // a / b
//            Mul *par = new Mul;
//            if ( nb )                                            par->push_number( nb                );
//            for(int j=0;j<pos_children.size();++j)               par->push_pos_op( pos_children[ j ] );
//            for(int j=0;j<neg_children.size();++j)               par->push_neg_op( neg_children[ j ] );
//            for(int j=0;j<pex_children.size();++j)               par->push_pex_op( pex_children[ j ] );
//            for(int j=0;j<nex_children.size();++j) if ( i != j ) par->push_nex_op( nex_children[ j ] );
//            const ValItem *bp2 = nex_children[ i ]->pow( number_2 );
//            bp2->push_or_fact_inv_this_to_Mul( par ); // / b²
//            dec_ref( bp2 );
//            nex_children[ i ]->op_mp->push_or_fact_this_to_Mul( par ); // * b'
//            ASSERT( 0, "WRONG : TODO !!" );
//
//            const ValItem *re = bp_op_or_similar( par );
//            re->push_or_fact_neg_this_to_Add( res ); // - b' * a / b²
//            dec_ref( re );
//        }
//    }
//
//    op_mp = bp_op_or_similar( res );
//}
//
//void Mul::get_subs() const {
//    if ( op_id == current_op_id ) // already done ?
//        return;
//    op_id = ValItem::current_op_id;
//    //
//    bool changed = false;
//    for(int i=0;i<pos_children.size();++i) { pos_children[ i ]->get_subs(); changed |= bool( pos_children[ i ]->op_mp ); }
//    for(int i=0;i<neg_children.size();++i) { neg_children[ i ]->get_subs(); changed |= bool( neg_children[ i ]->op_mp ); }
//    for(int i=0;i<pex_children.size();++i) { pex_children[ i ]->get_subs(); changed |= bool( pex_children[ i ]->op_mp ); }
//    for(int i=0;i<nex_children.size();++i) { nex_children[ i ]->get_subs(); changed |= bool( nex_children[ i ]->op_mp ); }
//    if ( not changed ) {
//        op_mp = 0;
//        return;
//    }
//    //
//    Mul *res = new Mul;
//    if ( nb ) nb->push_this_to_Mul( res );
//    for(int i=0;i<pos_children.size();++i) { ( pos_children[ i ]->op_mp ? pos_children[ i ]->op_mp : pos_children[ i ] )->push_or_fact_this_to_Mul    ( res ); }
//    for(int i=0;i<neg_children.size();++i) { ( neg_children[ i ]->op_mp ? neg_children[ i ]->op_mp : neg_children[ i ] )->push_or_fact_inv_this_to_Mul( res ); }
//    for(int i=0;i<pex_children.size();++i) { ( pex_children[ i ]->op_mp ? pex_children[ i ]->op_mp : pex_children[ i ] )->push_or_fact_this_to_Mul    ( res ); }
//    for(int i=0;i<nex_children.size();++i) { ( nex_children[ i ]->op_mp ? nex_children[ i ]->op_mp : nex_children[ i ] )->push_or_fact_inv_this_to_Mul( res ); }
//    op_mp = bp_op_or_similar( res );
//}
//
//
//void Mul::poly_deg_rec() const {
//    if ( op_id == current_op_id ) return; op_id = ValItem::current_op_id;
//    int &res = reinterpret_cast<int &>( op_mp );
//    res = 0;
//    for(int i=0;i<neg_children.size();++i) { neg_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( neg_children[ i ]->op_mp ); if ( v !=  0 ) { res = -2; return; }; }
//    for(int i=0;i<nex_children.size();++i) { nex_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( nex_children[ i ]->op_mp ); if ( v !=  0 ) { res = -2; return; }; }
//    for(int i=0;i<pos_children.size();++i) { pos_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( pos_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res += v; }
//    for(int i=0;i<pex_children.size();++i) { pex_children[ i ]->poly_deg_rec(); int v = reinterpret_cast<const int &>( pex_children[ i ]->op_mp ); if ( v == -2 ) { res = -2; return; }; res += v; }
//}


}


