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

#ifndef METIL_GEOMETRIC_SUPPORT_H
#define METIL_GEOMETRIC_SUPPORT_H

#include "GeomItem.h"
#include "ElementType.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Geom.cpp
#endif

namespace Metil {

/**
*/
class MakeRect {};

/**

*/
class Geom {
public:
    Geom( MakeRect, const ElementType *element_type, const BasicVec<double> &diag_0, const BasicVec<double> &diag_1, const BasicVec<int> &nb_div );

private:
    const GeomItem *item;
};


}

#endif // METIL_GEOMETRIC_SUPPORT_H
