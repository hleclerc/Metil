#ifndef MATLAB_H
#define MATLAB_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/local/matlab-7/extern/include
#pragma inc_path /usr/local/matlab-R2008b/extern/include
#endif

#include "BasicVec.h"
#include "String.h"
#include <mex.h>

BEG_METIL_NAMESPACE

extern String matlab_output;

END_METIL_NAMESPACE;

#endif // MATLAB_H
