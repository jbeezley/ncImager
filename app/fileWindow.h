#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QHBoxLayout>

#include <ncFileReader.h>
#include <string>

#include "imageWindow.h"


class FileWindow : public QMainWindow
{
    Q_OBJECT

    const NcSliceFile *_file;
    const QString _fileName;
    QComboBox *variables;
    QHBoxLayout *layout;
    //ImageWindow *imageWindow;

    void populateVariables();
public:
    explicit FileWindow(QString fileName, QWidget *parent = 0);

signals:

public slots:
    void openVariable(QString varName);
};

#endif // FILEWINDOW_H
