#include "imageScrollArea.h"

#include <math.h>
#include <QtGlobal>
#include <QScrollBar>

ImageScrollArea::ImageScrollArea(QWidget *parent) :
    QScrollArea(parent) {
    maxScale = 1.0;
    minScale = 1.0;
    scale = 1.0;
    scaleFactor = 1.25;
    mouseZoomFactor = 1.0;
    scrolling = false;
}

void ImageScrollArea::zoomIn(const double nSteps) {
    updateScales();
    setWidgetResizable(false);
    double temp = scale * pow(scaleFactor, nSteps);
    if (temp > maxScale) {
        if (scale == maxScale) return;
        temp = maxScale;
    }
    else if(temp < minScale) {
        if (scale == minScale) return;
        temp = minScale;
    }
    scale = temp;
    QSize newSize(fitSizeToAspectRatio(widget()->sizeHint() * scale));
    widget()->resize(newSize);
}

void ImageScrollArea::zoomOut(const double nSteps) {
    zoomIn(-nSteps);
}

void ImageScrollArea::fitToWindow() {
    updateScales();
    setWidgetResizable(true);
    if(widget())
        widget()->resize(size());
}

void ImageScrollArea::setWidget(QWidget *widget) {
    this->QScrollArea::setWidget(widget);
    setAlignment(Qt::AlignCenter);
    setWidgetResizable(true);
    updateScales();
}

void ImageScrollArea::updateScales() {
    if(!widget() ||
          ( widget()->sizeHint().width() == 0 ||
            widget()->sizeHint().height() == 0)) {
        maxScale = 1.0;
        minScale = 1.0;
    }
    else {
        QSize wsize(widget()->sizeHint());
        minScale = fmin(
          ((double) minImageHeight)/wsize.height(),
          ((double) minImageWidth)/wsize.width() );
        maxScale = fmax(
          ((double) maxImageHeight)/wsize.height(),
          ((double) maxImageWidth)/wsize.width() );
    }
}

QSize ImageScrollArea::fitSizeToAspectRatio(const QSize &wsize) {
    setWidgetResizable(false);
    if(!widget()) return size();
    QSize isize(widget()->sizeHint());
    double iw = isize.width();
    double ih = isize.height();
    double ww = wsize.width();
    double wh = wsize.height();
    int w, h;
    if ( iw == 0 || ih == 0 || ww == 0 || wh == 0 )
        return size();
    else if (iw/ih >= ww/wh) {
        w = ww;
        h = round(ww * ih / iw);
    }
    else {
        w = round(wh * iw / ih);
        h = wh;
    }
    return QSize(w,h);
}

void ImageScrollArea::wheelEvent(QWheelEvent *event) {
    if(event->modifiers().testFlag(Qt::ControlModifier)) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        double factor = mouseZoomFactor * event->angleDelta().y()/360.;
#else
        double factor = mouseZoomFactor * event->delta()/360.;
#endif
        zoomIn(factor);
    }
    else {
        QScrollArea::wheelEvent(event);
    }
}

void ImageScrollArea::scrollWindow(const QPoint &delta) {
    QScrollBar *vscroll=verticalScrollBar();
    QScrollBar *hscroll=horizontalScrollBar();

    vscroll->setValue(vscroll->value() + delta.y());
    hscroll->setValue(hscroll->value() + delta.x());
}

void ImageScrollArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scrolling = true;
    }
}

void ImageScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scrolling) {
        scrollWindow(lastPoint - event->pos());
        lastPoint = event->pos();
    }
}

void ImageScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scrolling) {
        scrollWindow(lastPoint - event->pos());
        lastPoint = event->pos();
        scrolling = false;
    }
}
