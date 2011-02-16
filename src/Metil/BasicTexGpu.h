#ifndef BASICTEXGPU_H
#define BASICTEXGPU_H

#include "CudaMetil.h"

BEG_METIL_NAMESPACE;

template<class T>
struct BasicTexGpu {

    cudaArray *data;
};

END_METIL_NAMESPACE;

#endif // BASICTEXGPU_H
