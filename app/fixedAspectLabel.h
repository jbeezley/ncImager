#ifndef FIXEDASPECTLABEL_H
#define FIXEDASPECTLABEL_H

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSize>

class FixedAspectLabel : public QLabel
{
    Q_OBJECT
private:
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

signals:

public slots:
    void updateImage();
};

#endif // FIXEDASPECTLABEL_H
