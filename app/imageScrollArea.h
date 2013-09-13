#ifndef IMAGESCROLLAREA_H
#define IMAGESCROLLAREA_H

#include <QScrollArea>
#include <QSize>
#include <QWheelEvent>

class ImageScrollArea : public QScrollArea
{
    Q_OBJECT
    double maxScale, minScale;
    double scale, scaleFactor;
    double mouseZoomFactor;

    static const int maxImageHeight = 10000;
    static const int maxImageWidth = 10000;
    static const int minImageHeight = 50;
    static const int minImageWidth = 50;

public:
    explicit ImageScrollArea(QWidget *parent = 0);

    void zoomIn(const double nSteps = 1);
    void zoomOut(const double nSteps = 1);
    void fitToWindow();
    void setWidget(QWidget *widget);
    void updateScales();
    QSize fitSizeToAspectRatio(const QSize& wsize);
    void wheelEvent(QWheelEvent *event);

signals:

public slots:

};

#endif // IMAGESCROLLAREA_H
