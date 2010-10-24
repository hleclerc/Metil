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

#include "DisplayObject.h"
#include "DisplayScene.h"
    
namespace Metil {

DisplayObject::DisplayObject( const DisplayableObject *dob, DisplayScene *display_scene ) : displayable_object( dob ), display_scene( display_scene ) {
}

DisplayObject::~DisplayObject() {
    displayable_object->attached_display_objects.remove_first_unordered( this );
    display_scene->remove_display_object( this );
}


DisplayableObject::~DisplayableObject() {
    for(int i=0;i<attached_display_objects.size();++i)
        delete attached_display_objects[ i ];
}

DisplayObject *DisplayableObject::attach_display_object( DisplayObject *obj ) const {
    attached_display_objects << obj;
    return obj;
}

}
