#ifndef CUDA_METIL_H
#define CUDA_METIL_H

#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

#include "TypeConfig.h"

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

END_METIL_NAMESPACE;

#endif // CUDA_METIL_H
