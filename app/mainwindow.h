#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "fileWindow.h"

class MainWindow : public QMenuBar
{
    Q_OBJECT
    QAction *openAct;
    QMenu *fileMenu;

public:
    MainWindow(QWidget *parent = 0);
    FileWindow* openFile(const char* fileName);

private slots:
    void open();
};

#endif // MAINWINDOW_H
