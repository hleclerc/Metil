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

#include "Allocator.h"

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/mman.h>
#endif

#ifndef USE_STD_ALLOC
    #include <pthread.h>
#endif

BEG_METIL_LEVEL1_NAMESPACE

static const int size_mmap = 8192;

void *new_allocator_chunk( ST size_in_mem ) {
    #ifdef WIN32
    void *res = malloc( size_mmap );
    #else
    void *res = mmap( 0, size_mmap, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0 ); // MAP_ANONYMOUS |
    #endif

    // chained list
    char *beg = reinterpret_cast<char *>( res );
    char *end = beg + size_mmap - 2 * size_in_mem + 1;
    for( ; beg < end ; beg += size_in_mem )
        *reinterpret_cast<void **>( beg ) = reinterpret_cast<void *>( beg + size_in_mem );
    *reinterpret_cast<void **>( beg ) = 0;

    return res;
}

/*
page_size := 4096
lst := Vec[S]([ 4 8 16 20 24 28 32 48 64 80 96 112 128 160 192 224 256 512 1024 2048 4096 6144 8192 ])

# -> .h
for s in lst
    print "template<> struct Allocator<$s,false> : public SmallSizeAllocator<$s> {};"
print "#define MaxSmallAllocatorSize " + lst.back

# -> .cpp
for s in lst
    n := String( s )
    print "template<> void *SmallSizeAllocator<$( " " * (4 - n.size) )$s>::free_room = 0;"

# -> .cpp
def write_malloc_find_rec( beg, end, spaces )
    if end - beg == 1
        size := l[ beg ]
        print spaces + "return _Allocator<$size,$(size>lst.back)>::malloc( size );"
    mid := ( beg + end ) / 2
    print "spaces + if ( size >= $( lst[ mid ] ) ) {"
    write_malloc_find_rec( beg, mid, spaces + "    " )
    print "} else {"
    write_malloc_find_rec( mid, end, spaces + "    " )
    print "}"

write_malloc_find_rec( 0, lst.size, "" )
*/
template<> void *SmallSizeAllocator<   4>::free_room = 0;
template<> void *SmallSizeAllocator<   8>::free_room = 0;
template<> void *SmallSizeAllocator<  16>::free_room = 0;
template<> void *SmallSizeAllocator<  20>::free_room = 0;
template<> void *SmallSizeAllocator<  24>::free_room = 0;
template<> void *SmallSizeAllocator<  28>::free_room = 0;
template<> void *SmallSizeAllocator<  32>::free_room = 0;
template<> void *SmallSizeAllocator<  48>::free_room = 0;
template<> void *SmallSizeAllocator<  64>::free_room = 0;
template<> void *SmallSizeAllocator<  80>::free_room = 0;
template<> void *SmallSizeAllocator<  96>::free_room = 0;
template<> void *SmallSizeAllocator< 112>::free_room = 0;
template<> void *SmallSizeAllocator< 128>::free_room = 0;
template<> void *SmallSizeAllocator< 160>::free_room = 0;
template<> void *SmallSizeAllocator< 192>::free_room = 0;
template<> void *SmallSizeAllocator< 224>::free_room = 0;
template<> void *SmallSizeAllocator< 256>::free_room = 0;
template<> void *SmallSizeAllocator< 512>::free_room = 0;
template<> void *SmallSizeAllocator<1024>::free_room = 0;
template<> void *SmallSizeAllocator<2048>::free_room = 0;
template<> void *SmallSizeAllocator<4096>::free_room = 0;
template<> void *SmallSizeAllocator<6144>::free_room = 0;
template<> void *SmallSizeAllocator<8192>::free_room = 0;

#ifndef USE_STD_ALLOC
template<int n> struct SmallSizeAllocatorMutex { static pthread_mutex_t mutex; };

