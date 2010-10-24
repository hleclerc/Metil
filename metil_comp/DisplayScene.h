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

#ifndef METILDISPLAYSCENE_H
#define METILDISPLAYSCENE_H

#include "BasicVec.h"
#include "Mutex.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file DisplayScene.cpp
#endif

namespace Metil {

class DisplayObject;

/**
	@author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class DisplayScene {
public:
    DisplayScene( int width, int height );
    ~DisplayScene();
    
    void operator<<( DisplayObject *dob );
    void remove_display_object( DisplayObject *display_object );

    void update_RC();
    
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );

private:
    int width, height;
    BasicVec<double,3> X, Y, Z, C;
    double R, zoom, perspective, offset_x, offset_y;
    
    Mutex objects_mutex;
    BasicVec<DisplayObject *> objects;
};

}

#endif
