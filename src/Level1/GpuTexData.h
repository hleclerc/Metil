#ifndef GPUTEXDATA_H
#define GPUTEXDATA_H

#include "CudaMetil.h"
#include "BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<int dim>
struct GpuTexData {
    cudaArray *data;
    BasicVec<ST,dim> size;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // GPUTEXDATA_H
