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

#ifndef METIL_LMAT_H
#define METIL_LMAT_H

#include "LBasicVec.h"
#include "BasicMat.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LMat.cpp
#endif

namespace Metil {

class LMatItem;
class Type;

/**

*/
class LMat {
public:
    struct Zeroes {};

    LMat();
    LMat( Zeroes, Int64 r, Int64 c );

    LMat &operator=( const LMat &l );

    ~LMat();

    Int64 nb_rows() const;
    Int64 nb_cols() const;
    
    BasicVec<const Type *,-1,1> types() const;
    void write_to_stream( Stream &os ) const;

private:
    BasicMat<const LMatItem *,Gen<-1,-1,1> > items;
    BasicVec<Int64> nb_rows_;
    BasicVec<Int64> nb_cols_;
};



}


#endif // METIL_LMAT_H
