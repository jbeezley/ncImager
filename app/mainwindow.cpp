#include "mainwindow.h"

#include <QInputDialog>
#include <QString>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menuBar = new QMenuBar(this);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openLocal()));

    urlAct = new QAction(tr("Open &URL..."), this);
    urlAct->setShortcut(tr("Ctrl+U"));
    connect(urlAct, SIGNAL(triggered()), this, SLOT(openURL()));

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(urlAct);

    menuBar->addMenu(fileMenu);

}

void MainWindow::openLocal() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open NetCDF File"),
                                                    QDir::currentPath());

    if(!fileName.isEmpty())
        new FileWindow(fileName, this);
}

FileWindow* MainWindow::openFile(const char* fileName ) {
    return new FileWindow(fileName, this);
}

void MainWindow::openURL() {
    //QInputDialog *dialog = new QInputDialog(this, Qt::Popup);
    bool ok;
    QString url = QInputDialog::getText(this,
                            tr("Open URL"),
                            tr("Enter a URL to an OPenDAP dataset:"),
                            QLineEdit::Normal,
                            QString(),
                            &ok);

    if(ok and !url.isEmpty()) new FileWindow(QString("[cache=1][noprefetch][wholevar]") + url, this);
}
