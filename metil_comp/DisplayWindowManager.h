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

#ifndef METILDISPLAYWINDOWMANAGER_H
#define METILDISPLAYWINDOWMANAGER_H

#include "DisplayWindow.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma cpp_path /usr/include/qt4
#pragma lib_name QtGui
#pragma src_file DisplayWindowManager.cpp
#endif

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

namespace Metil {

class DisplayWindowManager : public QObject {
    Q_OBJECT
public:
    DisplayWindowManager();
    
    DisplayWindow &operator[]( const char   *display_name );
    DisplayWindow &operator[]( const String &display_name );
    
    template<class TD>
    void operator<<( const TD &object ) {
        operator[]( "main" ) << object;
    }
    
    void wait_until_all_windows_are_closed();
    void rem_display_windows( const char *name );
    
public slots:
    void lastWindowClosed();
    void slot_add_display_window( const char *name );
    void slot_show_display_window( const char *name );

signals:
    void sign_add_display_window( const char *name );
    void sign_show_display_window( const char *name );
    
private:
    QMap<String,DisplayWindow *> display_windows;
    QMutex wait_mutex; // for the wait condition
    QWaitCondition wait_condition;
};

extern DisplayWindowManager display;

} // namespace Metil

int main_thread( int argc, char **argv ); //
#ifndef METILDISPLAYWINDOWMANAGER_CPP
    #define main main_thread
#endif // METILDISPLAYWINDOWMANAGER_CPP

#endif
