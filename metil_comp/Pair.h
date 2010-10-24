#ifndef PAIR_H
#define PAIR_H

namespace Metil {

/**
*/
template<class T0,class T1>
struct Pair {
    Pair() {}
    template<class P0,class P1>
    Pair( const P0 &a, const P1 &b ) : a( a ), b( b ) {}

    T0 a;
    T1 b;
};


}

#endif // PAIR_H
