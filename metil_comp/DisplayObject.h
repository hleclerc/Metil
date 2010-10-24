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

#ifndef METILDISPLAYOBJECT_H
#define METILDISPLAYOBJECT_H

#include "DisplayWindowManager.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file DisplayObject.cpp
#endif

namespace Metil {

class DisplayableObject;
class DisplayScene;

/**

*/
class DisplayObject {
public:
    DisplayObject( const DisplayableObject *dob, DisplayScene *display_scene );
    virtual ~DisplayObject();
    
    virtual void update_borders( const BasicVec<Vec<double,3> > &axes, BasicVec<double> &mi, BasicVec<double> &ma ) = 0;

private:
    const DisplayableObject *displayable_object;
    DisplayScene *display_scene;
};

/**

*/
class DisplayableObject {
public:
    virtual ~DisplayableObject();
    
    DisplayObject *attach_display_object( DisplayObject *obj ) const;
    
    friend class DisplayObject;
private:
    mutable BasicVec<DisplayObject *> attached_display_objects;
};

}

#endif
