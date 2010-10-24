#ifndef OPNUMBER_H
#define OPNUMBER_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ValItemNumber.cpp
#endif

namespace Metil {

///
struct ValItemNumber : public ValItem {
    virtual bool is_a_Number() const { return true; }
    virtual void add_parent( const ValItem *p ) const { inc_ref( this ); }
    virtual void rem_parent( const ValItem *p ) const { dec_ref( this ); }

    virtual bool done() const { return true; }
    virtual void exec_node() const {}

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

    void poly_deg_rec() const {
        if ( op_id == current_op_id )
            return; op_id = ValItem::current_op_id;
        reinterpret_cast<int &>( op_mp ) = is_always_equal_to_zero() ? 0 : -1;
    }

    virtual const ValItem *r_mul( const ValItem    *op ) const;
    virtual const ValItem *r_mul( const ValItemMul *op ) const;
    virtual const ValItem *r_mul( const ValItemNeg *op ) const;

    virtual const ValItem *as_Number() const { return this; }
};

extern const ValItem *number_0;  // 0
extern const ValItem *number_1;  // 1
extern const ValItem *number_2;  // 2
extern const ValItem *number_m1; // -1
extern const ValItem *number_05; // 0.5
extern const ValItem *number_pi; // pi ~ 3.14

const ValItemNumber *new_number( const BigInt &val );
const ValItemNumber *new_number( const Int32 &val );
const ValItemNumber *new_number( const Int64 &val );

const ValItemNumber *new_number( const BigInt &den, const BigInt &num );
const ValItemNumber *new_number( const BigRat &val );

const ValItemNumber *new_number( Float32 val );
const ValItemNumber *new_number( Float64 val );

// -------------------------------------------------------------------------------------------------------------------------------

/// computed number
struct ValItemNumberC : public ValItemNumber {
    ValItemNumberC( const ValItem *op ) : ch( op ) {
        ch->add_parent( this );
    }

    virtual ~ValItemNumberC() {
        ch->rem_parent( this );
    }

    virtual int nb_children() const { return 1; }
    virtual const ValItem *child( int i ) const { return ch; }
    virtual void dec_ref_op_mp_rec_children() const { ch->dec_ref_op_mp_rec(); }

    virtual void get_type_name( Stream &os ) const { os << "ValItemNumberC"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "nb"; }
    virtual void get_tex_sym    ( Stream &os ) const {}
    virtual void write_to_stream( Stream &os, int priority_parent ) const { ch->write_to_stream( os, priority() ); }
    virtual void write_tex      ( Stream &os, int priority_parent ) const { ch->write_tex      ( os, priority() ); }

    virtual int priority() const { return 0; }

    virtual const ValItem *sin() const { return ch->sin()->as_Number(); }
    virtual const ValItem *cos() const { return ch->cos()->as_Number(); }
    virtual const ValItem *log() const { return ch->log()->as_Number(); }
    virtual const ValItem *neg() const { return ch->neg()->as_Number(); }
    virtual const ValItem *inv() const { return ch->inv()->as_Number(); }

    virtual const ValItem *add( const ValItem *op ) const { return op->r_add( this ); }
    virtual const ValItem *sub( const ValItem *op ) const { return op->r_sub( this ); }
    virtual const ValItem *mul( const ValItem *op ) const { return op->r_mul( this ); }
    virtual const ValItem *div( const ValItem *op ) const { return op->r_div( this ); }
    virtual const ValItem *pow( const ValItem *op ) const { return op->r_pow( this ); }

    virtual const ValItem *r_add( const ValItemNumberC *op ) const { return op->ch->add( ch )->as_Number(); }
    virtual const ValItem *r_sub( const ValItemNumberC *op ) const { return op->ch->sub( ch )->as_Number(); }
    virtual const ValItem *r_mul( const ValItemNumberC *op ) const { return op->ch->mul( ch )->as_Number(); }
    virtual const ValItem *r_div( const ValItemNumberC *op ) const { return op->ch->div( ch )->as_Number(); }
    virtual const ValItem *r_pow( const ValItemNumberC *op ) const { return op->ch->pow( ch )->as_Number(); }

    virtual const ValItem *make_operation( const ValItem *a ) const { return inc_ref( this ); }

    const ValItem *ch;
};

///
template<class T>
struct ValItemNumberT : public ValItemNumber {
    template<class T0>
    ValItemNumberT( const T0 &v0 ) : val( v0 ) {}

    template<class T0,class T1>
    ValItemNumberT( const T0 &v0, const T1 &v1 ) : val( v0, v1 ) {}

    virtual void write_to_stream( Stream &os, int priority_parent ) const { os << val; }
    virtual void write_tex      ( Stream &os, int priority_parent ) const { os << val; }
    virtual void get_tiny_repr( Stream &os ) const { os << val; }
    virtual const Type *type() const { return type_ptr( StructForType<T>() ); }
    virtual int priority() const { return 0; }

    virtual int nb_children() const { return 0; }
    virtual const ValItem *child( int i ) const { return 0; }

    virtual void dec_ref_op_mp_rec_children() const {}

