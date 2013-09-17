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

    void openFile() { _file = new NcSliceFile(_fileName.toStdString()); }
signals:
    void fileOpenFinished(NcSliceFile*);
    void finished();

public slots:
    void openFileSlot() {
        openFile();
        emit fileOpenFinished(_file);
    }
    void outputSlot() {
        bool test = true;
        bool test1=test;
    }


};

#endif // FILEOBJECT_H
