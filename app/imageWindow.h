#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include "common.h"

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QSizePolicy>
#include <QSignalMapper>

#include <ncFileReader.h>
#include <lookupTable.h>
#include <norm.h>
#include <lutData.h>
#include <string>
#include <cstddef>

#include "imageScrollArea.h"
#include "fixedAspectLabel.h"
#include "lookupTableSelector.h"
#include "ncImagerSettings.h"
#include "imageSettingsWidget.h"

class ImageWindow : public QMainWindow
{
    Q_OBJECT

    static const int _dimLabelPos = 0,
                     _xcheckPos   = 1,
                     _ycheckPos   = 2,
                     _sliderPos   = 3,
                     _textPos     = 4,
                     _reversePos  = 5,
                     _headerRows  = 2;

    QWidget *mainWidget;
    ImageScrollArea *imageBox;
    FixedAspectLabel *imageLabel;
    QGridLayout *layout;
    QButtonGroup *xButtonGroup;
    QButtonGroup *yButtonGroup;
    QSignalMapper *indexMapper;
    LookupTableSelector *lTableBox;
    ImageWindowSettings *imgSettings;

    const BaseVariable* _var;
    BaseVariable::sliceType _slice;
    const LookupTable* _lut;
    LinearNorm<double> _norm;
    string _lutName;
    const double *data;
    int nDims;

    int findWidgetIDim(QWidget *widget) const;
    int widget2VarIDim(int iDim) const;

public:
    explicit ImageWindow(const BaseVariable* var, QWidget *parent = 0);
    //void setLUT(const string& lutName);
    void createDimensionControl(const string& dimname, const size_t dlen, const int iDim);
    void update();
    void closeEvent(QCloseEvent *);

signals:
    void closeWindow(QMainWindow*);

public slots:
    void setXDim(int xDim);
    void setYDim(int yDim);
    void setIndexValue(QWidget *widget);
    void setMirroring();
    void setLUT(int iLUT);
    void openSettings();

protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // IMAGEWINDOW_H
