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

#include "LBasicMat.h"
#include "LMatItem.h"
#include "VecMath.h"

namespace Metil {

LMat::LMat() {}

LMat::LMat( Zeroes, Int64 r, Int64 c ) {
    items.resize( 1, 1 );
    items( 0, 0 ) = new LMatItemCst<Float64>( r, c, 0.0 );
    nb_rows_ << r;
    nb_cols_ << c;
}

LMat &LMat::operator=( const LMat &l ) {
    for(int i=0;i<items.nb_rows();++i)
        for(int j=0;j<items.nb_cols();++j)
            if ( l.items( i, j ) )
                inc_ref( l.items( i, j ) );
    for(int i=0;i<items.nb_rows();++i)
        for(int j=0;j<items.nb_cols();++j)
            if ( l.items( i, j ) )
                dec_ref( items( i, j ) );
    items = l.items;
    return *this;
}

LMat::~LMat() {
    for(int i=0;i<items.nb_rows();++i)
        for(int j=0;j<items.nb_cols();++j)
            if ( items( i, j ) )
                dec_ref( items( i, j ) );
}

Int64 LMat::nb_rows() const { return sum( nb_rows_ ); }
Int64 LMat::nb_cols() const { return sum( nb_cols_ ); }

Vec<const Type *,-1,1> LMat::types() const {
    BasicVec<const Type *,-1,1> res;
    for(int i=0;i<items.nb_rows();++i)
        for(int j=0;j<items.nb_cols();++j)
            if ( items( i, j ) )
                res.push_back_unique( items( i, j )->type() );
    return res;
}

void LMat::write_to_stream( Stream &os ) const {
    LStream ls( &os );
    for(int r=0;r<items.nb_rows();++r)
        for(int c=0;c<items.nb_cols();++c)
            if ( items( r, c ) )
                ls.append( items( r, c ) );
}


}


