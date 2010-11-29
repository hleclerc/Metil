#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include "BitmapDisplayWidget.h"

BEG_METIL_NAMESPACE;

BitmapDisplayWidget::BitmapDisplayWidget( int w, int h, QWidget *parent ) : QWidget(parent), display( w, h ) {
    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

QSize BitmapDisplayWidget::sizeHint() const {
    return QSize( display.get_w(), display.get_h() );
}

void BitmapDisplayWidget::keyPressEvent( QKeyEvent *key_event ) {
    if ( key_event->key() == Qt::Key_Escape )
        emit close();
}

void BitmapDisplayWidget::mousePressEvent( QMouseEvent *mouse_event ) {
    x_press = mouse_event->x();
    y_press = mouse_event->y();
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
    double d = pow( 1.5, e->delta() / 120.0 );
    display.zoom( d, e->x(), e->y() );
    repaint();
}

void BitmapDisplayWidget::resizeEvent( QResizeEvent *event ) {
    display.set_w( event->size().width() );
    display.set_h( event->size().height() );
}

void BitmapDisplayWidget::paintEvent( QPaintEvent * ) {
    QPainter painter( this );
    painter.fillRect( 0, 0, width(), height(), QColor( 0, 0, 0 ) );

    QImage img( display.get_w(), display.get_h(), QImage::Format_ARGB32 );
    display.render();
    display.img_rgba.copy_gpu_to_cpu( img.bits() );
    painter.drawImage( 0, 0, img );
}

END_METIL_NAMESPACE;
