/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESST FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef MALLOC_H

#define MALLOC_H

#include "Assert.h"
#include "Number.h"
#include "Allocator.h"
#include "CanBeDerived.h"

#include <new>

#ifdef USE_STD_ALLOC
    #include <cstdlib>
#endif

#ifdef DEBUG_ALLOC_LEVEL_1
    #include <typeinfo>
#endif

BEG_METIL_LEVEL1_NAMESPACE

template<int size>
void *_malloc( Number<size> ) { return Allocator<size>::malloc(); } ///< replacement of malloc for compile-time known sizes and mono-thread (~25 times faster than usual malloc)
void *_malloc( ST &size ); ///< replacement of malloc for mono-thread (~3 times faster than usual malloc)
template<int size>
void *_malloc_mt( Number<size> ) { return Allocator<size>::malloc_mt(); } ///< replacement of malloc for compile-time known sizes and mono-thread (~25 times faster than usual malloc)
void *_malloc_mt( ST &size ); ///< replacement of malloc for mono-thread (~3 times faster than usual malloc)

template<int size>
void _free( const void *address, Number<size> ) { Allocator<size>::free( address ); } ///< free for size known during compile time
void _free( const void *address, ST size ); ///< replacement of free for mono-thread
template<int size>
void _free_mt( const void *address, Number<size> ) { Allocator<size>::free_mt( address ); } ///< free for size known during compile time
void _free_mt( const void *address, ST size ); ///< replacement of free for mono-thread

template<class Obj> void _destroy( const Obj *obj ) { obj->~Obj(); } ///< call destructor (we needed a function to know the type of obj)

#ifdef USE_STD_ALLOC
    template<class T> inline void del_std( T *obj ) { obj->~T(); free( const_cast<void *>( reinterpret_cast<const void *>( obj ) ) ); }
    template<int size> void *malloc( Number<size> ) { return ::malloc( size ); }
    inline void *malloc( ST size ) { return std::malloc( size ); }
    inline void free( void *data, ST ) { return std::free( data ); }

    #define NEW( Obj, ... )          new( Metil::Level1::malloc( sizeof( Obj ) ) ) Obj( __VA_ARGS__ )
    #define DEL( obj )               Metil::Level1::del_std( obj );

    #define NEW_MT( Obj, ... )       new( Metil::Level1::malloc( sizeof( Obj ) ) ) Obj( __VA_ARGS__ )
    #define DEL_MT( obj )            Metil::Level1::del_std( obj )j

    #define MALLOC( size )           Metil::Level1::malloc( size )
    #define FREE( address, size )    Metil::Level1::free( address, size )

    #define MALLOC_MT( size )        Metil::Level1::malloc( size )
    #define FREE_MT( address, size ) Metil::Level1::free( const_cast<void *>( reinterpret_cast<const void *>( address ) ) )
