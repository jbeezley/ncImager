#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QHBoxLayout>
#include <QThread>
#include <QProgressDialog>
#include <QList>
#include <QStringList>

#include <ncFileReader.h>
#include <string>

#include "fileObject.h"
//#include "ncFileReader.h"
#include "imageWindow.h"


class FileWindow : public QMainWindow
{
    Q_OBJECT

    //const NcSliceFile *_file;
    const QString _fileName;
    QComboBox *variables;
    QHBoxLayout *layout;
    QThread *fthread;
    QProgressDialog *openDialog;
    QList<QString> queuedVariables;
    FileObject *fileObj;

    //void openFile(const QString& fileName);
public:
    explicit FileWindow(QString fileName, QWidget *parent = 0);
    ~FileWindow();
    void requestOpenVariable(QString varname);

signals:
    //void filePointerReceived();
    void _requestOpenVariable(const QString& varname);

public slots:
    void fileOpened(bool opened);
    void openVariable(const BaseVariable* var);
    void cancelOpen();
    //void openFile();
protected slots:
    void populateVariables(QStringList);
};

#endif // FILEWINDOW_H
