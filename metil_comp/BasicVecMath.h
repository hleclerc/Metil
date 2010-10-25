#ifndef VECMATH_H
#define VECMATH_H

#include "BasicVec.h"

namespace Metil {

/**
    \code
        tokenize(String("toto:tata:1"),':') returns ["toto","tata","1"]. Sep must be a ScalarType<T2>
    \relates Vec
*/
template<class T2,class T3> BasicVec<T2> tokenize( T2 t, const T3 &sep ) {
    BasicVec<T2> res;
    int deb = 0;
    for(int i=0;i<t.size();++i) {
        if ( t[i] == sep ) {
            if ( i )
                res << T2( &t[deb], &t[i] );
            deb = i + 1;
        }
    }
    if ( deb < t.size() )
        res << T2( &t[deb], &t[t.size()] );
    return res;
}

///
template<class T,int s,int p>
T product( const BasicVec<T,s,p> &v ) {
    if ( not v.size() )
        return 1;
    T res = v[0];
    for(int i=1;i<v.size();++i)
        res *= v[i];
    return res;
}

/// sum
template<class T,int s,int p>
T sum( const BasicVec<T,s,p> &v ) {
    if ( not v.size() )
        return 0;
    T res = v[0];
    for(int i=1;i<v.size();++i)
        res += v[i];
    return res;
}

///
template<class T,int s,int p>
T norm_2( const BasicVec<T,s,p> &v ) {
    if ( not v.size() )
        return 1;
    T res = v[0] * v[0];
    for(int i=1;i<v.size();++i)
        res *= v[i] * v[i];
    return sqrt( res );
}

/// v + v
template<class T1,int s1,int p1,class T2,int s2,int p2>
BasicVec<typename TypePromote<void,T1,T2>::T,MAX(s1,s2),MAX(p1,p2)> operator+( const BasicVec<T1,s1,p1> &a, const BasicVec<T2,s2,p2> &b ) {
    ASSERT_IF_DEBUG( a.size() == b.size() );
    BasicVec<typename TypePromote<void,T1,T2>::T,MAX(s1,s2),MAX(p1,p2)> res( SetSize(), a.size() );
    for(int i=0;i<a.size();++i)
        res[ i ] = a[ i ] + b[ i ];
    return res;
}

/// v - v
template<class T1,int s1,int p1,class T2,int s2,int p2>
BasicVec<typename TypePromote<void,T1,T2>::T,MAX(s1,s2),MAX(p1,p2)> operator-( const BasicVec<T1,s1,p1> &a, const BasicVec<T2,s2,p2> &b ) {
    ASSERT_IF_DEBUG( a.size() == b.size() );
    BasicVec<typename TypePromote<void,T1,T2>::T,MAX(s1,s2),MAX(p1,p2)> res( SetSize(), a.size() );
    for(int i=0;i<a.size();++i)
        res[ i ] = a[ i ] - b[ i ];
    return res;
}

/// v - s
template<class T1,int s1,int p1,class T2>
BasicVec<typename TypePromote<void,T1,T2>::T,s1,p1> operator-( const BasicVec<T1,s1,p1> &a, const T2 &b ) {
    BasicVec<typename TypePromote<void,T1,T2>::T,s1,p1> res( SetSize(), a.size() );
    for(int i=0;i<a.size();++i)
        res[ i ] = a[ i ] - b;
    return res;
}


/// s * v
template<class T1,class T2,int s2,int p2>
BasicVec<typename TypePromote<void,T1,T2>::T,s2,p2> operator*( const T1 &a, const BasicVec<T2,s2,p2> &b ) {
    BasicVec<typename TypePromote<void,T1,T2>::T,s2,p2> res( SetSize(), b.size() );
    for(int i=0;i<b.size();++i)
        res[ i ] = a * b[ i ];
    return res;
}


/// v += v
template<class T1,int s1,int p1,class T2,int s2,int p2>
BasicVec<T1,s1,p1> &operator+=( BasicVec<T1,s1,p1> &a, const BasicVec<T2,s2,p2> &b ) {
    for(int i=0;i<a.size();++i)
        a[ i ] += b[ i ];
    return a;
}

/// dot
template<class T1,int s1,int p1,class T2,int s2,int p2>
typename TypePromote<void,T1,T2>::T dot( const BasicVec<T1,s1,p1> &a, const BasicVec<T2,s2,p2> &b ) {
    if ( not a.size() )
        return 0;
    typename TypePromote<void,T1,T2>::T res = a[ 0 ] * b[ 0 ];
    for(int i=1;i<a.size();++i)
        res += a[ i ] * b[ i ];
    return res;
}

// abs
template<class T1,int s1,int p1>
BasicVec<T1,s1,p1> abs( const BasicVec<T1,s1,p1> &a ) {
    BasicVec<T1,s1,p1> res;
    for(int i=0;i<a.size();++i)
        res[ i ] = abs( a[ i ] );
    return res;
}

// ----------------------------------------------------------------------------------------------------------------
namespace OpNs {
    struct Inf   { template<class T1,class T2> bool operator()( const T1 &a, const T2 &b ) const { return a <  b; } };
    struct InfEq { template<class T1,class T2> bool operator()( const T1 &a, const T2 &b ) const { return a <= b; } };
    struct Sup   { template<class T1,class T2> bool operator()( const T1 &a, const T2 &b ) const { return a >  b; } };
    struct SupEq { template<class T1,class T2> bool operator()( const T1 &a, const T2 &b ) const { return a >= b; } };

