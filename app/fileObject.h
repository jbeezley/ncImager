#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include "common.h"

#include <QObject>
#include <QStringList>
#include <QMessageBox>
#include <iostream>

#include "ncFileReader.h"

class FileObject : public QObject
{
    Q_OBJECT
    const QString _fileName;
    NcSliceFile *_file;
    QStringList *varList;
    const QString _openvarmessage;

    bool checkFileOpen() {
        if (!_file || !_file->isOpen()) {
            QMessageBox::critical(NULL, tr("fileObject"),
                                  QString("Something has gone wrong with ") + _fileName);
            return false;
        }
        return true;
    }
    bool checkFileNotOpen() {
        if (_file && _file->isOpen()) {
            QMessageBox::critical(NULL, tr("fileObject"),
                                  QString("Trying to reopen an opened file ") + _fileName);
            return false;
        }
        return true;
    }

    void populateVarList() {
        if(varList) return;
        varList = new QStringList;
        varList->append(_openvarmessage);
        if(!checkFileOpen()) return;
        NcSliceFile::variableMapType vmap = _file->variables();
        for(NcSliceFile::variableMapType::const_iterator it=vmap.begin(); it != vmap.end(); it++) {
            std::string varname = it->first;
            varList->append(QString(varname.c_str()));
        }
    }

public:
    explicit FileObject(const QString& fileName, QObject *parent = 0) :
        QObject(parent), _fileName(fileName), _file(NULL), varList(NULL),
        _openvarmessage("Select a variable:"){}


signals:

    void variableList(QStringList); //
    void variableOpened(const BaseVariable*);
    void fileOpened(bool);
    void finished();

public slots:

    void openVariable(QString varName) {
        if(varName == _openvarmessage) return;
        emit variableOpened(_file->getVariable(varName.toStdString()));
    }

    void openFile() {
        if(checkFileNotOpen())
            _file = new NcSliceFile(_fileName.toStdString());
        emitFileStatus();
    }

    void emitFileStatus() {
        emit fileOpened( _file && _file->isOpen() );
    }

    void emitVariableList() {
        populateVarList();
        emit variableList(*varList);
    }

    void closeFile() {
        if(_file) {
            std::cerr << "Closing file " << _fileName.toStdString() << std::endl;
            delete _file;
            _file = NULL;
        }
        deleteLater();
    }

};

#endif // FILEOBJECT_H
