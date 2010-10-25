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

#include "Type.h"
#include "Stream.h"
#include "AutoPtr.h"
#include "File.h"
#include "String.h"
#include "Memory.h"

#include <map>

namespace Metil {

void Type::write( void *dst, const Type *src_type, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }

void Type::write( void *dst, const Float32    *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Float64    *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Float96    *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Int8       *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Int16      *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Int32      *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Int64      *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Unsigned8  *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Unsigned16 *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Unsigned32 *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::write( void *dst, const Unsigned64 *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }

void Type::r_write( Float32    *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Float64    *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Float96    *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Int8       *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Int16      *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Int32      *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Int64      *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Unsigned8  *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Unsigned16 *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Unsigned32 *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }
void Type::r_write( Unsigned64 *dst, const void *src, Int64 size ) const { ASSERT( 0, "TODO with " + String( *this ) ); }

const Type *Type::corresponding_floating_point() const {
    return this;
}

int Type::alignement() const {
    return 1;
}

/// signed by default
template<class T>
struct TypeInstAncestor : public Type {
    virtual bool is_integer() const { return false; }
    virtual bool is_floating() const { return false; }
    virtual bool is_signed() const { return true; }
    virtual bool is_rational() const { return false; }
    virtual int nb_bits_in_mantissa() const { return 8 * sizeof( T ) - is_signed(); }
    virtual int nb_bits_in_exponent() const { return 0; }
    virtual int tensor_order() const { return 0; }
    virtual int static_size( int dim = 0 ) const { return -1; }
    virtual int size( int dim = 0 ) const { return 0; }
    virtual const Type *corresponding_floating_point() const { return type_Float64; }
    virtual void write_to_stream( class Stream &stream ) const { write_cpp_type( stream ); }
    virtual int size_in_bytes() const { return sizeof( T ); }
    virtual void write_cpp_value( Stream &stream, const void *val ) const { stream << *reinterpret_cast<const T *>( val ); }
    virtual void *allocate( Int64 s ) const { return memalign( sizeof( T ) * alignement(), sizeof( T ) * s ); }
};

///
template<class T>
struct TypeInstNumeric : public TypeInstAncestor<T> {
    virtual void write( void *dst, const Type *src_type, const void *src, Int64 size ) const { src_type->r_write( reinterpret_cast<T *>( dst ), src, size ); }
    
    virtual void write( void *dst, const Float32    *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Float64    *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Float96    *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Int8       *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Int16      *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Int32      *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Int64      *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Unsigned8  *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Unsigned16 *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Unsigned32 *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }
    virtual void write( void *dst, const Unsigned64 *src, Int64 size ) const { for(Int64 i=0;i<size;++i) reinterpret_cast<T *>( dst )[ i ] = T( src[ i ] ); }


    virtual void r_write( Float32    *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Float32   ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Float64    *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Float64   ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Float96    *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Float96   ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Int8       *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Int8      ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Int16      *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Int16     ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Int32      *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Int32     ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Int64      *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Int64     ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Unsigned8  *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Unsigned8 ( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Unsigned16 *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Unsigned16( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Unsigned32 *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Unsigned32( reinterpret_cast<const T *>( src )[ i ] ); }
    virtual void r_write( Unsigned64 *dst, const void *src, Int64 size ) const { for(Int64 i=0;i<size;++i) dst[ i ] = Unsigned64( reinterpret_cast<const T *>( src )[ i ] ); }
};

///
struct TypeInstFloat32 : public TypeInstNumeric<Float32> {
    virtual bool is_floating() const { return true; }
    virtual int nb_bits_in_mantissa() const { return 23; }
    virtual int nb_bits_in_exponent() const { return 8; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Float32"; }
};

///
struct TypeInstFloat64 : public TypeInstNumeric<Float64> {
    virtual bool is_floating() const { return true; }
    virtual int nb_bits_in_mantissa() const { return 52; }
    virtual int nb_bits_in_exponent() const { return 11; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Float64"; }
};

///
struct TypeInstFloat96 : public TypeInstNumeric<Float96> {
    virtual bool is_floating() const { return true; }
    virtual int nb_bits_in_mantissa() const { return 63; }
    virtual int nb_bits_in_exponent() const { return 32; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Float96"; }
};



///
struct TypeInstInt8 : public TypeInstNumeric<Int8> {
    virtual bool is_integer() const { return true; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Int8"; }
};

///
struct TypeInstInt16 : public TypeInstNumeric<Int16> {
    virtual bool is_integer() const { return true; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Int16"; }
};

///
struct TypeInstInt32 : public TypeInstNumeric<Int32> {
    virtual bool is_integer() const { return true; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Int32"; }
};

///
struct TypeInstInt64 : public TypeInstNumeric<Int64> {
    virtual bool is_integer() const { return true; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Int64"; }
};






///
struct TypeInstUnsigned8 : public TypeInstNumeric<Unsigned8> {
    virtual bool is_integer() const { return true; }
    virtual bool is_signed() const { return false; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Unsigned8"; }
};

///
struct TypeInstUnsigned16 : public TypeInstNumeric<Unsigned16> {
    virtual bool is_integer() const { return true; }
    virtual bool is_signed() const { return false; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Unsigned16"; }
};

///
struct TypeInstUnsigned32 : public TypeInstNumeric<Unsigned32> {
    virtual bool is_integer() const { return true; }
    virtual bool is_signed() const { return false; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Unsigned32"; }
};

///
struct TypeInstUnsigned64 : public TypeInstNumeric<Unsigned64> {
    virtual bool is_integer() const { return true; }
    virtual bool is_signed() const { return false; }
    virtual void write_cpp_type( Stream &stream ) const { stream << "Unsigned64"; }
};




// ----------------------------------------------- Type *type_... ----------------------------------------------------------

TypeInstFloat32    inst_type_Float32    ;
TypeInstFloat64    inst_type_Float64    ;
TypeInstFloat96    inst_type_Float96    ;
TypeInstInt8       inst_type_Int8       ;
TypeInstInt16      inst_type_Int16      ;
TypeInstInt32      inst_type_Int32      ;
TypeInstInt64      inst_type_Int64      ;
TypeInstUnsigned8  inst_type_Unsigned8  ;
TypeInstUnsigned16 inst_type_Unsigned16 ;
TypeInstUnsigned32 inst_type_Unsigned32 ;
TypeInstUnsigned64 inst_type_Unsigned64 ;

const Type *type_Float32    = &inst_type_Float32     ;
const Type *type_Float64    = &inst_type_Float64     ;
const Type *type_Float96    = &inst_type_Float96     ;
const Type *type_Int8       = &inst_type_Int8        ;
const Type *type_Int16      = &inst_type_Int16       ;
const Type *type_Int32      = &inst_type_Int32       ;
const Type *type_Int64      = &inst_type_Int64       ;
const Type *type_Unsigned8  = &inst_type_Unsigned8   ;
const Type *type_Unsigned16 = &inst_type_Unsigned16  ;
const Type *type_Unsigned32 = &inst_type_Unsigned32  ;
const Type *type_Unsigned64 = &inst_type_Unsigned64  ;

const Type *type_ptr( StructForType<Float32   > ) { return type_Float32   ; }
const Type *type_ptr( StructForType<Float64   > ) { return type_Float64   ; }
const Type *type_ptr( StructForType<Float96   > ) { return type_Float96   ; }
const Type *type_ptr( StructForType<Int8      > ) { return type_Int8      ; }
const Type *type_ptr( StructForType<Int16     > ) { return type_Int16     ; }
const Type *type_ptr( StructForType<Int32     > ) { return type_Int32     ; }
const Type *type_ptr( StructForType<Int64     > ) { return type_Int64     ; }
const Type *type_ptr( StructForType<Unsigned8 > ) { return type_Unsigned8 ; }
const Type *type_ptr( StructForType<Unsigned16> ) { return type_Unsigned16; }
const Type *type_ptr( StructForType<Unsigned32> ) { return type_Unsigned32; }
const Type *type_ptr( StructForType<Unsigned64> ) { return type_Unsigned64; }

// ------------------------------------------------- POINTERS --------------------------------------------------------
struct TypeInstPtr : public TypeInstAncestor<void *> {
    TypeInstPtr( const Type *sub_type ) : sub_type( sub_type ) {}
    virtual bool is_integer() const { return true; }
    virtual void write_cpp_type( Stream &stream ) const { sub_type->write_cpp_type( stream ); stream << "*"; }
    const Type *sub_type;
};

const Type *ptr_on( const Type *type ) {
    static std::map<const Type *,ConstAutoPtr<Type> > pointers_on;
    ConstAutoPtr<Type> &res = pointers_on[ type ];
    if ( not res.ptr() )
        res = new TypeInstPtr( type );
    return res.ptr();
}

// ------------------------------------------------- type with carac ------------------------------------------------------
const Type *type_with_carac(
        bool is_integer,
        bool is_floating,
        bool is_signed,
        bool is_rationnal,
        int nb_bits_in_mantissa,
        int nb_bits_in_exponent,
        int tensor_order,
        int *static_size,
        int *size ) {
    if ( is_integer ) {
        ASSERT( is_signed, "TODO not signed int" );
        if ( nb_bits_in_mantissa <= 31 )
            return type_Int32;
        if ( nb_bits_in_mantissa <= 63 )
            return type_Int64;
        ASSERT( nb_bits_in_mantissa <= 63, "TODO" );
        return 0;
    }
    if ( is_floating ) {
        if ( nb_bits_in_mantissa <= 23 ) {
            ASSERT( nb_bits_in_exponent <= 8, "nb_bits_in_exponent <= 8 with float" );
            return type_Float32;
        }
        if ( nb_bits_in_mantissa <= 52 ) {
            ASSERT( nb_bits_in_exponent <= 11, "nb_bits_in_exponent (" + String( nb_bits_in_exponent ) + ") <= 11 with double" );
            return type_Float64;
        }
        ASSERT( nb_bits_in_mantissa <= 52, "TODO" );
        return 0;
    }
    return 0;
}


}

