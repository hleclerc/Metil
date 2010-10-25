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

#include "ImgItemGridFromImgItem.h"
#include "ImgWriter.h"
#include "Type.h"

namespace Metil {

int ImgItem::nb_lines() const {
    int res = 1;
    for(int i=1;i<nb_dim();++i)
        res *= size( i );
    return res;
}

const ImgItemGrid *ImgItem::as_grid_of_type( const Type *type ) const {
#warning obj_or_sibling
    return new ImgItemGridFromImgItem( type, this );
}

const LazyObject *ImgItem::save( const CString &filename ) const {
    return new_ImgWriter( filename, this );
}


} // namespace Metil


