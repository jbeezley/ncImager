#include "fixedAspectLabel.h"

#include <QPainter>

#pragma GCC diagnostic ignored "-Wunused-parameter"

FixedAspectLabel::FixedAspectLabel(QWidget *parent) :
    QLabel(parent) {
    x = 0;
    y = 0;
    buffer = NULL;
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

void FixedAspectLabel::setImageFromData(uint8_t *data, int width, int height) {
    if(buffer) delete [] buffer;
    buffer = data;
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