    virtual bool get_val( int   &v ) const { v = val; return true; }
    virtual bool get_val( double &v ) const { v = val; return true; }

    T val;
};


///
struct ValItemNumberI : public ValItemNumberT<BigInt> {
    ValItemNumberI( BigInt val ) : ValItemNumberT<BigInt>( val ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemNumberI"; }

    virtual bool is_always_an_integer() const { return true; }
    virtual bool get_val( int &v ) const { v = val; return Metil::abs( val ) <= BigInt( std::numeric_limits<int>::max() ); }

    virtual bool is_always_strictly_positive() const { return val.is_strictly_positive(); }
    virtual bool is_always_positive_or_null () const { return val.is_positive_or_null (); }
    virtual bool is_always_equal_to_one     () const { return val.is_equal_to_one     (); }
    virtual bool is_always_equal_to_zero    () const { return val.is_equal_to_zero    (); }

    virtual const ValItem *neg() const { return new ValItemNumberI( -val ); }
    virtual const ValItem *inv() const { return new_number( 1, val ); }

    virtual const ValItem *sin() const;

    virtual const ValItem *add( const ValItem *op ) const;
    virtual const ValItem *sub( const ValItem *op ) const;
    virtual const ValItem *mul( const ValItem *op ) const;
    virtual const ValItem *div( const ValItem *op ) const;
    virtual const ValItem *pow( const ValItem *op ) const;

    virtual const ValItem *r_add( const ValItem *op ) const;
    virtual const ValItem *r_sub( const ValItem *op ) const;
    virtual const ValItem *r_mul( const ValItem *op ) const;
    virtual const ValItem *r_div( const ValItem *op ) const;
    
    virtual const ValItem *r_add( const ValItemNumberC *op ) const;
    virtual const ValItem *r_add( const ValItemNumberI *op ) const;
    virtual const ValItem *r_add( const ValItemNumberR *op ) const;
    virtual const ValItem *r_add( const ValItemNumberD *op ) const;

    virtual const ValItem *r_sub( const ValItemNumberC *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberI *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberR *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberD *op ) const;

    virtual const ValItem *r_mul( const ValItemNumberC *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberI *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberR *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberD *op ) const;

    virtual const ValItem *r_div( const ValItemNumberC *op ) const;
    virtual const ValItem *r_div( const ValItemNumberI *op ) const;
    virtual const ValItem *r_div( const ValItemNumberR *op ) const;
    virtual const ValItem *r_div( const ValItemNumberD *op ) const;

    virtual const ValItem *r_pow( const ValItemNumberC *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberI *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberR *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberD *op ) const;
};

///
struct ValItemNumberR : public ValItemNumberT<BigRat> {
    ValItemNumberR( const BigRat &val ) : ValItemNumberT<BigRat>( val ) {}
    ValItemNumberR( const BigInt &num, const BigInt &den ) : ValItemNumberT<BigRat>( num, den ) {}
    ValItemNumberR( int num, int den ) : ValItemNumberT<BigRat>( num, den ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemNumberR"; }

    virtual bool is_always_an_integer() const { return val.is_integer(); }
    virtual bool is_always_equal_to_one_half() const { return val.is_equal_to_one_half(); }
    virtual bool get_val( int &v ) const { v = val; return Metil::abs( val ) <= BigInt( std::numeric_limits<int>::max() ) and val.is_integer(); }

    virtual bool is_always_strictly_positive() const { return val.is_strictly_positive(); }
    virtual bool is_always_positive_or_null () const { return val.is_positive_or_null (); }
    virtual bool is_always_equal_to_one     () const { return val.is_equal_to_one     (); }
    virtual bool is_always_equal_to_zero    () const { return val.is_equal_to_zero    (); }

    virtual const ValItem *neg() const { return new ValItemNumberR( -val ); }
    virtual const ValItem *inv() const { return new ValItemNumberR( 1/val/*::inv( val )*/ ); }

    virtual const ValItem *add( const ValItem *op ) const;
    virtual const ValItem *sub( const ValItem *op ) const;
    virtual const ValItem *mul( const ValItem *op ) const;
    virtual const ValItem *div( const ValItem *op ) const;
    virtual const ValItem *pow( const ValItem *op ) const;

    virtual const ValItem *r_add( const ValItem        *op ) const;
    virtual const ValItem *r_add( const ValItemNumberC *op ) const;
    virtual const ValItem *r_add( const ValItemNumberI *op ) const;
    virtual const ValItem *r_add( const ValItemNumberR *op ) const;
    virtual const ValItem *r_add( const ValItemNumberD *op ) const;

    virtual const ValItem *r_sub( const ValItem        *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberC *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberI *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberR *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberD *op ) const;

    virtual const ValItem *r_mul( const ValItem        *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberC *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberI *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberR *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberD *op ) const;

    virtual const ValItem *r_div( const ValItem        *op ) const;
    virtual const ValItem *r_div( const ValItemNumberC *op ) const;
    virtual const ValItem *r_div( const ValItemNumberI *op ) const;
    virtual const ValItem *r_div( const ValItemNumberR *op ) const;
    virtual const ValItem *r_div( const ValItemNumberD *op ) const;

    virtual const ValItem *r_pow( const ValItemNumberC *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberI *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberR *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberD *op ) const;
};

///
struct ValItemNumberD : public ValItemNumberT<double> {
    ValItemNumberD( double val ) : ValItemNumberT<double>( val ) {}

