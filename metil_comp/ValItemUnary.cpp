#include "ValItem.h"

namespace Metil {

const ValItem *ValItemNeg::inv() const {
    AutoDecRef<ValItem> i( ch->inv() );
    return i.op->neg();
}

const ValItem *ValItemNeg::neg() const {
    return inc_ref( ch );
}

const ValItem *ValItemNeg::r_add( const ValItemMul *op ) const {
    if ( ch == op->ch[1] /*and op->ch[ 0 ]->is_a_Number()*/  ) { /// 2 * a + (-a)
        const ValItem *a = op->ch[ 0 ]->sub( number_1 );
        const ValItem *r = a->mul( op->ch[ 1 ] );
        dec_ref( a );
        return r;
    }
    return op->sub( ch ); /// a * b + (-c) -> a*b-c
}

const ValItem *ValItemNeg::r_mul( const ValItem *op ) const { /// simplification de b * (-a)
    const ValItem *prod = op->mul( ch );
    const ValItem *res  = prod->neg();
    dec_ref( prod );
    return res;
}

const ValItem *ValItemNeg::r_mul( const ValItemNumberC *op ) const {
    const ValItem *n = op->neg();
    const ValItem *r = n->mul( ch );
    dec_ref( n );
    return r;
}

const ValItem *ValItemNeg::r_mul( const ValItemNumberI *op ) const {
    const ValItem *n = op->neg();
    const ValItem *r = n->mul( ch );
    dec_ref( n );
    return r;
}

const ValItem *ValItemNeg::r_mul( const ValItemNumberR *op ) const {
    const ValItem *n = op->neg();
    const ValItem *r = n->mul( ch );
    dec_ref( n );
    return r;
}

const ValItem *ValItemNeg::r_mul( const ValItemNumberD *op ) const {
    const ValItem *n = op->neg();
    const ValItem *r = n->mul( ch );
    dec_ref( n );
    return r;
}


}
