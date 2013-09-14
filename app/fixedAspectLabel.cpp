#include "fixedAspectLabel.h"

#include <QPainter>
#include <cassert>

#pragma GCC diagnostic ignored "-Wunused-parameter"

FixedAspectLabel::FixedAspectLabel(QWidget *parent) :
    QLabel(parent) {
    x = 0;
    y = 0;
    buffer = NULL;
    dbuffer = NULL;
    setMouseTracking(true);
    setCursor(Qt::CrossCursor);
}

void FixedAspectLabel::redraw() {
    QPainter p(this);
    p.drawPixmap(x,y,scaledPixmap);
    p.end();
}

void FixedAspectLabel::setPixmap(const QPixmap& pixmap) {
    originalPixmap = pixmap;
    resizeEvent(NULL);
    repaint(rect());
}

void FixedAspectLabel::resizeEvent(QResizeEvent *event) {
    if( originalPixmap.isNull() ) return;
    scaledPixmap = originalPixmap.scaled(size(), Qt::KeepAspectRatio);
}

void FixedAspectLabel::paintEvent(QPaintEvent *event) {
    if(scaledPixmap.isNull()) return;
    const int lw = width();
    const int lh = height();
    const int pw = scaledPixmap.width();
    const int ph = scaledPixmap.height();

    x = (lw - pw)/2;
    y = (lh - ph)/2;

    redraw();
}

QSize FixedAspectLabel::sizeHint() const {
    if(!originalPixmap.isNull())
        return originalPixmap.size();
    else
        return QSize(0,0);
}

void FixedAspectLabel::setImageFromData(uint8_t *data, int width, int height, const double *ddata) {
    if(buffer) delete [] buffer;
    if(dbuffer) delete [] dbuffer;
    buffer = data;
    dbuffer = ddata;
    image = new QImage((uchar*) buffer, width, height, QImage::Format_ARGB32);
    updateImage();
}

void FixedAspectLabel::updateImage() {
   setPixmap(QPixmap::fromImage(image->mirrored(mirrorH, !mirrorV)));
}

void FixedAspectLabel::setMirror(bool horizontal, bool vertical) {
    mirrorH = horizontal;
    mirrorV = vertical;
    updateImage();
}

FixedAspectLabel::~FixedAspectLabel() {
    if(buffer) delete [] buffer;
}

double FixedAspectLabel::getDataValue(int i, int j) const {
    assert(dbuffer);
    return dbuffer[j*originalPixmap.width() + i];
}

void FixedAspectLabel::mouseMoveEvent(QMouseEvent *event) {
    if (!_statusBar || scaledPixmap.isNull()) return;
    int xp=event->pos().x() - x;
    int yp=event->pos().y() - y;
    if (xp >= 0 && yp >=0 &&
            xp < scaledPixmap.width() &&
            yp < scaledPixmap.height()) {
        yp = scaledPixmap.height() - yp - 1;
        xp = (xp * originalPixmap.width())/scaledPixmap.width();
        yp = (yp * originalPixmap.height())/scaledPixmap.height();
        QString status;
        if(dbuffer) {
            double d = getDataValue(xp,yp);
            status = "< %1, %2 > = %3";
            status = status.arg(xp).arg(yp).arg(d);
        }
        else {
            status = "< %1 , %2 >";
            status = status.arg(xp).arg(yp);
        }
        _statusBar->showMessage(status);
    }
}
