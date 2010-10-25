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

#ifndef METILDISPLAYOBJECTIMAGE_H
#define METILDISPLAYOBJECTIMAGE_H

#include "DisplayObject.h"
#include "Type.h"
#include "BasicVec.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file DisplayObjectImage.cpp
#endif

namespace Metil {

/**
    @author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class DisplayObjectImage : public DisplayObject {
public:
    DisplayObjectImage( const DisplayableObject *dob, DisplayScene *dsc, BasicVec<int> size, const void *data, const Type *type );
    virtual ~DisplayObjectImage();
    
    virtual void update_borders( const BasicVec<Vec<double,3> > &axes, BasicVec<double> &mi, BasicVec<double> &ma );
    
private:
    BasicVec<int> _size;
    const void *_data;
    const Type *_type;
};

}

#endif
