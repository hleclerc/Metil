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

#define METILDISPLAYWINDOWMANAGER_CPP
#include "DisplayWindowManager.h"

#include <QtCore/QTimer>
#include <QtCore/QThread>

#include <QtGui/QApplication> 

namespace Metil {

DisplayWindowManager display;

// -----------------------------------------------------------------------------------------------
struct MainThread : public QThread {
    MainThread( int argc, char **argv ) : res( 0 ), argc( argc ), argv( argv ) {
        connect( this, SIGNAL(finished())        , qApp    , SLOT(quit())             );
        connect( qApp, SIGNAL(lastWindowClosed()), &display, SLOT(lastWindowClosed()) );
    }
    void run() {
        res = main_thread( argc, argv );
        display.wait_until_all_windows_are_closed();
    }
    int res;
    int argc;
    char **argv;
};

// -----------------------------------------------------------------------------------------------
DisplayWindowManager::DisplayWindowManager() {
    connect( this, SIGNAL(sign_add_display_window(const char *)), this, SLOT(slot_add_display_window(const char *)), Qt::BlockingQueuedConnection );
    connect( this, SIGNAL(sign_show_display_window(const char *)), this, SLOT(slot_show_display_window(const char *)) );
}

DisplayWindow &DisplayWindowManager::operator[]( const char *display_name ) {
    if ( not display_windows.count( display_name ) )
        emit sign_add_display_window( display_name );
    return *display_windows[ display_name ];
}

DisplayWindow &DisplayWindowManager::operator[]( const String &display_name ) {
    return operator[]( display_name.data() );
}

void DisplayWindowManager::wait_until_all_windows_are_closed() {
    if ( display_windows.size() ) {
        wait_mutex.lock();
        wait_condition.wait( &wait_mutex );
        wait_mutex.unlock();
    }
}

void DisplayWindowManager::lastWindowClosed() {
    wait_condition.wakeAll();
}

void DisplayWindowManager::slot_add_display_window( const char *name ) {
    DisplayWindow *res = new DisplayWindow( this, name );
    display_windows[ name ] = res;
}

void DisplayWindowManager::slot_show_display_window( const char *name ) {
    display_windows[ name ]->show();
}

void DisplayWindowManager::rem_display_windows( const char *name ) {
    display_windows.remove( name );
}

} // namespace Metil

// -----------------------------------------------------------------------------------------------
int main( int argc, char **argv ) {
    QApplication app( argc, argv );
    app.setQuitOnLastWindowClosed( false );
    
    Metil::MainThread main_thread( argc, argv );
    QTimer::singleShot( 0, &main_thread, SLOT(start()) );
 
//     app.exec();
    return main_thread.res;
}
