#ifndef CUDAARRAY_H
#define CUDAARRAY_H

#include "BasicVec.h"
#include "CudaMetil.h"

BEG_METIL_NAMESPACE;

/*
  interface to cuda arrays, used for textures

*/
template<int dim>
struct CudaArray {
    typedef int I;
    typedef cudaArray A;

    BasicVec<I> size; ///< real size
    A *gpu_array;
};


END_METIL_NAMESPACE;

#endif // CUDAARRAY_H
