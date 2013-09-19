#ifndef NCIMAGERSETTINGS_H
#define NCIMAGERSETTINGS_H

#include "common.h"

#include <QObject>
#include <QSettings>
#include <QString>

class NcImagerSettings : public QObject
{
    QSettings *_settingsObj;
    Q_OBJECT
public:
    explicit NcImagerSettings(QObject *parent = 0);

protected:
    QSettings* settingsObj() const {return _settingsObj;}

signals:

public slots:
    virtual void readDefaults();
    virtual void writeDefaults() const;

};

class ImageWindowSettings : public NcImagerSettings
{
    Q_OBJECT
    int _xDim, _yDim;
    bool _rxDim, _ryDim;
    int _iWidth, _iHeight;

    const QString settingsGroup;

public:
    explicit ImageWindowSettings(QObject *parent = 0);

    int xDim() const {return _xDim;}
    int yDim() const {return _yDim;}
    bool rxDim() const {return _rxDim;}
    bool ryDim() const {return _ryDim;}
    int iWidth() const {return _iWidth;}
    int iHeight() const {return _iHeight;}
    int xDim(int n) const;
    int yDim(int n) const;

public slots:
    virtual void readDefaults();
    virtual void writeDefaults() const;

};

#endif // NCIMAGERSETTINGS_H
