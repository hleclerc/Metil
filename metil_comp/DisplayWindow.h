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

#ifndef METILDISPLAYWINDOW_H
#define METILDISPLAYWINDOW_H

#include "DisplayScene.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file DisplayWindow.cpp
#pragma cpp_path /usr/include/qt4
#pragma lib_name QtOpenGL
#endif

#include <QtOpenGL/QGLWidget>

namespace Metil {

class DisplayWindowManager;

/**
	@author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class DisplayWindow : public QGLWidget {
    Q_OBJECT
public:
    DisplayWindow( DisplayWindowManager *dwm, const char *name );
    
    template<class TD>
    DisplayWindow( const TD &object ) {
        add_display_object( object.new_display_object( &scene ) );
    }
    
    ~DisplayWindow();
    
    /// add correponding DisplayObject
    template<class TD>
    void operator<<( const TD &object ) {
        add_display_object( object.new_display_object( &scene ) );
    }
    
    ///
    void add_display_object( DisplayObject *dob );
    
    /// remove DisplayObject from list of objects to be displayed
    void remove_display_object( DisplayObject *display_object );
    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
    
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void keyPressEvent ( QKeyEvent * event );
    
signals:
    void scene_has_changed();
    
public slots:
    void remove_from_dwm();
private:
    DisplayScene scene;
    DisplayWindowManager *dwm;
    String name;
};

}

#endif