    virtual void get_type_name( Stream &os ) const { os << "ValItemNumberD"; }

    virtual bool is_always_an_integer() const { return round( val ) == val; }
    virtual bool is_always_equal_to_one_half() const { return val == 0.5; }
    virtual bool get_val( long &v ) const {
        v = long( val );
        return long( val ) == val and val <= std::numeric_limits<double>::max() and val >= -std::numeric_limits<double>::max();
    }

    virtual bool is_always_strictly_positive() const { return val >  0; }
    virtual bool is_always_positive_or_null () const { return val >= 0; }
    virtual bool is_always_equal_to_one     () const { return val == 1; }
    virtual bool is_always_equal_to_zero    () const { return val == 0; }

    virtual const ValItem *neg() const { return new_number( -val         ); }
    virtual const ValItem *inv() const { return new_number( 1.0 / val    ); }
    virtual const ValItem *cos() const { return new_number( ::cos( val ) ); }
    virtual const ValItem *sin() const { return new_number( ::sin( val ) ); }
    virtual const ValItem *log() const { return new_number( ::log( val ) ); }

    virtual const ValItem *add( const ValItem *op ) const;
    virtual const ValItem *sub( const ValItem *op ) const;
    virtual const ValItem *mul( const ValItem *op ) const;
    virtual const ValItem *div( const ValItem *op ) const;
    virtual const ValItem *pow( const ValItem *op ) const;

    virtual const ValItem *r_add( const ValItem        *op ) const;
    virtual const ValItem *r_add( const ValItemNumberC *op ) const;
    virtual const ValItem *r_add( const ValItemNumberI *op ) const;
    virtual const ValItem *r_add( const ValItemNumberR *op ) const;
    virtual const ValItem *r_add( const ValItemNumberD *op ) const;

    virtual const ValItem *r_sub( const ValItem        *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberC *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberI *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberR *op ) const;
    virtual const ValItem *r_sub( const ValItemNumberD *op ) const;

    virtual const ValItem *r_mul( const ValItem        *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberC *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberI *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberR *op ) const;
    virtual const ValItem *r_mul( const ValItemNumberD *op ) const;

    virtual const ValItem *r_div( const ValItem        *op ) const;
    virtual const ValItem *r_div( const ValItemNumberC *op ) const;
    virtual const ValItem *r_div( const ValItemNumberI *op ) const;
    virtual const ValItem *r_div( const ValItemNumberR *op ) const;
    virtual const ValItem *r_div( const ValItemNumberD *op ) const;

    virtual const ValItem *r_pow( const ValItemNumberC *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberI *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberR *op ) const;
    virtual const ValItem *r_pow( const ValItemNumberD *op ) const;
};

/// pi number ~ 3.14
struct ValItemNumberPI : public ValItemNumber {
    virtual ~ValItemNumberPI() {}

    virtual int nb_children() const { return 0; }
    virtual const ValItem *child( int i ) const { return NULL; }
    virtual void dec_ref_op_mp_rec_children() const {  }

    virtual void get_type_name( Stream &os ) const { os << "ValItemNumberPI"; }
    virtual void get_tiny_repr( Stream &os ) const { os << "pi"; }
    virtual void get_tex_sym    ( Stream &os ) const { os << "\\pi"; }
    virtual void write_to_stream( Stream &os, int priority_parent ) const { os << "pi"; }
    virtual void write_tex      ( Stream &os, int priority_parent ) const { /** ???? */}

    virtual int priority() const { return 0; }

    virtual const ValItem *sin() const { return inc_ref( number_0  ); }
    virtual const ValItem *cos() const { return inc_ref( number_m1 ); }

    virtual const ValItem *add( const ValItem *op ) const { return op->r_add( this ); }
    virtual const ValItem *sub( const ValItem *op ) const { return op->r_sub( this ); }
    virtual const ValItem *mul( const ValItem *op ) const { return op->r_mul( this ); }
    virtual const ValItem *div( const ValItem *op ) const { return op->r_div( this ); }
    virtual const ValItem *pow( const ValItem *op ) const { return op->r_pow( this ); }

//     virtual const ValItem *r_add( const ValItemNumberC *op ) const { return op->ch->add( ch )->as_Number(); }
//     virtual const ValItem *r_sub( const ValItemNumberC *op ) const { return op->ch->sub( ch )->as_Number(); }
//     virtual const ValItem *r_mul( const ValItemNumberC *op ) const { return op->ch->mul( ch )->as_Number(); }
//     virtual const ValItem *r_div( const ValItemNumberC *op ) const { return op->ch->div( ch )->as_Number(); }
//     virtual const ValItem *r_pow( const ValItemNumberC *op ) const { return op->ch->pow( ch )->as_Number(); }

    virtual const ValItem *make_operation( const ValItem *a ) const { return inc_ref( this ); }
};

}

#endif // OPNUMBER_H
