#ifndef PREVNEXTPOW2_H
#define PREVNEXTPOW2_H

#include "Config.h"

BEG_METIL_LEVEL1_NAMESPACE;

template<int n,int i,bool ok>
struct GetPrevPow2 {
    enum { res = GetPrevPow2<n,i*2,(i*2>n)>::res };
};

template<int n,int i>
struct GetPrevPow2<n,i,true> {
    enum { res = i / 2 };
};

template<int n,int i,bool ok>
struct GetNextPow2 {
    enum { res = GetNextPow2<n,i*2,(i*2>=n)>::res };
};

template<int n,int i>
struct GetNextPow2<n,i,true> {
    enum { res = i };
};

END_METIL_LEVEL1_NAMESPACE;

BEG_METIL_NAMESPACE;

/// get the highest 2^i <= n
template<int n>
struct PrevPow2 {
    enum { res = Level1::GetPrevPow2< n, 1, n == 0 >::res };
};

/// get the lowest 2^i >= n
template<int n>
struct NextPow2 {
    enum { res = Level1::GetNextPow2< n, 1, n <= 1 >::res };
};

END_METIL_NAMESPACE;

#endif // PREVNEXTPOW2_H
