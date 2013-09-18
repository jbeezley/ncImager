#include "fileWindow.h"

#include <QMessageBox>
#include <QProgressBar>

#include <iostream>
#include <cassert>
/*
void FileWindow::openFile(const QString &fileName) {
    _file->openFile();
}
*/
FileWindow::FileWindow(QString fileName, QWidget *parent) :
    QMainWindow(parent), _fileName(fileName)
{

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    //_file = new NcSliceFile(fileName.toStdString());
    this->setWindowTitle(fileName);

    variables = new QComboBox(this);
    variables->setToolTip(tr("Select a variable to view."));

    QWidget* mainWidget = new QWidget(this);
    layout = new QHBoxLayout(mainWidget);
    layout->addWidget(variables);


    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    this->raise();
    this->show();

    fileObj = new FileObject(fileName);
    fthread = new QThread;

    fileObj->moveToThread(fthread);

    connect(fthread, SIGNAL(started()), fileObj, SLOT(openFile()));
    connect(fileObj, SIGNAL(fileOpened(bool)), this, SLOT(fileOpened(bool)));
    connect(fileObj, SIGNAL(variableList(QStringList)), this, SLOT(populateVariables(QStringList)));


    openDialog = new QProgressDialog(tr("Opening ") + fileName,
                                     tr("Cancel"), 0, 1, this);
    openDialog->setWindowModality(Qt::WindowModal);
    QProgressBar *bar = new QProgressBar(openDialog);
    bar->setVisible(false);
    openDialog->setBar(bar);
    openDialog->setValue(0);

    connect(openDialog, SIGNAL(canceled()), this, SLOT(cancelOpen()));
    connect(fileObj, SIGNAL(fileOpened(bool)), openDialog, SLOT(accept()));
    connect(fthread,SIGNAL(finished()), fileObj, SLOT(closeFile()));

    fthread->start();
    openDialog->exec();

}

FileWindow::~FileWindow() {
    if (fthread && fthread->isRunning()) {
        fthread->exit();
    }
}

void FileWindow::fileOpened(bool opened) {
    openDialog->setValue(1);

    if (!opened) {
        QMessageBox::critical(this, tr("ncImager"),
                              QString("Could not open file: ") + _fileName);
        this->close();
        return;
    }
    fileObj->emitVariableList();
}

void FileWindow::populateVariables(QStringList vlist) {
    // In case this method is called twice for some reason...
    fileObj->disconnect(SIGNAL(variableOpened(const BaseVariable*)));
    this->disconnect(SIGNAL(_requestOpenVariable(QString)));
    variables->disconnect();
    variables->clear();

    //variables->addItem(QString(""));
    variables->addItems(vlist);
    variables->setCurrentIndex(0);
    connect(variables, SIGNAL(activated(QString)),
            fileObj, SLOT(openVariable(QString)));
    connect(this, SIGNAL(_requestOpenVariable(QString)),
            fileObj, SLOT(openVariable(QString)));
    connect(fileObj, SIGNAL(variableOpened(const BaseVariable*)),
            this, SLOT(openVariable(const BaseVariable*)));
}

void FileWindow::openVariable(const BaseVariable* var) {
    variables->setCurrentIndex(0);
    if(!var) {
        QMessageBox::critical(this, tr("File Window"),
                              tr("Could not open variable."));
        return;
    }
    ImageWindow* imageWindow=new ImageWindow(var, this);
    imageWindow->setWindowTitle(_fileName + " : " + var->name().c_str());
    imageWindow->raise();
    imageWindow->show();
}

void FileWindow::cancelOpen() {
    std::cerr << std::string("Warning forcing close of file ") + _fileName.toStdString() << std::endl;
    fthread->terminate();
    //fthread->wait();
    this->close();
}

void FileWindow::requestOpenVariable(QString varname) {
    emit _requestOpenVariable(varname);
}

void FileWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_W && event->modifiers().testFlag(Qt::ControlModifier))
        close();
    else
        QMainWindow::keyPressEvent(event);
}
