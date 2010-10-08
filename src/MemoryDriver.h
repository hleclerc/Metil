#ifndef MEMORYDRIVER_H
#define MEMORYDRIVER_H

#include "StringHelp.h"
#include "Malloc.h"
#include "Math.h"
#include "Ps.h"

BEG_METIL_NAMESPACE;

///
class MemoryDriver {
public:
    template<class T,class MemoryDriver_Len,class MemoryDriver_Cpy>
    struct CopyCs {
        CopyCs( const T *str, ST n ) : str( str ), n( n ) {}

        template<class C>
        operator Ps<C>() const {
            MemoryDriver_Len md;
            C::copy( md, str, n );

            MemoryDriver_Cpy mc( md.off );
            return Ps<C>( C::copy( mc, str, n ), n, md.off );
        }

        const T *str;
        ST n;
    };

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
    MemoryDriver_Dry();
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );
    ST off;
};

///
class MemoryDriver_Cpu : public MemoryDriver {
public:
    MemoryDriver_Cpu( ST &size );
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );

    template<class T>
    static CopyCs<T,MemoryDriver_Dry,MemoryDriver_Cpu> copy_cs( const T *str, ST n = 1 ) {
        return CopyCs<T,MemoryDriver_Dry,MemoryDriver_Cpu>( str, n );
    }

    char *res;
    ST off;
};

///
class MemoryDriver_Gpu : public MemoryDriver {
public:
    MemoryDriver_Gpu( ST &size );
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );

    template<class T>
    static CopyCs<T,MemoryDriver_Dry,MemoryDriver_Gpu> copy_cs( const T *str, ST n = 1 ) {
        return CopyCs<T,MemoryDriver_Dry,MemoryDriver_Gpu>( str, n );
    }

    char *res;
    ST off;
};

END_METIL_NAMESPACE;

#endif // MEMORYDRIVER_H
