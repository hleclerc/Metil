#ifndef MATLAB_H
#define MATLAB_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file matlab.cpp
#pragma cpp_path /usr/local/matlab-R2008b/extern/include
#endif

#include "BasicVec.h"
#include <mex.h>

namespace Metil {

extern Stream &matlab_output;

}

#endif // MATLAB_H
