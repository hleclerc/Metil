#ifndef TYPEPROMOTE_H
#define TYPEPROMOTE_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

template<class Op,class A,class B>
struct TypePromote;

template<class Op,class A>
struct TypePromote<Op,A,A> {
    typedef A T;
};
template<class Op,class A,class B>
struct TypePromote<Op,A *,B> {
    typedef A T;
};

END_METIL_NAMESPACE;

#endif // TYPEPROMOTE_H
