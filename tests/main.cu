#include <String.h>
#include <BasicVecGpu.h>
#include <CudaAccumulation.h>
using namespace Metil;

int main() {
    BasicVec<int> c;
    for( int i = 0; i < 32; ++i )
        c << 1;
    BasicVecGpu<int> g( c );
    PRINT( g.size() );
    cuda_accumulation( g.ptr(), g.size() );
    PRINT( g );
}
