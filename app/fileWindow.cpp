#include "fileWindow.h"

#include <QMessageBox>

#include <iostream>
#include <cassert>
/*
void FileWindow::openFile(const QString &fileName) {
    _file->openFile();
}
*/
FileWindow::FileWindow(QString fileName, QWidget *parent) :
    QMainWindow(parent), _file(NULL), _fileName(fileName)
{

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    //_file = new NcSliceFile(fileName.toStdString());

    variables = new QComboBox(this);
    variables->setToolTip(tr("Select a variable."));

    QWidget* mainWidget = new QWidget(this);
    layout = new QHBoxLayout(mainWidget);
    layout->addWidget(variables);


    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    this->raise();
    this->show();

    FileObject *fileObj = new FileObject(fileName);
    fthread = new QThread;

    fileObj->moveToThread(fthread);
    connect(fthread, SIGNAL(started()), fileObj, SLOT(openFileSlot()));
    connect(fthread, SIGNAL(finished()), fthread, SLOT(deleteLater()));
    connect(fileObj, SIGNAL(fileOpenFinished(NcSliceFile*)), this, SLOT(fileOpened(NcSliceFile*)));
    connect(fileObj, SIGNAL(finished()), fileObj, SLOT(deleteLater()));
    connect(this, SIGNAL(filePointerReceived()), fthread, SLOT(quit()));
    connect(this, SIGNAL(filePointerReceived()), fileObj, SLOT(deleteLater()));

    openDialog = new QProgressDialog(tr("Opening ") + fileName,
                                     tr("Cancel"), 0, 1, this);
    openDialog->setWindowModality(Qt::WindowModal);
    //connect(openDialog, SIGNAL(canceled()), this, SLOT(cancelOpen()));
    connect(this, SIGNAL(filePointerReceived()), openDialog, SLOT(accept()));
    openDialog->raise();
    openDialog->show();
    fthread->start();


}

void FileWindow::fileOpened(NcSliceFile* file) {
    openDialog->setValue(1);
    _file = file;

    emit filePointerReceived();
    fthread = NULL;

    if (!_file || !_file->isOpen()) {
        QMessageBox::critical(this, tr("ncImager"),
                              QString("Could not open file: ") + _fileName);
        this->close();
        return;
    }
    populateVariables();
    connect(variables, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(openVariable(QString)));

    this->raise();
    this->show();
    flushVariableQueue();
}

void FileWindow::populateVariables() {
    variables->clear();
    NcSliceFile::variableMapType vmap = _file->variables();
    for(NcSliceFile::variableMapType::const_iterator it=vmap.begin(); it != vmap.end(); it++) {
        std::string varname = it->first;
        variables->addItem(QString(varname.c_str()));
    }
}

void FileWindow::flushVariableQueue() {
    while(!queuedVariables.isEmpty()) {
        openVariable(queuedVariables.takeFirst(), false);
    }
}


void FileWindow::openVariable(QString varName, bool enableQueue) {

    if(!_file || !_file->isOpen()) {
        if(!enableQueue) {
            QMessageBox::critical(this, tr("ncImager"),
                                  tr("Error: The file is not opened!"));
        }
        else {
            queuedVariables << varName;
        }
        return;
    }
    //cout << "openVariable  called: " << varName.toStdString() << endl;
    const BaseVariable *var = _file->getVariable(varName.toStdString());
    assert(var);
    ImageWindow* imageWindow=new ImageWindow(var, this);
    imageWindow->setWindowTitle(_fileName + " : " + varName);
    imageWindow->raise();
    imageWindow->show();
}

void FileWindow::cancelOpen() {
    fthread->terminate();
    this->close();
}
