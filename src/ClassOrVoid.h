#ifndef CLASSORVOID_H
#define CLASSORVOID_H

#include "Config.h"

BEG_METIL_NAMESPACE;

template<class T,bool want_class>
struct ClassOrVoid : public T {
};

template<class T>
struct ClassOrVoid<T,false> {
};

END_METIL_NAMESPACE;

#endif // CLASSORVOID_H
