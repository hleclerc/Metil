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
typename T::HasOffPtr memcpy( Ps<T> &res, const Ps<T> &str, cudaMemcpyKind memcpy_kind ) {
    cudaMemcpy( &res.data, str.data, str.rese, memcpy_kind );
}

/// make a new copy of data from str
template<class T>
Ps<T> strdup( const Ps<T> &str, cudaMemcpyKind memcpy_kind ) {
    Ps<T> res( 0, str.size, str.rese );
    cudaMalloc( &res.data, str.rese );
    memcpy( res, str, memcpy_kind );
    return res;
}


END_METIL_NAMESPACE;

#endif // CUDA_METIL_H
