#include "imageSettingsWidget.h"

#include <QLabel>
#include <QPushButton>

ImageSettingsWidget::ImageSettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    settings = new ImageWindowSettings(this);
    layout = new QGridLayout(this);

    settings->readDefaults();

    createControls();
}

void ImageSettingsWidget::apply()
{
    settings->writeDefaults();
    emit applied();
    deleteLater();
}

void ImageSettingsWidget::cancel()
{
    emit canceled();
    deleteLater();
}

void ImageSettingsWidget::createControls()
{

    QSpinBox *xdimBox = new QSpinBox(this);
    QSpinBox *ydimBox = new QSpinBox(this);
    QCheckBox *xreverse = new QCheckBox(this);
    QCheckBox *yreverse = new QCheckBox(this);
    QSpinBox *imageWidth = new QSpinBox(this);
    QSpinBox *imageHeight = new QSpinBox(this);
    QPushButton *applyButton = new QPushButton(tr("Apply"),this);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"),this);

    xdimBox->setRange(-5,5);
    ydimBox->setRange(-5,5);
    imageWidth->setRange(30,999);
    imageHeight->setRange(30,999);

    xdimBox->setValue(settings->xDim());
    ydimBox->setValue(settings->yDim());
    xreverse->setChecked(settings->rxDim());
    yreverse->setChecked(settings->ryDim());
    imageWidth->setValue(settings->iWidth());
    imageHeight->setValue(settings->iHeight());

    layout->addWidget(new QLabel("X dimension:", this),0,0);
    layout->addWidget(xdimBox,0,1);
    layout->addWidget(new QLabel("Invert?", this),0,2);
    layout->addWidget(xreverse,0,3);

    layout->addWidget(new QLabel("Y dimension:", this),1,0);
    layout->addWidget(ydimBox,1,1);
    layout->addWidget(new QLabel("Invert?", this),1,2);
    layout->addWidget(yreverse,1,3);

    layout->addWidget(new QLabel("Image width: "),2,0);
    layout->addWidget(imageWidth,2,1);
    layout->addWidget(new QLabel("Image height:"),3,0);
    layout->addWidget(imageHeight,3,1);

    layout->addWidget(cancelButton,4,0);
    layout->addWidget(applyButton,4,1);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(applyButton, SIGNAL(clicked()), this, SLOT(apply()));

}
