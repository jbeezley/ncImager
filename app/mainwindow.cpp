#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMenuBar(parent)
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);

    this->addMenu(fileMenu);
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open NetCDF File"),
                                                    QDir::currentPath());

    if(!fileName.isEmpty())
        new FileWindow(fileName, this);
}
