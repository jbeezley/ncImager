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
    QAction *urlAct;
    QMenu *fileMenu;

public:
    MainWindow(QWidget *parent = 0);
    FileWindow* openFile(const char* fileName);

private slots:
    void openLocal();
    void openURL();
};

#endif // MAINWINDOW_H
