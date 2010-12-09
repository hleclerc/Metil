#ifndef PREVNEXTPOW2_H
#define PREVNEXTPOW2_H

#include "Config.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<int n,int i,bool ok>
struct GetPrevPow2 {
    enum {
        res = GetPrevPow2<n,i*2,(i*2>n)>::res
    };
};

template<int n,int i>
struct GetPrevPow2<n,i,true> {
    enum {
        res = i / 2
    };
};

END_METIL_LEVEL1_NAMESPACE;

BEG_METIL_NAMESPACE;

/// get the higher 2^i <= n
template<int n>
struct PrevPow2 {
    enum { res = Level1::GetPrevPow2< n, 1, n == 0 >::res };
};

END_METIL_NAMESPACE;

#endif // PREVNEXTPOW2_H
