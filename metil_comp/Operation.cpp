/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "ValItemeration.h"
#include "Type.h"
#include "StdValItem.h"
#include "File.h"


namespace Metil {

const Type *Operation::type_promote( const Type *t ) const {
    return t;
}

const Type *Operation::type_promote( const Type *t0, const Type *t1 ) const {
    bool is_integer = t0->is_integer() and t1->is_integer();
    bool is_floating = t0->is_floating() or t1->is_floating();
    bool is_signed = t0->is_signed() or t1->is_signed();
    bool is_rationnal = ( t0->is_rational() or t1->is_rational() ) and t0->is_floating() == false and t1->is_floating() == false;
    int nb_bits_in_mantissa = (
            t0->is_floating() or t1->is_floating() ?
            max( t0->nb_bits_in_mantissa() * t0->is_floating(), t1->nb_bits_in_mantissa() * t1->is_floating() ) :
            max( t0->nb_bits_in_mantissa()                    , t1->nb_bits_in_mantissa()                     )
    );
    int nb_bits_in_exponent = max( t0->nb_bits_in_exponent(), t1->nb_bits_in_exponent() );
    int tensor_order = 0;
    int *static_size = 0;
    int *size = 0;
    return type_with_carac( is_integer, is_floating, is_signed, is_rationnal, nb_bits_in_mantissa,
        nb_bits_in_exponent, tensor_order, static_size, size );
}

// ------------ ------------ ------------ ------------ ------------ ------------ ------------
struct ValItemerationFloat : public ValItemeration {
    virtual bool conserve_zero() const { return true; } // by default
    virtual bool conserve_integers() const { return false; }
};

struct ValItemerationBinary : public ValItemeration {
    virtual bool conserve_zero() const { return true; }
    virtual bool conserve_integers() const { return true; }
    virtual const Type *type_promote( const Type *t ) const { return t; }
};

// ------------ ------------ ------------ ------------ ------------ ------------ ------------
struct ValItemerationAbs : public ValItemeration {
    virtual bool conserve_zero() const { return true; }
    virtual bool conserve_integers() const { return true; }
};

struct ValItemerationAcos : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationAsin : public ValItemerationFloat {
};

struct ValItemerationAtan : public ValItemerationFloat {
};

struct ValItemerationCos : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationCosh : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationExp : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationLog : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationLog10 : public ValItemerationFloat {
    virtual bool conserve_zero() const { return false; }
};

struct ValItemerationSin : public ValItemerationFloat {
};

struct ValItemerationSinh : public ValItemerationFloat {
};
struct ValItemerationSqrt : public ValItemerationFloat {
};

struct ValItemerationTan : public ValItemerationFloat {
};

struct ValItemerationTanh : public ValItemerationFloat {
};

struct ValItemerationReal : public ValItemerationFloat {
};

struct ValItemerationImag : public ValItemerationFloat {
};

struct ValItemerationArg : public ValItemerationFloat {
};

// ------------------------------------------------------------------------------------

struct ValItemerationPlus       : public ValItemerationBinary {};
struct ValItemerationMinus      : public ValItemerationBinary {};
struct ValItemerationModulus    : public ValItemerationBinary {};
struct ValItemerationDivides    : public ValItemerationBinary {};
struct ValItemerationEqual      : public ValItemerationBinary {};
struct ValItemerationNot_equal  : public ValItemerationBinary {};
struct ValItemerationLess       : public ValItemerationBinary {};
struct ValItemerationGreater    : public ValItemerationBinary {};
struct ValItemerationLesseq     : public ValItemerationBinary {};
struct ValItemerationGreatereq  : public ValItemerationBinary {};
struct ValItemerationAnd        : public ValItemerationBinary {};
struct ValItemerationOr         : public ValItemerationBinary {};
struct ValItemerationXor        : public ValItemerationBinary {};
struct ValItemerationAndand     : public ValItemerationBinary {};
struct ValItemerationOror       : public ValItemerationBinary {};
struct ValItemerationShiftleft  : public ValItemerationBinary {};
struct ValItemerationShiftright : public ValItemerationBinary {};
struct ValItemerationMin        : public ValItemerationBinary {};
struct ValItemerationMax        : public ValItemerationBinary {};
struct ValItemerationPow        : public ValItemerationBinary {};

// ------------ ------------ ------------ ------------ ------------ ------------ ------------
OperationAbs   inst_operation_abs  ;
OperationAcos  inst_operation_acos ;
OperationAsin  inst_operation_asin ;
OperationAtan  inst_operation_atan ;
OperationCos   inst_operation_cos  ;
OperationCosh  inst_operation_cosh ;
OperationExp   inst_operation_exp  ;
OperationLog   inst_operation_log  ;
OperationLog10 inst_operation_log10;
OperationSin   inst_operation_sin  ;
OperationSinh  inst_operation_sinh ;
OperationSqrt  inst_operation_sqrt ;
OperationTan   inst_operation_tan  ;
OperationTanh  inst_operation_tanh ;
OperationReal  inst_operation_real ;
OperationImag  inst_operation_imag ;
OperationArg   inst_operation_arg  ;

OperationPlus       inst_operation_plus      ;
OperationMinus      inst_operation_minus     ;
OperationModulus    inst_operation_modulus   ;
OperationDivides    inst_operation_divides   ;
OperationEqual      inst_operation_equal     ;
OperationNot_equal  inst_operation_not_equal ;
OperationLess       inst_operation_less      ;
OperationGreater    inst_operation_greater   ;
OperationLesseq     inst_operation_lesseq    ;
OperationGreatereq  inst_operation_greatereq ;
OperationAnd        inst_operation_and       ;
OperationOr         inst_operation_or        ;
OperationXor        inst_operation_xor       ;
OperationAndand     inst_operation_andand    ;
OperationOror       inst_operation_oror      ;
OperationShiftleft  inst_operation_shiftleft ;
OperationShiftright inst_operation_shiftright;
OperationMin        inst_operation_min       ;
OperationMax        inst_operation_max       ;
OperationPow        inst_operation_pow       ;

// ------------ ------------ ------------ ------------ ------------ ------------ ------------
Operation *operation_abs   = &inst_operation_abs  ;
Operation *operation_acos  = &inst_operation_acos ;
Operation *operation_asin  = &inst_operation_asin ;
Operation *operation_atan  = &inst_operation_atan ;
Operation *operation_cos   = &inst_operation_cos  ;
Operation *operation_cosh  = &inst_operation_cosh ;
Operation *operation_exp   = &inst_operation_exp  ;
Operation *operation_log   = &inst_operation_log  ;
Operation *operation_log10 = &inst_operation_log10;
Operation *operation_sin   = &inst_operation_sin  ;
Operation *operation_sinh  = &inst_operation_sinh ;
Operation *operation_sqrt  = &inst_operation_sqrt ;
Operation *operation_tan   = &inst_operation_tan  ;
Operation *operation_tanh  = &inst_operation_tanh ;
Operation *operation_real  = &inst_operation_real ;
Operation *operation_imag  = &inst_operation_imag ;
Operation *operation_arg   = &inst_operation_arg  ;

Operation *operation_plus       = &inst_operation_plus      ;
Operation *operation_minus      = &inst_operation_minus     ;
Operation *operation_modulus    = &inst_operation_modulus   ;
Operation *operation_divides    = &inst_operation_divides   ;
Operation *operation_equal      = &inst_operation_equal     ;
Operation *operation_not_equal  = &inst_operation_not_equal ;
Operation *operation_less       = &inst_operation_less      ;
Operation *operation_greater    = &inst_operation_greater   ;
Operation *operation_lesseq     = &inst_operation_lesseq    ;
Operation *operation_greatereq  = &inst_operation_greatereq ;
Operation *operation_and        = &inst_operation_and       ;
Operation *operation_or         = &inst_operation_or        ;
Operation *operation_xor        = &inst_operation_xor       ;
Operation *operation_andand     = &inst_operation_andand    ;
Operation *operation_oror       = &inst_operation_oror      ;
Operation *operation_shiftleft  = &inst_operation_shiftleft ;
Operation *operation_shiftright = &inst_operation_shiftright;
Operation *operation_min        = &inst_operation_min       ;
Operation *operation_max        = &inst_operation_max       ;
Operation *operation_pow        = &inst_operation_pow       ;

// ------------ ------------ ------------ ------------ ------------ ------------ ------------
const Type *type_promote( const ValItemeration *op, const Type *t1 ) {
    if ( t1->is_integer() ) {
        if ( op->conserve_integers() )
            return t1;
        return t1->corresponding_floating_point();
    }
    return op->type_promote( t1 );
}

const Type *type_promote( const ValItemeration *op, const Type *t1, const Type *t2 ) {
    return op->type_promote( t1, t2 );
}

}
