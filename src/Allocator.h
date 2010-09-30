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

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "TypeConfig.h"

BEG_METIL_LEVEL1_NAMESPACE

///
void *new_allocator_chunk( ST size_in_mem );
///
void *new_room_large_size( ST &size_in_mem );
///
void del_room_large_size( const void *data, ST size_in_mem );
///
void del_room_large_size_with_probably_wrong_reservation_size( const void *data, ST size_in_mem );

template<int size_>
struct SmallSizeAllocator {
    static const int size = ( size_ >= sizeof(void *) ? size_ : sizeof(void *) );

    // single thread
    static void *malloc() {
        void *res = free_room;
        if ( not res )
            res = new_allocator_chunk( size );
        free_room = *reinterpret_cast<void **>( res );
        return res;
    }
    static void *malloc( ST &real_size ) {
        real_size = size;
        return malloc();
    }
    static void free( const void *data ) {
        *reinterpret_cast<void **>( const_cast<void *>( data ) ) = free_room;
        free_room = const_cast<void *>( data );
    }

    // multithreaded version
    static void *malloc_mt() {
        lock();
        void *res = malloc();
        unlock();
        return res;
    }
    static void *malloc_mt( ST &real_size ) {
        real_size = size;
        return malloc_mt();
    }
    static void free_mt( const void *data ) {
        lock();
        *reinterpret_cast<void **>( const_cast<void *>( data ) ) = free_room;
        free_room = const_cast<void *>( data );
        unlock();
    }

    #ifdef USE_STD_ALLOC
    static void lock() {}
    static void unlock() {}
    #else
    static void lock();
    static void unlock();
    #endif

    static void *free_room;
};

template<int size>
struct LargeSizeAllocator {
    static void *malloc() {
        ST real_size = size;
        return new_room_large_size( real_size );
    }
    static void *malloc( ST &real_size ) {
        real_size = size;
        return new_room_large_size( real_size );
    }
    static void free( const void *data ) {
        del_room_large_size_with_probably_wrong_reservation_size( data, size );
    }
};

// small sizes -> look for specialization with small size
template<int size,bool large_size>
struct _Allocator : public _Allocator<( size + 4 ) & ~3, large_size> {};

// large size
template<int size> struct _Allocator<size,true> : public LargeSizeAllocator<size> {};

// see .cpp for generation
template<> struct _Allocator<   4,false> : SmallSizeAllocator<   4> {};
template<> struct _Allocator<   8,false> : SmallSizeAllocator<   8> {};
template<> struct _Allocator<  16,false> : SmallSizeAllocator<  16> {};
template<> struct _Allocator<  20,false> : SmallSizeAllocator<  20> {};
template<> struct _Allocator<  24,false> : SmallSizeAllocator<  24> {};
template<> struct _Allocator<  28,false> : SmallSizeAllocator<  28> {};
template<> struct _Allocator<  32,false> : SmallSizeAllocator<  32> {};
template<> struct _Allocator<  48,false> : SmallSizeAllocator<  48> {};
template<> struct _Allocator<  64,false> : SmallSizeAllocator<  64> {};
template<> struct _Allocator<  80,false> : SmallSizeAllocator<  80> {};
template<> struct _Allocator<  96,false> : SmallSizeAllocator<  96> {};
template<> struct _Allocator< 112,false> : SmallSizeAllocator< 112> {};
template<> struct _Allocator< 128,false> : SmallSizeAllocator< 128> {};
template<> struct _Allocator< 160,false> : SmallSizeAllocator< 160> {};
template<> struct _Allocator< 192,false> : SmallSizeAllocator< 192> {};
template<> struct _Allocator< 224,false> : SmallSizeAllocator< 224> {};
template<> struct _Allocator< 256,false> : SmallSizeAllocator< 256> {};
template<> struct _Allocator< 512,false> : SmallSizeAllocator< 512> {};
template<> struct _Allocator<1024,false> : SmallSizeAllocator<1024> {};
template<> struct _Allocator<2048,false> : SmallSizeAllocator<2048> {};
template<> struct _Allocator<4096,false> : SmallSizeAllocator<4096> {};
template<> struct _Allocator<6144,false> : SmallSizeAllocator<6144> {};
template<> struct _Allocator<8192,false> : SmallSizeAllocator<8192> {};
#define MaxSmallAllocatorSize 8192

template<int size>
struct Allocator : public _Allocator< size, ( size > MaxSmallAllocatorSize ) > {};

END_METIL_LEVEL1_NAMESPACE

#endif // ALLOCATOR_H
