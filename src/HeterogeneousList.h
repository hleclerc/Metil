#ifndef HETEROGENEOUSLIST_H
#define HETEROGENEOUSLIST_H

#include "Number.h"

BEG_METIL_NAMESPACE;

template<class T0,class T1=void,class T2=void,class T3=void>
struct HeterogeneousList {
    template<int n,int d=0> struct SubType { typedef void T; };
    template<int d> struct SubType<0,d> { typedef T0 T; };
    template<int d> struct SubType<1,d> { typedef T1 T; };
    template<int d> struct SubType<2,d> { typedef T2 T; };
    template<int d> struct SubType<3,d> { typedef T3 T; };
};

template<class TL>
struct NbSubType {
    template<class ST,int sol>
    struct GetNbSubType {
        enum { res = GetNbSubType<typename TL::template SubType<sol+1>::T,sol+1>::res };
    };
    template<int sol>
    struct GetNbSubType<void,sol> {
        enum { res = sol };
    };

    enum { res = GetNbSubType<typename TL::template SubType<0>::T,0>::res };
};


template<class TL,class TM>
struct HeterogeneousMapType {
    enum { nb_sub_types = NbSubType<TL>::res };

    template<int n>
    struct SubType {
        typedef typename TL::template SubType<n>::T R;
        typedef typename TM::template SubType<R>::T T;
    };

    template<int n,int d>
    struct DataType : public DataType<n+1,d> {
        typedef typename SubType<n>::T T;

        const T &get_data( N<n> ) const { return data; }
        T &get_data( N<n> ) { return data; }

        T data;
    };
    template<int d>
    struct DataType<d,d> {
    };

    template<int n>
    typename SubType<n>::T &get_data( N<n> c ) { return data.get_data( c ); }

    template<int n>
    const typename SubType<n>::T &get_data( N<n> c ) const { return data.get_data( c ); }

    DataType<0,nb_sub_types> data;
};

END_METIL_NAMESPACE;

#endif // HETEROGENEOUSLIST_H
