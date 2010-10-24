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

#ifndef METIL_TYPE_PROMOTE_H
#define METIL_TYPE_PROMOTE_H

#include "TypeConfig.h"

namespace Metil {

template<class Op,class T1,class T2=void,class T3=void>
struct TypePromote;

template<class Op,class T1>
struct TypePromote<Op,T1,T1> {
    typedef T1 T;
};

template<class Op> struct TypePromote<Op,Int32,Int64> { typedef Int64 T; };
template<class Op> struct TypePromote<Op,Int64,Int32> { typedef Int64 T; };

template<class Op> struct TypePromote<Op,int,double> { typedef double T; };
template<class Op> struct TypePromote<Op,double,int> { typedef double T; };

template<class Op> struct TypePromote<Op,int,float> { typedef float T; };
template<class Op> struct TypePromote<Op,float,int> { typedef float T; };

} // namespace Metil

#endif // METIL_TYPE_PROMOTE_H