template<> pthread_mutex_t SmallSizeAllocatorMutex<   4>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<   8>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  16>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  20>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  24>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  28>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  32>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  48>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  64>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  80>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<  96>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 112>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 128>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 160>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 192>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 224>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 256>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex< 512>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<1024>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<2048>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<4096>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<6144>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<> pthread_mutex_t SmallSizeAllocatorMutex<8192>::mutex = PTHREAD_MUTEX_INITIALIZER;

template<> void SmallSizeAllocator<   4>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<   4>::mutex ); }
template<> void SmallSizeAllocator<   8>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<   8>::mutex ); }
template<> void SmallSizeAllocator<  16>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  16>::mutex ); }
template<> void SmallSizeAllocator<  20>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  20>::mutex ); }
template<> void SmallSizeAllocator<  24>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  24>::mutex ); }
template<> void SmallSizeAllocator<  28>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  28>::mutex ); }
template<> void SmallSizeAllocator<  32>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  32>::mutex ); }
template<> void SmallSizeAllocator<  48>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  48>::mutex ); }
template<> void SmallSizeAllocator<  64>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  64>::mutex ); }
template<> void SmallSizeAllocator<  80>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  80>::mutex ); }
template<> void SmallSizeAllocator<  96>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<  96>::mutex ); }
template<> void SmallSizeAllocator< 112>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 112>::mutex ); }
template<> void SmallSizeAllocator< 128>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 128>::mutex ); }
template<> void SmallSizeAllocator< 160>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 160>::mutex ); }
template<> void SmallSizeAllocator< 192>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 192>::mutex ); }
template<> void SmallSizeAllocator< 224>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 224>::mutex ); }
template<> void SmallSizeAllocator< 256>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 256>::mutex ); }
template<> void SmallSizeAllocator< 512>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex< 512>::mutex ); }
template<> void SmallSizeAllocator<1024>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<1024>::mutex ); }
template<> void SmallSizeAllocator<2048>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<2048>::mutex ); }
template<> void SmallSizeAllocator<4096>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<4096>::mutex ); }
template<> void SmallSizeAllocator<6144>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<6144>::mutex ); }
template<> void SmallSizeAllocator<8192>::lock() { pthread_mutex_lock( &SmallSizeAllocatorMutex<8192>::mutex ); }

template<> void SmallSizeAllocator<   4>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<   4>::mutex ); }
template<> void SmallSizeAllocator<   8>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<   8>::mutex ); }
template<> void SmallSizeAllocator<  16>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  16>::mutex ); }
template<> void SmallSizeAllocator<  20>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  20>::mutex ); }
template<> void SmallSizeAllocator<  24>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  24>::mutex ); }
template<> void SmallSizeAllocator<  28>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  28>::mutex ); }
template<> void SmallSizeAllocator<  32>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  32>::mutex ); }
template<> void SmallSizeAllocator<  48>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  48>::mutex ); }
template<> void SmallSizeAllocator<  64>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  64>::mutex ); }
template<> void SmallSizeAllocator<  80>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  80>::mutex ); }
template<> void SmallSizeAllocator<  96>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<  96>::mutex ); }
template<> void SmallSizeAllocator< 112>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 112>::mutex ); }
template<> void SmallSizeAllocator< 128>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 128>::mutex ); }
template<> void SmallSizeAllocator< 160>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 160>::mutex ); }
template<> void SmallSizeAllocator< 192>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 192>::mutex ); }
template<> void SmallSizeAllocator< 224>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 224>::mutex ); }
template<> void SmallSizeAllocator< 256>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 256>::mutex ); }
template<> void SmallSizeAllocator< 512>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex< 512>::mutex ); }
template<> void SmallSizeAllocator<1024>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<1024>::mutex ); }
template<> void SmallSizeAllocator<2048>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<2048>::mutex ); }
template<> void SmallSizeAllocator<4096>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<4096>::mutex ); }
template<> void SmallSizeAllocator<6144>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<6144>::mutex ); }
template<> void SmallSizeAllocator<8192>::unlock() { pthread_mutex_unlock( &SmallSizeAllocatorMutex<8192>::mutex ); }
#endif

END_METIL_LEVEL1_NAMESPACE
