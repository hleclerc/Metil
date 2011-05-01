#ifndef CONJUGATEGRADIENT_H
#define CONJUGATEGRADIENT_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

/**
*/
template<class Precond,class Residual,class Dot,class Conv>
struct ConjugateGradient {
    void exec() {
    }

    Precond precond;
    Residual residual;
    Dot dot;
};

END_METIL_NAMESPACE;

#endif // CONJUGATEGRADIENT_H
