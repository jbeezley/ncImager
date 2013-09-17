#include "fileWindow.h"

#include <QMessageBox>

//#include <iostream>
#include <cassert>

void FileWindow::openFile(const QString &fileName) {
    _file = new FileObject(fileName);
    _file->openFile();
}

FileWindow::FileWindow(QString fileName, QWidget *parent) :
    QMainWindow(parent), _fileName(fileName)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    //_file = new NcSliceFile(fileName.toStdString());
    openFile(fileName);

    if (!_file || !_file->isOpen()) {
        QMessageBox::critical(this, tr("ncImager"),
                              QString("Could not open file: ") + fileName);
        this->close();
        return;
    }
    variables = new QComboBox(this);
    variables->setToolTip(tr("Select a variable."));

    QWidget* mainWidget = new QWidget(this);
    layout = new QHBoxLayout(mainWidget);
    layout->addWidget(variables);


    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    populateVariables();

    connect(variables, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(openVariable(QString)));

    this->raise();
    this->show();
}

void FileWindow::populateVariables() {
    variables->clear();
    NcSliceFile::variableMapType vmap = _file->variables();
    for(NcSliceFile::variableMapType::const_iterator it=vmap.begin(); it != vmap.end(); it++) {
        std::string varname = it->first;
        variables->addItem(QString(varname.c_str()));
    }
}

void FileWindow::openVariable(QString varName) {
    if(!_file->isOpen()) return;
    //cout << "openVariable  called: " << varName.toStdString() << endl;
    const BaseVariable *var = _file->getVariable(varName);
    assert(var);
    ImageWindow* imageWindow=new ImageWindow(var, this);
    imageWindow->setWindowTitle(_fileName + " : " + varName);
    imageWindow->raise();
    imageWindow->show();
}
