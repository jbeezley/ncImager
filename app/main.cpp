#include "mainWindow.h"
#include <QApplication>
#include <QString>
#include <cassert>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* mainWindow = new MainWindow;

    mainWindow->show();
    //mainWindow->setHidden(true);
    return a.exec();
}
