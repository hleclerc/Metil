#include "TypeConstructor_SymbolicExpression.h"
#include "TypeConstructor_Cst.h"

BEG_METIL_LEVEL1_NAMESPACE;

static char char_type( TypeConstructor *constructor ) {
    if ( dynamic_cast<TypeConstructor_SymbolicExpression *>( constructor ) )
        return 'P';
    return 'V';
}

static bool make_expr_add( MethodWriter &mw, const Mos *args, const String &ret ) {
    Type *t_0 = mw.get_type( 0 ), *t_1 = mw.get_type( 1 );
    // a + 0,  0 + b
    if ( int e = t_1->constructor->equ_code( mw, args[ 1 ], "0" ) ) { mw.n << ret << "CM_1( copy, " << args[ 0 ] << " );"; mw.ret(); if ( e > 1 ) return true; }
    if ( int e = t_0->constructor->equ_code( mw, args[ 0 ], "0" ) ) { mw.n << ret << "CM_1( copy, " << args[ 1 ] << " );"; mw.ret(); if ( e > 1 ) return true; }
}

static Val make_op( const Val &a, const Val &b, const String &op ) {
    if ( op == "mul" ) return a * b;
    ERROR( "unmanaged op %s", op.c_str() );
    return 0;
}

static bool make_expr_mul( MethodWriter &mw, const Mos *args, const String &ret ) {
    Type *t_0 = mw.get_type( 0 ), *t_1 = mw.get_type( 1 );
    // a * 0, 0 * b
    if ( int e = t_1->constructor->equ_code( mw, args[ 1 ], "0" ) ) { mw.n << ret << "&metil_type_cst_Cst_0;"; mw.ret(); if ( e > 1 ) return true; }
    if ( int e = t_0->constructor->equ_code( mw, args[ 0 ], "0" ) ) { mw.n << ret << "&metil_type_cst_Cst_0;"; mw.ret(); if ( e > 1 ) return true; }
    // a * 1, 1 * b
    if ( int e = t_1->constructor->equ_code( mw, args[ 1 ], "1" ) ) { mw.n << ret << "CM_1( copy, " << args[ 0 ] << " );"; mw.ret(); if ( e > 1 ) return true; }
    if ( int e = t_0->constructor->equ_code( mw, args[ 0 ], "1" ) ) { mw.n << ret << "CM_1( copy, " << args[ 1 ] << " );"; mw.ret(); if ( e > 1 ) return true; }
    // a * -1, -1 * b
    if ( int e = t_1->constructor->equ_code( mw, args[ 1 ], "m_1" ) ) { mw.n << ret << "CM_1( neg, " << args[ 0 ] << " );"; mw.ret(); if ( e > 1 ) return true; }
    if ( int e = t_0->constructor->equ_code( mw, args[ 0 ], "m_1" ) ) { mw.n << ret << "CM_1( neg, " << args[ 1 ] << " );"; mw.ret(); if ( e > 1 ) return true; }

    return false;
}

void make_expr( MethodWriter &mw, const Mos *args, const String &ret, const String &op ) {
    if ( op == "add" and make_expr_add( mw, args, ret ) )
        return;
    if ( op == "mul" and make_expr_mul( mw, args, ret ) )
        return;


    // op( cst, number ) or op( number, cst )
    //    TypeConstructor_Cst *cst_0 = dynamic_cast<TypeConstructor_Cst *>( t_0->constructor );
    //    TypeConstructor_Cst *cst_1 = dynamic_cast<TypeConstructor_Cst *>( t_1->constructor );
    //    if ( cst_0 ) {
    //        if ( cst_1 ) {
    //            SI64 ia, ib;
    //            bool ca = cst_0->conversion_to( ia );
    //            bool cb = cst_1->conversion_to( ib );
    //            if ( ca and cb ) {
    //                Val res = make_op( ia, ib, "mul" );
    //                mw.n << ret << "NEW_Number( " << res << " );";
    //                mw.ret();
    //                return true;
    //            }
    //        } else {
    //        }
    //    } else if ( cst_1 ) {

    //    }


    // resulting type
    String op_type;
    op_type << "Op_" << op << '_';
    for( int i = 0; i < mw.nb_types(); ++i )
        op_type << char_type( mw.get_type( i )->constructor );
    mw.add_type_decl( op_type );

    // default behavior -> op( a, b, ... )
    mw.n << "Type *type = &metil_type_bas_" << op_type << ";";
    mw << ret << "MO( NEW( Owcp<" << mw.nb_types() << ">, type";
    for( int i = 0; i < mw.nb_types(); ++i )
        mw << ", " << args[ i ];
    mw.n << " ), type );";
}

#define DEF_OP( OP ) \
    void metil_gen_##OP##__when__a__isa__SymbolicExpression__or__b__isa__SymbolicExpression__pert__0( MethodWriter &mw, const Mos *args, const String &ret ) { \
        make_expr( mw, args, ret, #OP ); \
    }

// #define DECL_OP() ...

DEF_OP( add         );
DEF_OP( sub         );
DEF_OP( mul         );
DEF_OP( div         );
DEF_OP( quo         );
DEF_OP( mod         );
DEF_OP( pow         );
DEF_OP( atan2       );

DEF_OP( inf         ); // <
DEF_OP( infeq       ); // <=
DEF_OP( sup         ); // >
DEF_OP( supeq       ); // >=
DEF_OP( equal       ); // ==
DEF_OP( noteq       ); // !=

DEF_OP( bitwise_and ); // &
DEF_OP( bitwise_or  ); // |
DEF_OP( bitwise_xor ); // ^

DEF_OP( boolean_and ); // &&
DEF_OP( boolean_or  ); // ||
DEF_OP( boolean_xor ); // ^^

DEF_OP( neg         ); // -.
DEF_OP( inv         ); // 1/.
DEF_OP( sin         ); //
DEF_OP( cos         ); //
DEF_OP( tan         ); //
DEF_OP( asin        ); //
DEF_OP( acos        ); //
DEF_OP( atan        ); //
DEF_OP( abs         ); //
DEF_OP( sqrt        ); //
DEF_OP( rsqrt       ); //
DEF_OP( log         ); //
DEF_OP( exp         ); //
DEF_OP( sgn         ); //
DEF_OP( eqz         ); // == 0
DEF_OP( supeqz      ); // >= 0
DEF_OP( supz        ); // > 0
DEF_OP( infeqz      ); // <= 0
DEF_OP( infz        ); // < 0


void TypeConstructor_SymbolicExpression::default_mw( MethodWriter &mw ) const {
    TypeConstructor::default_mw( mw );
    mw.add_include( "Level1/Owcp.h" );
}

END_METIL_LEVEL1_NAMESPACE;
