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

#ifndef METIL_IMG_H
#define METIL_IMG_H

#include "Val.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Img.cpp
#endif

namespace Metil {

class ImgItem;

/**
  n-dimensionnal image
  can have one or several channels ( ex : RGBA, CMJK, gray, ... )
*/
class Img {
public:
    typedef Float64 Float64Function( int, int );

    Img();
    // Img( const CString &filename );
    Img( Float64Function *f, int w, int h );

    ~Img();

    Val nb_dim() const;

    // void save( const CString &filename ) const;

protected:
    const ImgItem *_data;
};

} // namespace Metil


#endif // METIL_IMG_H
