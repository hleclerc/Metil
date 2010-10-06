#ifndef MEMORYDRIVER_H
#define MEMORYDRIVER_H

#include "StringHelp.h"
#include "Malloc.h"
#include "Math.h"

BEG_METIL_NAMESPACE;

///
class MemoryDriver {
public:
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig ) = 0; ///< make room in local and target memory
    virtual void end_local_data( void * dst, void * loc, ST size ) = 0; ///< save local memory
    virtual void copy( void **dst, const void *src, ST size, ST alig ) = 0; ///< copy src in memory. put position in dst

    template<class T>
    void copy( T **dst, const void *src, ST size, ST alig ) { copy( (void **)dst, src, size, alig ); }

    template<class T1,class T2>
    void beg_local_data( T1 **dst, T2 **loc, ST &size, ST alig ) { beg_local_data( (void **)dst, (void **)loc, size, alig ); }
};

///
class MemoryDriver_Dry : public MemoryDriver {
public:
    MemoryDriver_Dry() : off( 0 ) {}
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig ) {
        off = ceil( off, alig ) + size;
        *dst = (void *)off;
        *loc = MALLOC( size );
    }
    virtual void end_local_data( void *dst, void *loc, ST size ) {
        FREE( loc, size );
    }
    virtual void copy( void **dst, const void *src, ST size, ST alig ) {
        *dst = (void *)off;
        off = ceil( off, alig ) + size;
    }
    ST off;
};

///
class MemoryDriver_Cpu : public MemoryDriver {
public:
    MemoryDriver_Cpu( ST &size ) {
        res = (char *)MALLOC( size );
        off = 0;
    }

    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig ) {
        off = ceil( off, alig );
        *dst = res + off;
        *loc = *dst;
        off += size;
    }
    virtual void end_local_data( void *dst, void *loc, ST size ) {
    }
    virtual void copy( void **dst, const void *src, ST size, ST alig ) {
        off = ceil( off, alig );
        *dst = res + off;
        Level1::memcpy( *dst, src, size );
        off += size;
    }

    char *res;
    ST off;
};

END_METIL_NAMESPACE;

#endif // MEMORYDRIVER_H
