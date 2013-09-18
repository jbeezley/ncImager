#include "ncImagerSettings.h"

NcImagerSettings::NcImagerSettings(QObject *parent) :
    QSettings(parent)
{
}

ImageWindowSettings::ImageWindowSettings(QObject *parent) :
    NcImagerSettings(parent)
{
    beginGroup("ImageWindow");
    endGroup();
}
