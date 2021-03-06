#ifndef FIXEDASPECTLABEL_H
#define FIXEDASPECTLABEL_H

#include "common.h"

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QStatusBar>
#include <QMouseEvent>

class FixedAspectLabel : public QLabel
{
    Q_OBJECT
private:
    QStatusBar *_statusBar;
    QPixmap originalPixmap;
    QPixmap scaledPixmap;
    QImage *image;
    uint8_t *buffer;
    const double *dbuffer;
    const double *_coordx, *_coordy;
    bool mirrorH, mirrorV;
    int x, y;
    QString varname;
    QSize *defaultSize;
    void redraw();
    double getDataValue(int i, int j) const;

public:
    explicit FixedAspectLabel(QWidget *parent = 0);
    ~FixedAspectLabel();
    void setPixmap(const QPixmap& pixmap);
    void setImageFromData(uint8_t *data, int width, int height, const double *ddata=NULL);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
    void setMirror(bool horizontal, bool vertical);
    void setStatusBar(QStatusBar *statusBar) { _statusBar = statusBar; }
    void setVarName(const QString& vname) {varname = vname;}
    void mouseMoveEvent(QMouseEvent *event);
    void setCoordinateArrays(const double *cx, const double *cy) {_coordx = cx; _coordy = cy;}
    void setDefaultSize(const QSize& size);

signals:

public slots:
    void updateImage();
};

#endif // FIXEDASPECTLABEL_H
