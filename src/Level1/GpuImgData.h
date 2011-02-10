#ifndef GPUIMGDATA_H
#define GPUIMGDATA_H

#include "Owcp.h"
#include "../BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<int dim>
struct GpuImgData {
    void *data;
    BasicVec<ST,dim> size;
};


END_METIL_LEVEL1_NAMESPACE;

#endif // GPUIMGDATA_H
