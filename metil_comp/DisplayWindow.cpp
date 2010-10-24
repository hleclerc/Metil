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

#include "DisplayWindow.h"
#include "DisplayObject.h"
#include "DisplayWindowManager.h"

#include <QtGui/QKeyEvent>

namespace Metil {


// -----------------------------------------------------------------------------------------------
DisplayWindow::DisplayWindow( DisplayWindowManager *dwm, const char *name ) : scene( 640, 480 ), dwm( dwm ), name( name ) {
    connect( this, SIGNAL(destroyed()), this, SLOT(remove_from_dwm()) );
    connect( this, SIGNAL(scene_has_changed()), this, SLOT(show()) );
}

DisplayWindow::~DisplayWindow() {
}

void DisplayWindow::remove_from_dwm() {
    dwm->rem_display_windows( name );
}

void DisplayWindow::add_display_object( DisplayObject *dob ) {
    scene << dob;
    coutn << "show " << name;
    emit scene_has_changed();
}

void DisplayWindow::remove_display_object( DisplayObject *display_object ) {
    scene.remove_display_object( display_object );
}

void DisplayWindow::initializeGL() {
    scene.initializeGL();
}

void DisplayWindow::paintGL() {
    coutn << "paintGL " << name;
    scene.paintGL();
}

void DisplayWindow::resizeGL( int width, int height ) {
    scene.resizeGL( width, height );
}

void DisplayWindow::mousePressEvent( QMouseEvent *event ) {
    //lastPos = event->pos();
}

void DisplayWindow::mouseMoveEvent( QMouseEvent *event ) {
//      int dx = event->x() - lastPos.x();
//      int dy = event->y() - lastPos.y();
// 
//      if (event->buttons() & Qt::LeftButton) {
//          setXRotation(xRot + 8 * dy);
//          setYRotation(yRot + 8 * dx);
//      } else if (event->buttons() & Qt::RightButton) {
//          setXRotation(xRot + 8 * dy);
//          setZRotation(zRot + 8 * dx);
//      }
//      lastPos = event->pos();
}

void DisplayWindow::keyPressEvent ( QKeyEvent *event ) {
    if ( event->key() == Qt::Key_Escape )
        emit close();
}

}


