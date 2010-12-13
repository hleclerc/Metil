#include <CudaAccumulation.h>
#include <BasicVecGpu.h>
using namespace Metil;

int main() {
    BasicVec<float> c;
    for( int i = 0; i < 10; ++i )
        c << 1;
    BasicVecGpu<float> g( c );
    cuda_accumulation( g.ptr(), g.size() );
    PRINT( g );
}
