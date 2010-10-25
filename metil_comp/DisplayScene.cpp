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

#include "DisplayScene.h"
#include "DisplayObject.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma cpp_path /usr/include/qt4
#endif

#include <limits>
#include <QtOpenGL/QGLWidget>

namespace Metil {

DisplayScene::DisplayScene( int width, int height ) : width( width ), height( height ) {
    X = BasicVec<double,3>(1.0,0.0,0.0);
    Y = BasicVec<double,3>(0.0,1.0,0.0);
    Z = BasicVec<double,3>(0.0,0.0,1.0);
    R = -1.0;
    C = BasicVec<double,3>(0.0,0.0,0.0);
    zoom = 1.0;
    perspective = 0.2;
    offset_x = 0.0;
    offset_y = 0.0;
}

DisplayScene::~DisplayScene() {
    for(int i=0;i<objects.size();++i)
        delete objects[ i ];
}

void DisplayScene::operator<<( DisplayObject *dob ) {
    objects_mutex.acquire();
    objects << dob;
    coutn << "add";
    objects_mutex.release();
}

void DisplayScene::remove_display_object( DisplayObject *display_object ) {
    objects_mutex.acquire();
    objects.remove_first_unordered( display_object );
    objects_mutex.release();
}

void DisplayScene::update_RC() {
    BasicVec<Vec<double,3> > axes;
    axes.push_back( 1, 0, 0 );
    axes.push_back( 0, 1, 0 );
    axes.push_back( 0, 0, 1 );
    //
    BasicVec<double> mi( SetSize(), axes.size(), +std::numeric_limits<double>::max() );
    BasicVec<double> ma( SetSize(), axes.size(), -std::numeric_limits<double>::max() );
    //
    PRINT( objects.size() );
    objects_mutex.acquire();
    for(int i=0;i<objects.size();++i)
        objects[ i ]->update_borders( axes, mi, ma );
    objects_mutex.release();
    PRINT( mi );
    PRINT( ma );
    
    R = 1;
}

void DisplayScene::initializeGL() {
//     glShadeModel(GL_FLAT);
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_CULL_FACE);
}

void DisplayScene::paintGL() {
    if ( R < 0 )
        update_RC();
        
    //
    glClear( /*GL_COLOR_BUFFER_BIT | */GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    
    //
    glBegin(GL_QUADS);
        glColor3f( 0, 0, 0.3 );
        glVertex3f( -1, -1, 0 );
        glVertex3f( +1, -1, 0 );
        glColor3f( 0, 0, 0 );
        glVertex3f( +1, +1, 0 );
        glVertex3f( -1, +1, 0 );
    glEnd();

}

void DisplayScene::resizeGL( int width, int height ) {
    int side = min( width, height );
//     glViewport((width - side) / 2, (height - side) / 2, side, side);
// 
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
//     glMatrixMode(GL_MODELVIEW);
}

}

