#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QHBoxLayout>
#include <QThread>
#include <QProgressDialog>
#include <QList>

//#include <ncFileReader.h>
#include <string>

#include "fileObject.h"
#include "ncFileReader.h"
#include "imageWindow.h"


class FileWindow : public QMainWindow
{
    Q_OBJECT

    const NcSliceFile *_file;
    const QString _fileName;
    QComboBox *variables;
    QHBoxLayout *layout;
    QThread *fthread;
    QProgressDialog *openDialog;
    QList<QString> queuedVariables;

    void populateVariables();
    void flushVariableQueue();
    //void openFile(const QString& fileName);
public:
    explicit FileWindow(QString fileName, QWidget *parent = 0);

signals:
    void filePointerReceived();

public slots:
    void fileOpened(NcSliceFile *file);
    void openVariable(QString varName, bool enableQueue = true);
    void cancelOpen();
    //void openFile();
};

#endif // FILEWINDOW_H
