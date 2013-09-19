#include "ncImagerSettings.h"

NcImagerSettings::NcImagerSettings(QObject *parent) :
    QObject(parent)
{
    _settingsObj = new QSettings("beeztree", "ncImager", this);
}

void NcImagerSettings::readDefaults()
{

}

void NcImagerSettings::writeDefaults() const
{

}

ImageWindowSettings::ImageWindowSettings(QObject *parent) :
    NcImagerSettings(parent),
    _xDim(0), _yDim(1),
    _rxDim(false), _ryDim(false),
    _iWidth(500), _iHeight(500),
    settingsGroup("ImageWindow")
{

}

int ImageWindowSettings::xDim(int n) const
{
    if(xDim() >= 0) return xDim();
    else return n + xDim();
}

int ImageWindowSettings::yDim(int n) const
{
    if(yDim() >= 0) return yDim();
    else return n + yDim();
}

void ImageWindowSettings::readDefaults()
{
    NcImagerSettings::readDefaults();
    QSettings *set = settingsObj();

    set->beginGroup(settingsGroup);
    _xDim = set->value("xDim", _xDim).toInt();
    _yDim = set->value("yDim", _yDim).toInt();
    _rxDim = set->value("rxDim", _rxDim).toBool();
    _ryDim = set->value("ryDim", _ryDim).toBool();
    _iWidth = set->value("iWidth", _iWidth).toInt();
    _iHeight = set->value("iHeight", _iHeight).toInt();
    set->endGroup();
}

void ImageWindowSettings::writeDefaults() const
{
    NcImagerSettings::writeDefaults();
    QSettings *set = settingsObj();

    set->beginGroup(settingsGroup);
    set->setValue("xDim", _xDim);
    set->setValue("yDim", _yDim);
    set->setValue("rxDim", _rxDim);
    set->setValue("ryDim", _ryDim);
    set->setValue("iWidth", _iWidth);
    set->setValue("iHeight", _iHeight);
    set->endGroup();
}