#else

  #ifdef DEBUG_ALLOC_LEVEL_0
    ST &total_allocated_memory();

    template<class Obj>
    inline void _rem_allocated_memory_and_del( const Obj *obj ) {
        total_allocated_memory() -= true_sizeof( *obj );
        _destroy_and_free_obj( obj );
    }

    template<int size>
    inline void *_malloc_with_counter( Number<size>  ) { total_allocated_memory() += size; return _malloc( Number<size>() ); }

    inline void *_malloc_with_counter( ST &size ) { void *res = _malloc( size ); total_allocated_memory() += size; return res; }

    inline void _rem_allocated_mem_and_free( const void *address, ST size ) {
        total_allocated_memory() -= size;
        _free( address, size );
    }

    #define NEW( Obj, ... )       new( Metil::Level1::_malloc_with_counter( Metil::Level1::Number<sizeof(Obj)>() ) ) Obj( __VA_ARGS__ )
    #define DEL( obj )            Metil::Level1::_rem_allocated_memory_and_del( obj )

    #define MALLOC( size )        Metil::Level1::_malloc_with_counter( size )
    #define FREE( address, size ) Metil::Level1::_rem_allocated_mem_and_free( address, size )

    #define __DEBUG_ALLOC__
  #endif // DEBUG_ALLOC_LEVEL_0
  #ifdef DEBUG_ALLOC_LEVEL_1
    void *_add_alloc_obj_ref( ST nb_objects, void *obj, const char *name, int line, const char *file );
    bool  _rem_alloc_obj_ref( ST nb_objects, const void *obj, const char *name, int line, const char *file );

    void *_add_alloc_obj_ref_mt( ST nb_objects, void *obj, const char *name, int line, const char *file );
    bool  _rem_alloc_obj_ref_mt( ST nb_objects, const void *obj, const char *name, int line, const char *file );

    template<class Obj>
    void _rem_alloc_obj_ref_and_del( ST nb_objects, const Obj *obj, int line, const char *file ) {
        if ( _rem_alloc_obj_ref( nb_objects, obj, typeid( Obj ).name(), line, file ) )
            _destroy_and_free_obj( obj );
    }

    inline void _rem_alloc_obj_ref_and_free( ST size, const void *address, const char *name, int line, const char *file ) {
        if ( _rem_alloc_obj_ref( size, address, name, line, file ) )
            _free( address, size );
    }

    template<class Obj>
    void _rem_alloc_obj_ref_and_del_mt( ST nb_objects, const Obj *obj, int line, const char *file ) {
        if ( _rem_alloc_obj_ref_mt( nb_objects, obj, typeid( Obj ).name(), line, file ) )
            _destroy_and_free_obj_mt( obj );
    }

    inline void _rem_alloc_obj_ref_and_free_mt( ST size, const void *address, const char *name, int line, const char *file ) {
        if ( _rem_alloc_obj_ref_mt( size, address, name, line, file ) )
            _free_mt( address, size );
    }

    #define NEW( Obj, ... )          new( Metil::Level1::_add_alloc_obj_ref( 1, Metil::Level1::_malloc( Metil::Level1::Number<sizeof(Obj)>() ), typeid( Obj ).name(), __LINE__, __FILE__ ) ) Obj( __VA_ARGS__ )
    #define DEL( obj )               Metil::Level1::_rem_alloc_obj_ref_and_del( 1, obj, __LINE__, __FILE__ )
    #define MALLOC( size )           Metil::Level1::_add_alloc_obj_ref( size, Metil::Level1::_malloc( size ), "anonymous byte", __LINE__, __FILE__ )
    #define FREE( address, size )    Metil::Level1::_rem_alloc_obj_ref_and_free( size, address, "anonymous byte", __LINE__, __FILE__ )

    #define NEW_MT( Obj, ... )       new( Metil::Level1::_add_alloc_obj_ref_mt( 1, Metil::Level1::_malloc_mt( Metil::Level1::Number<sizeof(Obj)>() ), typeid( Obj ).name(), __LINE__, __FILE__ ) ) Obj( __VA_ARGS__ )
    #define DEL_MT( obj )            Metil::Level1::_rem_alloc_obj_ref_and_del_mt( 1, obj, __LINE__, __FILE__ )
    #define MALLOC_MT( size )        Metil::Level1::_add_alloc_obj_ref_mt( size, Metil::_malloc_mt( size ), "anonymous byte", __LINE__, __FILE__ )
    #define FREE_MT( address, size ) Metil::Level1::_rem_alloc_obj_ref_and_free_mt( size, address, "anonymous byte", __LINE__, __FILE__ )

    #define __DEBUG_ALLOC__
  #endif // DEBUG_ALLOC_LEVEL_1
  #ifndef __DEBUG_ALLOC__
    template<class Obj> void _destroy_and_free_obj( const Obj *obj, Number<0> ) { obj->~Obj(); Allocator<sizeof(Obj)>::free( obj ); }
    template<class Obj> void _destroy_and_free_obj( const Obj *obj, Number<1> ) { obj->_free(); }
    template<class Obj> void _destroy_and_free_obj( const Obj *obj ) { _destroy_and_free_obj( obj, Number<CanBeDerived<Obj>::res>() ); }

    template<class Obj> void _destroy_and_free_obj_mt( const Obj *obj, Number<0> ) { obj->_free_mt(); }
    template<class Obj> void _destroy_and_free_obj_mt( const Obj *obj, Number<1> ) { obj->~Obj(); Allocator<sizeof(Obj)>::free_mt( obj ); }
    template<class Obj> inline void _destroy_and_free_obj_mt( const Obj *obj ) { _destroy_and_free_obj_mt( obj, Number<CanBeDerived<Obj>::res>() ); }

    #define NEW( Obj, ... )          new( Metil::Level1::Allocator<sizeof(Obj)>::malloc() ) Obj( __VA_ARGS__ )
    #define DEL( obj )               Metil::Level1::_destroy_and_free_obj( obj )

    #define MALLOC( size )           Metil::Level1::_malloc( size )
    #define FREE( address, size )    Metil::Level1::_free( address, size )

    #define NEW_MT( Obj, ... )       new( Metil::Level1::Allocator<sizeof(Obj)>::malloc_mt() ) Obj( __VA_ARGS__ )
    #define DEL_MT( obj )            Metil::Level1::_destroy_and_free_obj_mt( obj )

    #define MALLOC_MT( size )        Metil::Level1::_malloc_mt( size )
    #define FREE_MT( address, size ) Metil::Level1::_free_mt( address, size )
