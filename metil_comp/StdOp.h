/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef METIL_STD_OP_H
#define METIL_STD_OP_H

#include "TypePromote.h"
#include "File.h"
#include <cmath>

namespace Metil {

// ------------------------------------ MATH ------------------------------------
#define MIN( a, b ) ( (a) <= (b) ? (a) : (b) )
#define MAX( a, b ) ( (a) >= (b) ? (a) : (b) )

template<class T1,class T2>
typename TypePromote<void,T1,T2>::T min( const T1 &a, const T2 &b ) { return ( a <= b ? a : b ); }

template<class T1,class T2>
typename TypePromote<void,T1,T2>::T max( const T1 &a, const T2 &b ) { return ( a >= b ? a : b ); }

inline int ceil( int a, int m ) { return ( a + m - 1 ) / m * m; }

inline double sqrt ( double a ) { return std::sqrt ( a ); }
inline double log  ( double a ) { return std::log  ( a ); }
inline double floor( double a ) { return std::floor( a ); }
inline double ceil ( double a ) { return std::ceil ( a ); }
//inline double round( double a ) { return std::round( a ); }

template<class T> inline bool is_always_strictly_positive( const T &a ) { return a >  0; }
template<class T> inline bool is_always_positive_or_null ( const T &a ) { return a >= 0; }
template<class T> inline bool is_always_equal_to_one     ( const T &a ) { return a == 1; }
template<class T> inline bool is_always_equal_to_zero    ( const T &a ) { return a == 0; }
template<class T> inline bool is_always_odd              ( const T &a ) { return a %  2; }

template<class T>
inline T abs( const T &a ) { return is_always_positive_or_null( a ) ? a : -a; }

template<class T>
T rsqrt( const T &val ) { return 1.0 / sqrt( val ); }

/// TODO : derecursion
template<class T>
T pow_by_positive_exponent( const T &m, const T &e ) {
    if ( is_always_equal_to_zero( e ) )
        return 1;
    if ( is_always_equal_to_one ( e ) )
        return m;
    if ( is_always_odd( e ) )
        return m * pow_by_positive_exponent( m, e - 1 );
    T tmp = pow_by_positive_exponent( m, e / 2 );
    return tmp * tmp;
}

template<class T>
void swap( T &a, T &b ) {
    T tmp = a;
    a = b;
    b = tmp;
}

// ------------------------------------ OPERATORS ------------------------------------
template<class T> struct PushBack {
    PushBack( T &vec ) : vec( vec ) {}
    template<class T2> void operator()( const T2 &v ) { vec.push_back( v ); }
    T &vec;
};

}


#endif // METIL_STD_OP_H
