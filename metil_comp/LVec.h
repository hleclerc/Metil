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

#ifndef METIL_LVEC_H
#define METIL_LVEC_H

#include "LStream.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LVec.cpp
#endif

namespace Metil {

class LVecItem;
class Type;
class ValItemeration;

/**

*/
class LVec {
public:
    typedef long S;
    
    LVec();
    LVec( const LVec &l );

    LVec &operator=( const LVec &l );

    ~LVec();

    LVec( const Range<Int32> &range );
    LVec( const Range<Int64> &range );
    LVec( const Range<Float32> &range );
    LVec( const Range<Float64> &range );

//    template<class T>
//    void get_values( BasicVec<T> &vec ) {
//        vec.resize( size() );
//        get_values( type_ptr( StructForType<T>() ), vec.ptr() );
//    }
    
//    void get_values( const Type *type, void *data ) const;
    
    S size() const;

    BasicVec<const Type *,-1,1> types() const;
    
    void write_to_stream( Stream &os ) const;

//    LVec operator+( const LVec &v ) const;

//    friend LVec abs( const LVec &v );
private:
//    static LVec binary_op( ValItemeration *op, const LVec &a, const LVec &b );
    
    BasicVec<const LVecItem *,-1,1> items;
};



}


#endif // METIL_LVEC_H