    template<class TV1,class TV2,class OpNs>
    struct VecCmp {
        VecCmp( const TV1 &a, const TV2 &b ) : a( a ), b( b ) {}
        int size() const { return a.size(); }
        bool operator[]( int i ) const { return op( a[i], b[i] ); }

        const TV1 &a;
        const TV2 &b;
        OpNs op;
    };

    template<class TV1,class TV2,class OpNs>
    struct VecCmpScal {
        VecCmpScal( const TV1 &a, const TV2 &b ) : a( a ), b( b ) {}
        int size() const { return a.size(); }
        bool operator[]( int i ) const { return op( a[i], b ); }

        const TV1 &a;
        const TV2 &b;
        OpNs op;
    };
}


/// example : all( v > 10 ) returns true if all components of a are > 10
template<class TV>
bool all( const TV &v ) {
    for(int i=0;i<v.size();++i)
        if ( not v[ i ] )
            return false;
    return true;
}

/// example : all( v > 10 ) returns true if at least one component of a is > 10
template<class TV>
bool any( const TV &v ) {
    for(int i=0;i<v.size();++i)
        if ( v[ i ] )
            return true;
    return false;
}

template<class T1,int s1,int p1,class T2,int s2,int p2> OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::Inf  > operator< (const BasicVec<T1,s1,p1> &a,const BasicVec<T2,s2,p2> &b){return OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::Inf  >(a,b);}
template<class T1,int s1,int p1,class T2,int s2,int p2> OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::Sup  > operator> (const BasicVec<T1,s1,p1> &a,const BasicVec<T2,s2,p2> &b){return OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::Sup  >(a,b);}
template<class T1,int s1,int p1,class T2,int s2,int p2> OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::InfEq> operator>=(const BasicVec<T1,s1,p1> &a,const BasicVec<T2,s2,p2> &b){return OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::InfEq>(a,b);}
template<class T1,int s1,int p1,class T2,int s2,int p2> OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::SupEq> operator>=(const BasicVec<T1,s1,p1> &a,const BasicVec<T2,s2,p2> &b){return OpNs::VecCmp<BasicVec<T1,s1,p1>,BasicVec<T2,s2,p2>,OpNs::SupEq>(a,b);}

// v cmp s
template<class T1,int s1,int p1,class T2> OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::Inf  > operator< (const BasicVec<T1,s1,p1> &a,const T2 &b) { return OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::Inf  >( a, b ); }
template<class T1,int s1,int p1,class T2> OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::Sup  > operator> (const BasicVec<T1,s1,p1> &a,const T2 &b) { return OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::Sup  >( a, b ); }
template<class T1,int s1,int p1,class T2> OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::InfEq> operator>=(const BasicVec<T1,s1,p1> &a,const T2 &b) { return OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::InfEq>( a, b ); }
template<class T1,int s1,int p1,class T2> OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::SupEq> operator>=(const BasicVec<T1,s1,p1> &a,const T2 &b) { return OpNs::VecCmpScal<BasicVec<T1,s1,p1>,T2,OpNs::SupEq>( a, b ); }


}

#endif // VECMATH_H
