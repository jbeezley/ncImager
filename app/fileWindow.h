#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QHBoxLayout>

//#include <ncFileReader.h>
#include <string>

#include "fileObject.h"
#include "ncFileReader.h"
#include "imageWindow.h"


class FileWindow : public QMainWindow
{
    Q_OBJECT

    FileObject *_file;
    const QString _fileName;
    QComboBox *variables;
    QHBoxLayout *layout;

    void populateVariables();
    void openFile(const QString& fileName);
public:
    explicit FileWindow(QString fileName, QWidget *parent = 0);

signals:

public slots:
    void openVariable(QString varName);
};

#endif // FILEWINDOW_H
