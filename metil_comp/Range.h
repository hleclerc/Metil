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

#ifndef METIL_RANGE_H
#define METIL_RANGE_H

namespace Metil {

/**

*/
template<class T>
class Range {
public:
    Range( T end = 0 ) : b(0), e(end), s(1) {}
    Range( T beg, T end, T step = 1 ) : b(beg), e(end), s(step) {}
    
    int size() const { return ( e - b ) / s; }
    
    T operator[]( int i ) const { return b + s * i; }
    
    T b, e, s;
};

///
template<class T>
Range<T> range( T end )  { return Range<T>( end ); }

///
template<class T>
Range<T> range( T beg, T end, T step = 1 )  { return Range<T>( beg, end, step ); }


}


#endif // METIL_RANGE_H
