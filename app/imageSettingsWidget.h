#ifndef IMAGESETTINGSWIDGET_H
#define IMAGESETTINGSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>

#include "ncImagerSettings.h"

#include <QLayout>

class ImageSettingsWidget : public QWidget
{
    Q_OBJECT

    ImageWindowSettings* settings;
    QGridLayout* layout;

    void createControls();

public:
    explicit ImageSettingsWidget(QWidget *parent = 0);

signals:
    void applied();
    void canceled();
public slots:
    void apply();
    void cancel();
};

#endif // IMAGESETTINGSWIDGET_H
