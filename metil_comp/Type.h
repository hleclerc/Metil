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

#ifndef METIL_TYPE_H
#define METIL_TYPE_H

#include "StructForType.h"
#include "TypeConfig.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Type.cpp
#endif

namespace Metil {

/**
*/
struct Type {
    virtual bool is_integer() const = 0;
    virtual bool is_floating() const = 0;
    virtual bool is_signed() const = 0;
    virtual bool is_rational() const = 0;
    virtual int nb_bits_in_mantissa() const = 0;
    virtual int nb_bits_in_exponent() const = 0;
    virtual int tensor_order() const = 0;
    virtual int static_size( int dim = 0 ) const = 0; // if tensor order
    virtual int size( int dim = 0 ) const = 0;
    virtual const Type *corresponding_floating_point() const;
    virtual void write_to_stream( class Stream &stream ) const = 0;
    virtual int size_in_bytes() const = 0;
    virtual void write_cpp_type( Stream &stream ) const = 0;
    virtual void write_cpp_value( Stream &stream, const void *val ) const = 0;
    virtual int alignement() const;
    virtual void *allocate( Int64 s ) const = 0;

    /// Generic write. "this" is the dst type.
    virtual void write( void *dst, const Type *src_type, const void *src, Int64 size ) const;

    virtual void write( void *dst, const Float32    *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Float64    *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Float96    *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Int8       *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Int16      *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Int32      *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Int64      *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Unsigned8  *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Unsigned16 *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Unsigned32 *src, Int64 size ) const; // "this" is the dst type
    virtual void write( void *dst, const Unsigned64 *src, Int64 size ) const; // "this" is the dst type


    virtual void r_write( Float32    *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Float64    *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Float96    *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Int8       *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Int16      *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Int32      *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Int64      *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Unsigned8  *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Unsigned16 *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Unsigned32 *dst, const void *src, Int64 size ) const; // "this" is the src type
    virtual void r_write( Unsigned64 *dst, const void *src, Int64 size ) const; // "this" is the src type
};

extern const Type *type_Float32   ;
extern const Type *type_Float64   ;
extern const Type *type_Float96   ;
extern const Type *type_Int8      ;
extern const Type *type_Int16     ;
extern const Type *type_Int32     ;
extern const Type *type_Int64     ;
extern const Type *type_Unsigned8 ;
extern const Type *type_Unsigned16;
extern const Type *type_Unsigned32;
extern const Type *type_Unsigned64;


const Type *type_ptr( StructForType<Float32> );
const Type *type_ptr( StructForType<Float64> );
const Type *type_ptr( StructForType<Float96> );
const Type *type_ptr( StructForType<Int8 > );
const Type *type_ptr( StructForType<Int16> );
const Type *type_ptr( StructForType<Int32> );
const Type *type_ptr( StructForType<Int64> );
const Type *type_ptr( StructForType<Unsigned8 > );
const Type *type_ptr( StructForType<Unsigned16> );
const Type *type_ptr( StructForType<Unsigned32> );
const Type *type_ptr( StructForType<Unsigned64> );

template<class T> const Type *type_ptr( StructForType<T> ) { return 0; }

const Type *ptr_on( const Type *type );

const Type *type_with_carac(
        bool is_integer,
        bool is_floating,
        bool is_signed,
        bool is_rationnal,
        int nb_bits_in_mantissa,
        int nb_bits_in_exponent,
        int tensor_order,
        int *static_size,
        int *size );

}


#endif // METIL_TYPE_H
