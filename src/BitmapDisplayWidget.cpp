#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include "BitmapDisplayWidget.h"
#include "CudaMetil.h"
#include "System.h"

BEG_METIL_NAMESPACE;

BitmapDisplayWidget::BitmapDisplayWidget( int w, int h, QWidget *parent ) : QWidget(parent), display( w, h ) {
    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

QSize BitmapDisplayWidget::sizeHint() const {
    return QSize( display.get_w(), display.get_h() );
}

void BitmapDisplayWidget::keyPressEvent( QKeyEvent *key_event ) {
    if ( key_event->modifiers() & Qt::ControlModifier ) {
        switch ( key_event->key() ) {
        case Qt::Key_Up    : display.zoom( 1.25, width() / 2, height() / 2 ); repaint(); break;
        case Qt::Key_Down  : display.zoom( 0.80, width() / 2, height() / 2 ); repaint(); break;
        }
    } else if ( key_event->modifiers() & Qt::ShiftModifier ) {
        switch ( key_event->key() ) {
        case Qt::Key_Right : display.pan( -10, 0 ); repaint(); break;
        case Qt::Key_Left  : display.pan( +10, 0 ); repaint(); break;
        case Qt::Key_Up    : display.pan( 0, +10 ); repaint(); break;
        case Qt::Key_Down  : display.pan( 0, -10 ); repaint(); break;
        }
    } else  {
        switch ( key_event->key() ) {
        case Qt::Key_Escape: emit close(); break;
        case Qt::Key_Right : display.rotate( 0.0, -0.2, 0.0 ); repaint(); break;
        case Qt::Key_Left  : display.rotate( 0.0, +0.2, 0.0 ); repaint(); break;
        case Qt::Key_Up    : display.rotate( -0.2, 0.0, 0.0 ); repaint(); break;
        case Qt::Key_Down  : display.rotate( +0.2, 0.0, 0.0 ); repaint(); break;
        case Qt::Key_Home  : display.fit(); repaint(); break;
        }
    }
}

void BitmapDisplayWidget::mousePressEvent( QMouseEvent *mouse_event ) {
    x_press = mouse_event->x();
    y_press = mouse_event->y();
    if ( mouse_event->buttons() & Qt::RightButton  ) {
        unsigned nnnn = display.img_nnnn.get_val_from_gpu( x_press, y_press );
        PRINT( nnnn );
    }
}

void BitmapDisplayWidget::mouseMoveEvent( QMouseEvent *mouse_event ) {
    int new_x = mouse_event->x();
    int new_y = mouse_event->y();

    T mwh = min( width(), height() );
    if ( mouse_event->buttons() & Qt::LeftButton ) { // rot
        display.rotate( 2.0 * ( new_y - y_press ) / mwh, 2.0 * ( x_press - new_x ) / mwh, 0.0 );
        repaint();
    } else if ( mouse_event->buttons() & Qt::MidButton ) { // pan
        T x = display.get_d() * ( new_x - x_press ) / mwh;
        T y = display.get_d() * ( new_y - y_press ) / mwh;
        display.set_O( display.get_O() - x * display.get_X() - y * display.get_Y() );
        repaint();
    }

    x_press = new_x;
    y_press = new_y;
}

void BitmapDisplayWidget::wheelEvent( QWheelEvent *e ) {
    if ( e->modifiers() & Qt::ShiftModifier ) {
        display.shrink( e->delta() / 12000.0 );
        repaint();
    } else {
        double d = pow( 1.5, e->delta() / 240.0 );
        display.zoom( d, e->x(), e->y() );
        repaint();
    }
}

void BitmapDisplayWidget::resizeEvent( QResizeEvent *event ) {
    display.set_w( event->size().width() );
    display.set_h( event->size().height() );
}

void BitmapDisplayWidget::paintEvent( QPaintEvent * ) {
    QPainter painter( this );

    // painter.fillRect( 0, 0, width(), height(), QColor( 0, 0, 0 ) );
    QLinearGradient grad( 0, 0, 0, height() );
    grad.setColorAt( 0.1, QColor( 0, 0,   0 ) );
    grad.setColorAt( 0.5, QColor( 0, 0,  25 ) );
    grad.setColorAt( 0.9, QColor( 0, 0, 125 ) );
    painter.fillRect( 0, 0, width(), height(), grad );

    // image
    QImage img( display.get_w(), display.get_h(), QImage::Format_ARGB32 );
    cudaThreadSynchronize();
    double t0 = time_of_day_in_sec();
    display.render();
    cudaThreadSynchronize();
    double t1 = time_of_day_in_sec();
    PRINT( t1 - t0 );

    display.img_rgba.copy_gpu_to_cpu( img.bits() );
    painter.drawImage( 0, 0, img );
}

END_METIL_NAMESPACE;