#endif // __DEBUG_ALLOC__

#endif // USE_STD_ALLOC

#define ALLOC_STATIC_VEC( T, size )    reinterpret_cast<T *>( Metil::Level1::malloc( Metil::Number< size * sizeof( T ) >() ) )
#define NEW_VAR( r, Obj, ... )          Obj *r = NEW( Obj, ##__VA_ARGS__ )


// --------------------------------------------------------------------
#define NEW_AND_DEL_COMPATIBLE \
    enum { can_be_derived = 1 }; \
    virtual void _free() const { Metil::Level1::_destroy( this ); Metil::Level1::Allocator<sizeof(*this)>::free( this ); } \
    virtual ST _size() const { return sizeof( *this ); }

#define NEW_AND_DEL_COMPATIBLE_PURE_VIRTUAL \
    enum { can_be_derived = 1 }; \
    virtual void _free() const = 0; \
    virtual ST _size() const = 0

#define CANNOT_BE_DERIVED \
    enum { can_be_derived = 0 }

template<class T> ST true_sizeof( const T &obj, Number<1> ) { return obj._size(); }
template<class T> ST true_sizeof( const T &obj, Number<0> ) { return sizeof( T ); }
template<class T> ST true_sizeof( const T &obj ) { return true_sizeof( obj, Number<CanBeDerived<T>::res>() ); } ///< if object is a reference, it can point to a child in the hierarchy... In this case sizeof() gives only the size of the parent.

// ----------------- reg_obj_to_be_deleted_at_the_end -----------------

///// @see reg_obj_to_be_deleted_at_the_end
//struct ObjectDeleter {
//    ObjectDeleter( const char *file, int line ): file( file ), line( line ) {}
//    virtual ~ObjectDeleter();
//    virtual void _free() const = 0;
//    virtual ST _size() const = 0;
//    ObjectDeleter *prev;
//    const char *file;
//    int line;
//};
//
///// @see reg_obj_to_be_deleted_at_the_end
//template<class T>
//struct ObjectDeleterT : public ObjectDeleter {
//    NEW_AND_DEL_COMPATIBLE
//    ObjectDeleterT( const T *data, const char *file, int line ) : ObjectDeleter( file, line ), data( data ) {}
//    virtual ~ObjectDeleterT() { DEL( data ); }
//    const T *data;
//};
//
///// @see reg_obj_to_be_deleted_at_the_end
//void _reg_obj_to_be_deleted_at_the_end( ObjectDeleter *obj );
//
///// obj will be freed at the end (before the memory checks)
//template<class Obj> Obj *reg_obj_to_be_deleted_at_the_end( Obj *obj, const char *file, int line ) {
//    _reg_obj_to_be_deleted_at_the_end( NEW( ObjectDeleterT<Obj>, obj, file, line ) );
//    return obj;
//}


END_METIL_LEVEL1_NAMESPACE

#endif // MALLOC_H
