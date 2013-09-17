#ifndef NCIMAGERSETTINGS_H
#define NCIMAGERSETTINGS_H

#include <QSettings>

class NcImagerSettings : public QSettings
{
    Q_OBJECT
public:
    explicit NcImagerSettings(QObject *parent = 0);

signals:

public slots:

};

#endif // NCIMAGERSETTINGS_H
