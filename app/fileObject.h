#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <QObject>
#include "ncFileReader.h"

class FileObject : public QObject
{
    Q_OBJECT
    const QString _fileName;
    NcSliceFile *_file;

public:
    explicit FileObject(const QString& fileName, QObject *parent = 0) :
        QObject(parent), _fileName(fileName), _file(NULL) {}

    bool openFile() { _file = new NcSliceFile(_fileName.toStdString());
                      return isOpen(); }
    bool isOpen() const { return _file != NULL && _file->isOpen(); }
    NcSliceFile::variableMapType variables() const { return _file->variables(); }
    const BaseVariable *getVariable(const QString& varName) const { return _file->getVariable(varName.toStdString()); }


signals:

public slots:

};

#endif // FILEOBJECT_H
