#include "MemoryDriver.h"
#include "CudaMetil.h"

BEG_METIL_NAMESPACE;

// MemoryDriver_Dry
MemoryDriver_Dry::MemoryDriver_Dry() : off( 0 ) {
}

void MemoryDriver_Dry::MemoryDriver_Dry::beg_local_data( void **dst, void **loc, ST &size, ST alig ) {
    off = ceil( off, alig );
    *dst = (void *)off;
    *loc = MALLOC( size );
    off += size;
}

void MemoryDriver_Dry::end_local_data( void *dst, void *loc, ST size ) {
    FREE( loc, size );
}

void MemoryDriver_Dry::copy( void **dst, const void *src, ST size, ST alig ) {
    *dst = (void *)off;
    off = ceil( off, alig ) + size;
}


// MemoryDriver_Cpu
MemoryDriver_Cpu::MemoryDriver_Cpu( ST &size ) {
    res = (char *)MALLOC( size );
    off = 0;
}

void MemoryDriver_Cpu::beg_local_data( void **dst, void **loc, ST &size, ST alig ) {
    off = ceil( off, alig );
    *dst = res + off;
    *loc = *dst;
    off += size;
}

void MemoryDriver_Cpu::end_local_data( void *dst, void *loc, ST size ) {
}

void MemoryDriver_Cpu::copy( void **dst, const void *src, ST size, ST alig ) {
    off = ceil( off, alig );
    *dst = res + off;
    Level1::memcpy( *dst, src, size );
    off += size;
}

// MemoryDriver_Gpu
MemoryDriver_Gpu::MemoryDriver_Gpu( ST &size ) {
    cudaMalloc( &res, size );
    off = 0;
}

void MemoryDriver_Gpu::beg_local_data( void **dst, void **loc, ST &size, ST alig ) {
    off = ceil( off, alig );
    *dst = res + off;
    *loc = MALLOC( size );
    off += size;
}

void MemoryDriver_Gpu::end_local_data( void *dst, void *loc, ST size ) {
    cudaMemcpy( dst, loc, size, cudaMemcpyHostToDevice );
    FREE( loc, size );
}

void MemoryDriver_Gpu::copy( void **dst, const void *src, ST size, ST alig ) {
    off = ceil( off, alig );
    *dst = res + off;
    cudaMemcpy( *dst, src, size, cudaMemcpyHostToDevice );
    off += size;
}


END_METIL_NAMESPACE;
