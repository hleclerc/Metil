#ifndef CONFIG_H
#define CONFIG_H

#define METIL_BOOSTRAP
#define USE_STD_ALLOC

// Doxygen stuff
#ifndef DOXYGEN
    #define WANT_METIL_NAMESPACE
#endif

// xxx_METIL_NAMESPACE
#ifdef WANT_METIL_NAMESPACE
    #define BEG_METIL_NAMESPACE namespace Metil {
    #define END_METIL_NAMESPACE }
#else
    #define BEG_METIL_NAMESPACE
    #define END_METIL_NAMESPACE
    namespace Metil {
        namespace Level1 {
        }
    }
#endif

// xxx_METIL_LEVEL1_NAMESPACE
#define BEG_METIL_LEVEL1_NAMESPACE BEG_METIL_NAMESPACE namespace Level1 {
#define END_METIL_LEVEL1_NAMESPACE END_METIL_NAMESPACE }


// cuda
#ifdef __CUDACC__
    #define __inline__ __device__ __host__ inline
#else
    //     struct MyDim { int x, y, z; };
    //     extern MyDim my_dim;
    //     #define threadIdx my_dim
    //     #define blockIdx my_dim
    //     #define blockDim my_dim
    #define __inline__ inline
#endif // __CUDACC__

#endif // CONFIG_H
