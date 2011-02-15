#ifndef BITMAPDISPLAYWIDGET_H
#define BITMAPDISPLAYWIDGET_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#pragma lib_name QtCore
#pragma lib_name QtGui
#endif // METIL_COMP_DIRECTIVE

#include <QtGui/QWidget>
#include "BitmapDisplay.h"

BEG_METIL_NAMESPACE;

class BitmapDisplayWidget : public QWidget { // Q_OBJECT
public:
    typedef BitmapDisplay::T T;
    explicit BitmapDisplayWidget( int w, int h, QWidget *parent = 0 );
    virtual void paintEvent( QPaintEvent *paint_event );
    virtual void keyPressEvent( QKeyEvent *key_event );
    virtual void mousePressEvent( QMouseEvent *mouse_event );
    virtual void mouseMoveEvent( QMouseEvent *mouse_event );
    virtual void wheelEvent( QWheelEvent *event );
    virtual void resizeEvent( QResizeEvent *event );
    QSize sizeHint() const;

    BitmapDisplay display;
signals:

public slots:

private:
    int x_press, y_press;
};

END_METIL_NAMESPACE;

#endif // BITMAPDISPLAYWIDGET_H
