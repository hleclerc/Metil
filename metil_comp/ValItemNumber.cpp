#include "ValItem.h"

namespace Metil {

const ValItem *ValItemNumber::r_mul( const ValItem *op ) const {
    return new_binary_op( StructForType<ValItemMul>(), this, op );
}

const ValItem *ValItemNumber::r_mul( const ValItemMul *op ) const {
    if ( op->ch[ 0 ]->is_a_Number() ) { // ( 2 * a ) * 4
        const ValItem *num = op->ch[ 0 ]->mul( this );
        const ValItem *res = num->mul( op->ch[ 1 ] );
        dec_ref( num );
        return res;
    }
    return new_binary_op( StructForType<ValItemMul>(), this, op );
}

const ValItem *ValItemNumber::r_mul( const ValItemNeg *op ) const { // 2 * ( -a )
    const ValItem *n = neg();
    const ValItem *r = n->mul( op->ch );
    dec_ref( n );
    return r;
}

const ValItem *ValItemNumberI::sin() const {
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    const ValItem *op_sin = new ValItemSin( this );
    const ValItem *op_res = new ValItemNumberC( op_sin );
    dec_ref( op_sin );
    return op_res;
}

const ValItemNumber *new_number( const BigInt &val ) { return new ValItemNumberI( val ); }
const ValItemNumber *new_number( const Int32  &val ) { return new ValItemNumberI( val ); }
const ValItemNumber *new_number( const Int64  &val ) { return new ValItemNumberI( val ); }

const ValItemNumber *new_number( const BigInt &den, const BigInt &num ) { return new ValItemNumberR( den, num ); }
const ValItemNumber *new_number( const BigRat &val ) { return new ValItemNumberR( val ); }

const ValItemNumber *new_number( Float32 val ) { return new ValItemNumberD( val ); }
const ValItemNumber *new_number( Float64 val ) { return new ValItemNumberD( val ); }

ValItemNumberI  inst_number_2 ( 2  );
ValItemNumberI  inst_number_1 ( 1  );
ValItemNumberI  inst_number_0 ( 0  );
ValItemNumberI  inst_number_m1( -1 );
ValItemNumberR  inst_number_05( 1, 2 );
ValItemNumberPI inst_number_pi;

const ValItem *number_2  = &inst_number_2 ;
const ValItem *number_1  = &inst_number_1 ;
const ValItem *number_0  = &inst_number_0 ;
const ValItem *number_m1 = &inst_number_m1;
const ValItem *number_05 = &inst_number_05;
const ValItem *number_pi = &inst_number_pi;

const ValItem *ValItemNumberI::add( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    if ( val.is_strictly_negative() ) { // a + (-2) -> a - 2
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return op->r_add( this );
}

const ValItem *ValItemNumberI::sub( const ValItem *op ) const {
    if ( Metil::is_always_equal_to_zero( val ) )
        return op->neg();
    return op->r_sub( this );
}

const ValItem *ValItemNumberI::mul( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_minus_one() )
        return op->neg();
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    return op->r_mul( this );
}

const ValItem *ValItemNumberI::div( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return op->inv();
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    if ( val.is_equal_to_minus_one() ) {
        AutoDecRef<ValItem> i( op->inv() );
        return i->neg();
    }
    return op->r_div( this );
}

const ValItem *ValItemNumberI::pow( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( this );
    return op->r_pow( this );
}

const ValItem *ValItemNumberI::r_add( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    if ( val.is_strictly_negative() ) {
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return ValItemNumber::r_add( op );
}

const ValItem *ValItemNumberI::r_sub( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    return ValItemNumber::r_sub( op );
}

const ValItem *ValItemNumberI::r_mul( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    return ValItemNumber::r_mul( op );
}

const ValItem *ValItemNumberI::r_div( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_minus_one() )
        return op->neg();
    return ValItemNumber::r_div( op );
}

// ------------------------------------------------------

const ValItem *ValItemNumberR::add( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    if ( val.is_strictly_negative() ) { // a + (-2) -> a - 2
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return op->r_add( this );
}

const ValItem *ValItemNumberR::sub( const ValItem *op ) const {
    return op->r_sub( this );
}

const ValItem *ValItemNumberR::mul( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_minus_one() )
        return op->neg();
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    return op->r_mul( this );
}

const ValItem *ValItemNumberR::div( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return op->inv();
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    return op->r_div( this );
}

const ValItem *ValItemNumberR::pow( const ValItem *op ) const {
    return op->r_pow( this );
}

const ValItem *ValItemNumberR::r_add( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    if ( val.is_strictly_negative() ) {
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return ValItemNumber::r_add( op );
}

const ValItem *ValItemNumberR::r_sub( const ValItem *op ) const {
    if ( val.is_equal_to_zero() )
        return inc_ref( op );
    return ValItemNumber::r_sub( op );
}

const ValItem *ValItemNumberR::r_mul( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_zero() )
        return inc_ref( this );
    return ValItemNumber::r_mul( op );
}

const ValItem *ValItemNumberR::r_div( const ValItem *op ) const {
    if ( val.is_equal_to_one() )
        return inc_ref( op );
    if ( val.is_equal_to_minus_one() )
        return op->neg();
    return ValItemNumber::r_div( op );
}

// ------------------------------------------------------

const ValItem *ValItemNumberD::add( const ValItem *op ) const {
    if ( val == 0 )
        return inc_ref( op );
    if ( val < 0 ) { // a + (-2) -> a - 2
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return op->r_add( this );
}

const ValItem *ValItemNumberD::sub( const ValItem *op ) const {
    return op->r_sub( this );
}

const ValItem *ValItemNumberD::mul( const ValItem *op ) const {
    if ( val == 1 )
        return inc_ref( op );
    if ( val == -1 )
        return op->neg();
    if ( val == 0 )
        return inc_ref( this );
    return op->r_mul( this );
}

const ValItem *ValItemNumberD::div( const ValItem *op ) const {
    if ( val == 1 )
        return op->inv();
    if ( val == 0 )
        return inc_ref( this );
    return op->r_div( this );
}

const ValItem *ValItemNumberD::pow( const ValItem *op ) const {
    return op->r_pow( this );
}

const ValItem *ValItemNumberD::r_add( const ValItem *op ) const {
    if ( val == 0 )
        return inc_ref( op );
    if ( val < 0 ) {
        AutoDecRef<ValItem> n( neg() );
        return op->sub( n.op );
    }
    return ValItemNumber::r_add( op );
}

const ValItem *ValItemNumberD::r_sub( const ValItem *op ) const {
    if ( val == 0 )
        return inc_ref( op );
    return ValItemNumber::r_sub( op );
}

const ValItem *ValItemNumberD::r_mul( const ValItem *op ) const {
    if ( val == 1 )
        return inc_ref( op );
    if ( val == 0 )
        return inc_ref( this );
    return ValItemNumber::r_mul( op );
}

const ValItem *ValItemNumberD::r_div( const ValItem *op ) const {
    if ( val == 1 )
        return inc_ref( op );
    if ( val == -1 )
        return op->neg();
    return ValItemNumber::r_div( op );
}


// ------------------------------------------------------

const ValItem *ValItemNumberI::r_add( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberI::r_sub( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberI::r_mul( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberI::r_div( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberI::r_pow( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }

const ValItem *ValItemNumberR::r_add( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberR::r_sub( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberR::r_mul( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberR::r_div( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberR::r_pow( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }

const ValItem *ValItemNumberD::r_add( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberD::r_sub( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberD::r_mul( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberD::r_div( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }
const ValItem *ValItemNumberD::r_pow( const ValItemNumberC *op ) const { return op->ch->add( this )->as_Number(); }

const ValItem *ValItemNumberI::r_add( const ValItemNumberI *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberI::r_add( const ValItemNumberR *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberI::r_add( const ValItemNumberD *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberR::r_add( const ValItemNumberI *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberR::r_add( const ValItemNumberR *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberR::r_add( const ValItemNumberD *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberD::r_add( const ValItemNumberI *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberD::r_add( const ValItemNumberR *op ) const { return new_number( op->val + val ); }
const ValItem *ValItemNumberD::r_add( const ValItemNumberD *op ) const { return new_number( op->val + val ); }

const ValItem *ValItemNumberI::r_sub( const ValItemNumberI *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberI::r_sub( const ValItemNumberR *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberI::r_sub( const ValItemNumberD *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberR::r_sub( const ValItemNumberI *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberR::r_sub( const ValItemNumberR *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberR::r_sub( const ValItemNumberD *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberD::r_sub( const ValItemNumberI *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberD::r_sub( const ValItemNumberR *op ) const { return new_number( op->val - val ); }
const ValItem *ValItemNumberD::r_sub( const ValItemNumberD *op ) const { return new_number( op->val - val ); }

const ValItem *ValItemNumberI::r_mul( const ValItemNumberI *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberI::r_mul( const ValItemNumberR *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberI::r_mul( const ValItemNumberD *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberR::r_mul( const ValItemNumberI *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberR::r_mul( const ValItemNumberR *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberR::r_mul( const ValItemNumberD *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberD::r_mul( const ValItemNumberI *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberD::r_mul( const ValItemNumberR *op ) const { return new_number( op->val * val ); }
const ValItem *ValItemNumberD::r_mul( const ValItemNumberD *op ) const { return new_number( op->val * val ); }

const ValItem *ValItemNumberI::r_div( const ValItemNumberI *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberI::r_div( const ValItemNumberR *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberI::r_div( const ValItemNumberD *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberR::r_div( const ValItemNumberI *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberR::r_div( const ValItemNumberR *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberR::r_div( const ValItemNumberD *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberD::r_div( const ValItemNumberI *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberD::r_div( const ValItemNumberR *op ) const { return new_number( op->val / val ); }
const ValItem *ValItemNumberD::r_div( const ValItemNumberD *op ) const { return new_number( op->val / val ); }

const ValItem *ValItemNumberI::r_pow( const ValItemNumberI *op ) const { // int ^ int
    if ( val.is_positive_or_null() ) // op->val ^ val
        return new_number( pow_by_positive_exponent( op->val, val ) );
    return new_number( 1, pow_by_positive_exponent( op->val, Metil::abs( val ) ) );
}

const ValItem *ValItemNumberI::r_pow( const ValItemNumberR *op ) const { // rat ^ int
    if ( val.is_positive_or_null() ) { // op->val ^ val
        BigRat res( 1 );
        for(Int64 e = val; e > 0; --e)
            res *= op->val;
        return new_number( res );
    }
    BigRat res( 1 );
    for(Int64 e = val; e > 0; --e)
        res /= op->val;
    return new_number( res );
}

const ValItem *ValItemNumberI::r_pow( const ValItemNumberD *op ) const {
    return new_number( ::pow( op->val, val ) );
} // flt ^ int

const ValItem *ValItemNumberR::r_pow( const ValItemNumberI *op ) const { // int ^ rat
    AutoDecRef<ValItem> p( new ValItemPow( op, this ) );
    return new ValItemNumberC( p.op );
}

const ValItem *ValItemNumberR::r_pow( const ValItemNumberR *op ) const { return new_number( ::pow( op->val, val ) ); }
const ValItem *ValItemNumberR::r_pow( const ValItemNumberD *op ) const { return new_number( ::pow( op->val, val ) ); }
const ValItem *ValItemNumberD::r_pow( const ValItemNumberI *op ) const { return new_number( ::pow( op->val, val ) ); }
const ValItem *ValItemNumberD::r_pow( const ValItemNumberR *op ) const { return new_number( ::pow( op->val, val ) ); }
const ValItem *ValItemNumberD::r_pow( const ValItemNumberD *op ) const { return new_number( ::pow( op->val, val ) ); }


}
