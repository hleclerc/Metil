#ifndef MEMORYDRIVER_H
#define MEMORYDRIVER_H

#include "Level1/StringHelp.h"
#include "Malloc.h"
#include "Math.h"
#include "Ps.h"

BEG_METIL_NAMESPACE;

///
class MemoryDriver {
public:
    NEW_AND_DEL_COMPATIBLE_PURE_VIRTUAL;
    virtual void init( ST &size ) = 0;
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
    NEW_AND_DEL_COMPATIBLE;
    virtual void init( ST &size );
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );
    ST *off;
};

///
class MemoryDriver_Cpu : public MemoryDriver {
public:
    NEW_AND_DEL_COMPATIBLE;
    virtual void init( ST &size );
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );
    static MachineId machine_id() { return MachineId::cpu( 0 ); }

    char *res;
    ST off;
};

///
class MemoryDriver_Gpu : public MemoryDriver {
public:
    NEW_AND_DEL_COMPATIBLE;
    virtual void init( ST &size );
    virtual void beg_local_data( void **dst, void **loc, ST &size, ST alig );
    virtual void end_local_data( void *dst, void *loc, ST size );
    virtual void copy( void **dst, const void *src, ST size, ST alig );
    static MachineId machine_id() { return MachineId::gpu( 0 ); }

    char *res;
    ST off;
};

template<class T>
struct CopyCs {
    CopyCs( const T *str, ST num ) : str( str ), num( num ) {}
    ~CopyCs() { DEL( cpy_driver ); }

    template<class C>
    operator Ps<C>() const {
        MemoryDriver_Dry ld;
        ST len = 0;
        ld.init( len );
        C::copy( ld, str, num );

        cpy_driver->init( *ld.off );
        return Ps<C>( C::copy( *cpy_driver, str, num ), num, *ld.off, machine );
    }

    MachineId machine;
    MemoryDriver *cpy_driver;
    const T *str;
    ST num;
};

template<class T>
CopyCs<T> make_cs( const T *str, ST num, MachineId machine ) {
    CopyCs<T> res( str, num );
    res.machine = machine;
    if ( machine.is_a_gpu() )
        res.cpy_driver = NEW( MemoryDriver_Gpu );
    else
        res.cpy_driver = NEW( MemoryDriver_Cpu );
    return res;
}


END_METIL_NAMESPACE;

#endif // MEMORYDRIVER_H
