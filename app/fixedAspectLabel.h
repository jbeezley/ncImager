#ifndef FIXEDASPECTLABEL_H
#define FIXEDASPECTLABEL_H

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
    bool mirrorH, mirrorV;
    int x, y;
    void redraw();

public:
    explicit FixedAspectLabel(QWidget *parent = 0);
    ~FixedAspectLabel();
    void setPixmap(const QPixmap& pixmap);
    void setImageFromData(uint8_t *data, int width, int height);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
    void setMirror(bool horizontal, bool vertical);
    void setStatusBar(QStatusBar *statusBar) { _statusBar = statusBar; }
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void updateImage();
};

#endif // FIXEDASPECTLABEL_H
