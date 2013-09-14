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
    if(argc > 1) {
        FileWindow *fileWindow = mainWindow->openFile(argv[1]);
        for(int i=2; i<argc; i++) {
            if(fileWindow) {
                fileWindow->openVariable(QString(argv[i]));
            }
        }
    }
    return a.exec();
}
