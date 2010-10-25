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

#ifndef METIL_OPERATION_H
#define METIL_OPERATION_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ValItemeration.cpp
#endif

namespace Metil {

struct Type;

/**
*/
struct ValItemeration {
    virtual bool conserve_zero() const = 0;
    virtual bool conserve_integers() const = 0;
    virtual const Type *type_promote( const Type *t ) const;
    virtual const Type *type_promote( const Type *t0, const Type *t1 ) const;
};

extern ValItemeration *operation_abs  ;
extern ValItemeration *operation_acos ;
extern ValItemeration *operation_asin ;
extern ValItemeration *operation_atan ;
extern ValItemeration *operation_cos  ;
extern ValItemeration *operation_cosh ;
extern ValItemeration *operation_exp  ;
extern ValItemeration *operation_log  ;
extern ValItemeration *operation_log10;
extern ValItemeration *operation_sin  ;
extern ValItemeration *operation_sinh ;
extern ValItemeration *operation_sqrt ;
extern ValItemeration *operation_tan  ;
extern ValItemeration *operation_tanh ;
extern ValItemeration *operation_real ;
extern ValItemeration *operation_imag ;
extern ValItemeration *operation_arg  ;

extern ValItemeration *operation_plus      ;
extern ValItemeration *operation_minus     ;
extern ValItemeration *operation_modulus   ;
extern ValItemeration *operation_divides   ;
extern ValItemeration *operation_equal     ;
extern ValItemeration *operation_not_equal ;
extern ValItemeration *operation_less      ;
extern ValItemeration *operation_greater   ;
extern ValItemeration *operation_lesseq    ;
extern ValItemeration *operation_greatereq ;
extern ValItemeration *operation_and       ;
extern ValItemeration *operation_or        ;
extern ValItemeration *operation_xor       ;
extern ValItemeration *operation_andand    ;
extern ValItemeration *operation_oror      ;
extern ValItemeration *operation_shiftleft ;
extern ValItemeration *operation_shiftright;
extern ValItemeration *operation_min       ;
extern ValItemeration *operation_max       ;
extern ValItemeration *operation_pow       ;

const Type *type_promote( const ValItemeration *op, const Type *t1 );
const Type *type_promote( const ValItemeration *op, const Type *t1, const Type *t2 );


}


#endif // METIL_OPERATION_H
