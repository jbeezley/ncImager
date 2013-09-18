#ifndef NCIMAGERSETTINGS_H
#define NCIMAGERSETTINGS_H

#include "common.h"

#include <QSettings>

class NcImagerSettings : public QSettings
{
    Q_OBJECT
public:
    explicit NcImagerSettings(QObject *parent = 0);

signals:

public slots:

};

class ImageWindowSettings : public NcImagerSettings
{
    Q_OBJECT
public:
    explicit ImageWindowSettings(QObject *parent = 0);

};

#endif // NCIMAGERSETTINGS_H
