#ifndef TYPECHOICE_H
#define TYPECHOICE_H

#include "Config.h"

BEG_METIL_NAMESPACE;

template<int n,class T0,class T1=void,class T2=void>
struct TypeChoice;

template<class T0,class T1,class T2>
struct TypeChoice<0,T0,T1,T2> {
    typedef T0 T;
};

template<class T0,class T1,class T2>
struct TypeChoice<1,T0,T1,T2> {
    typedef T1 T;
};

template<class T0,class T1,class T2>
struct TypeChoice<2,T0,T1,T2> {
    typedef T1 T;
};

END_METIL_NAMESPACE;

#endif // TYPECHOICE_H
