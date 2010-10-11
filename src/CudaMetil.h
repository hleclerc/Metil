#ifndef CUDA_METIL_H
#define CUDA_METIL_H

#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

#include "EnableIf.h"
#include "Ps.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name cudart
#pragma lib_path /usr/local/cuda/lib64
#pragma lib_path /usr/local/cuda/lib
#pragma cpp_path /usr/local/cuda/include
#endif

BEG_METIL_NAMESPACE;

inline void check_err( const char *file, int line, const char *msg ) {
    cudaError_t err = cudaGetLastError();                                   
    if( cudaSuccess != err ) {                                               
        fprintf( stderr, "Cuda error: %s in file '%s' in line %i : %s.\n",   
                msg, file, line, cudaGetErrorString( err) );
        exit( EXIT_FAILURE );                                                  
    }                                                                        
}

#define CHECK_ERR( msg ) check_err( __FILE__, __LINE__, msg );

#define CSC( func ) func; check_err( __FILE__, __LINE__, #func )

/// copy data from str to res ( which must be pre-allocated )
template<class T>
typename T::HasOffPtr memcpy( Ps<T> &dst, const Ps<T> &src ) {
    // dst_id = ;
    cudaMemcpyKind mc[] = { cudaMemcpyHostToHost, cudaMemcpyHostToDevice, cudaMemcpyDeviceToHost, cudaMemcpyDeviceToDevice };
    cudaMemcpy( dst.data, src.data, src.rese, mc[ 2 * src.pos.is_a_gpu() + dst.pos.is_a_gpu() ] );
    if ( dst.pos.is_a_cpu() )
        dst->update_ptr_cpu( (const char *)dst.data - (const char *)src.data );
    else
        dst->update_ptr_gpu( (const char *)dst.data - (const char *)src.data );
}

/// make a new copy of data from str
template<class T>
Ps<T> strdup( const Ps<T> &src, MachineId dst_id ) {
    Ps<T> dst( 0, src.size, src.rese, dst_id );
    if ( dst_id.is_a_cpu() )
        dst.data = (T *)MALLOC( dst.rese );
    else
        cudaMalloc( &dst.data, dst.rese );
    memcpy( dst, src );
    return dst;
}


END_METIL_NAMESPACE;

#endif // CUDA_METIL_H
