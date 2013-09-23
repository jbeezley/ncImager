#include "imageWindow.h"

#include <QStatusBar>
#include <cassert>
#include <QDebug>

ImageWindow::ImageWindow(const BaseVariable* var, QWidget *parent) :
    QMainWindow(parent), _var(var), _slice(var->shape()) {

    nDims = var->nDims();
    imgSettings = new ImageWindowSettings;
    imgSettings->readDefaults();

    mainWidget = new QWidget(this);
    imageBox = new ImageScrollArea(mainWidget);
    imageLabel = new FixedAspectLabel(imageBox);
    imageBox->setWidget(imageLabel);

    layout = new QGridLayout(mainWidget);
    layout->setContentsMargins(5,5,5,5);
    layout->setColumnStretch(_sliderPos, 1);
    layout->setRowStretch(0,1);

    layout->addWidget(imageBox, 0, 0, 1, 6);
    layout->addWidget(new QLabel(QString("X"), mainWidget), 1, _xcheckPos);
    layout->addWidget(new QLabel(QString("Y"), mainWidget), 1, _ycheckPos);

    lTableBox = new LookupTableSelector();
    lTableBox->setToolTip(tr("<p>Select a color map.</p>"));
    layout->addWidget(lTableBox, 1, _sliderPos);

    QPushButton *config = new QPushButton(QString("&Config"), mainWidget);
    layout->addWidget(config, 1, _textPos, 1, 2);

    xButtonGroup = new QButtonGroup(mainWidget);
    yButtonGroup = new QButtonGroup(mainWidget);
    indexMapper = new QSignalMapper(mainWidget);

    size_t dlen;
    int vdim;
    for(int iDim = 0; iDim < (int) var->nDims(); iDim++) {
        vdim = widget2VarIDim(iDim);
        dlen = var->shape()[vdim];
        createDimensionControl(var->dimName(vdim), dlen, iDim);
    }

    imageLabel->setStatusBar(statusBar());
    imageLabel->setVarName(QString(_var->name().c_str()));

    connect(xButtonGroup,SIGNAL(buttonPressed(int)),
            this, SLOT(setXDim(int)));
    connect(yButtonGroup,SIGNAL(buttonPressed(int)),
            this, SLOT(setYDim(int)));
    connect(indexMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setIndexValue(QWidget*)));
    connect(lTableBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setLUT(int)));
    connect(config, SIGNAL(clicked()), this, SLOT(openSettings()));

    _slice.setXDim(widget2VarIDim(imgSettings->xDim(nDims)));
    _slice.setYDim(widget2VarIDim(imgSettings->yDim(nDims)));

    setCentralWidget(mainWidget);
    mainWidget->setLayout(layout);
    setLUT(LookupTableSelector::defaultLUTIndex);
    update();
    setMirroring();
}

void ImageWindow::setLUT(int iLUT) {
    _lut = lTableBox->getLUT(iLUT);
    update();
}

void ImageWindow::openSettings()
{
    QMainWindow *window = new QMainWindow(this);
    window->setWindowModality(Qt::WindowModal);
    ImageSettingsWidget *widget = new ImageSettingsWidget(window);
    window->setCentralWidget(widget);
    connect(widget, SIGNAL(applied()), this, SLOT(update()));
    connect(widget, SIGNAL(destroyed()), window, SLOT(deleteLater()));
    window->raise();
    window->show();
}

void ImageWindow::createDimensionControl(const string &dimname, const size_t dlen, const int iDim) {

    QLabel          *label = new QLabel(QString(dimname.c_str()), mainWidget);
    QRadioButton   *checkx = new QRadioButton(mainWidget);
    QRadioButton   *checky = new QRadioButton(mainWidget);
    QSlider        *slider = new QSlider(Qt::Horizontal, mainWidget);
    QSpinBox         *text = new QSpinBox(mainWidget);
    QCheckBox     *reverse = new QCheckBox(mainWidget);

    xButtonGroup->addButton(checkx, iDim);
    yButtonGroup->addButton(checky, iDim);

    slider->setSizePolicy(QSizePolicy::MinimumExpanding,
                          QSizePolicy::Fixed);
    slider->setRange(0, dlen-1);
    slider->setValue(0);
    slider->setDisabled(iDim == imgSettings->xDim(nDims) || iDim == imgSettings->yDim(nDims));
    slider->setToolTip(tr("<p>Slide to adjust the index of non-sliced dimension.</p>"));

    text->setRange(0, dlen-1);
    text->setWrapping(true);
    text->setButtonSymbols(QSpinBox::NoButtons);
    text->setValue(0);
    text->setToolTip(tr("<p>Enter index of non-sliced dimension.</p>"));

    reverse->setHidden(iDim != imgSettings->xDim(nDims) && iDim != imgSettings->yDim(nDims));
    reverse->setToolTip(tr("<p>Click here to invert this dimension.</p>"));

    if(iDim == imgSettings->xDim(nDims) && imgSettings->rxDim())
        reverse->toggle();
    if(iDim == imgSettings->yDim(nDims) && imgSettings->ryDim())
        reverse->toggle();

    checkx->setChecked(iDim == imgSettings->xDim(nDims));
    checky->setDisabled(iDim == imgSettings->xDim(nDims));
    checky->setChecked(iDim == imgSettings->yDim(nDims));
    checkx->setDisabled(iDim == imgSettings->yDim(nDims));
    checkx->setToolTip(tr("<p>Click here to show this dimension on the horizontal axis.</p>"));
    checky->setToolTip(tr("<p>Click here to show this dimension on the vertical axis.</p>"));

    layout->addWidget(label,  _headerRows + iDim, _dimLabelPos);
    layout->addWidget(checkx, _headerRows + iDim, _xcheckPos);
    layout->addWidget(checky, _headerRows + iDim, _ycheckPos);
    layout->addWidget(slider, _headerRows + iDim, _sliderPos);
    layout->addWidget(text,   _headerRows + iDim, _textPos);
    layout->addWidget(reverse,_headerRows + iDim, _reversePos);

    indexMapper->setMapping(text, text);

    connect(slider, SIGNAL(valueChanged(int)),
            text,   SLOT(setValue(int)));
    connect(text,   SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));

    connect(checkx, SIGNAL(toggled(bool)),
            slider, SLOT(setDisabled(bool)));
    connect(checkx, SIGNAL(toggled(bool)),
            text,   SLOT(setDisabled(bool)));
    connect(checkx, SIGNAL(toggled(bool)),
            checky, SLOT(setDisabled(bool)));
    connect(checkx, SIGNAL(toggled(bool)),
            reverse,SLOT(setVisible(bool)));

    connect(checky, SIGNAL(toggled(bool)),
            slider, SLOT(setDisabled(bool)));
    connect(checky, SIGNAL(toggled(bool)),
            text,   SLOT(setDisabled(bool)));
    connect(checky, SIGNAL(toggled(bool)),
            checkx, SLOT(setDisabled(bool)));
    connect(checky, SIGNAL(toggled(bool)),
            reverse,SLOT(setVisible(bool)));

    connect(text, SIGNAL(valueChanged(int)),
            indexMapper, SLOT(map()));
    connect(reverse, SIGNAL(toggled(bool)),
            this, SLOT(setMirroring()));

    /*
            checkx.toggled.connect(self.updateImage)
            checky.toggled.connect(self.updateImage)
            text.valueChanged.connect(self.updateImage)
            invert.toggled.connect(self.updateImage)
            */
}

void ImageWindow::setXDim(int xDim) {
    _slice.setXDim(widget2VarIDim(xDim));
    //cout << _slice << endl;
    update();
}

void ImageWindow::setYDim(int yDim) {
    _slice.setYDim(widget2VarIDim(yDim));
    //cout << _slice << endl;
    update();
}

int ImageWindow::findWidgetIDim(QWidget *widget) const {
    int index = layout->indexOf(widget);
    if(index < 0) return -1;
    int row, column, rowSpan, columnSpan;
    layout->getItemPosition(index, &row, &column, &rowSpan, &columnSpan);
    assert(row - _headerRows >= 0);
    return widget2VarIDim(row - _headerRows);
}

int ImageWindow::widget2VarIDim(int iDim) const {
    return _var->nDims() - iDim - 1;
}

void ImageWindow::setIndexValue(QWidget *widget) {
    QSpinBox *spinBox = qobject_cast<QSpinBox *> (widget);
    if(spinBox) {
        int vDim = findWidgetIDim(widget);
        _slice[vDim] = spinBox->value();
    }
    //cout << _slice << endl;
    update();
}

void ImageWindow::update() {
    assert(_slice.isValid());
    const int N = _var->sliceSize(_slice);
    double *vardata = new double [N];
    assert(vardata);
    _var->readSlice(_slice, vardata);
    uint8_t *pixdata = new uint8_t [N];
    assert(pixdata);
    _norm.setMinMaxValFromArray(N, vardata);
    _norm.normalize(N,vardata,pixdata);
    uint8_t *data = new uint8_t [_lut->imageSize(N)];
    assert(data);
    _lut->makePColor(N,pixdata,data);
    delete [] pixdata;
    int width = _var->shape()[_slice.xDim()];
    int height = _var->shape()[_slice.yDim()];
    assert(width*height == N);
    imageLabel->setImageFromData(data, width, height, vardata);
    setMirroring();
    imageBox->fitToWindow();
}

void ImageWindow::closeEvent(QCloseEvent *)
{
    emit closeWindow(this);
}

void ImageWindow::setMirroring() {
    int xDim = widget2VarIDim(_slice.xDim());
    int yDim = widget2VarIDim(_slice.yDim());

    QCheckBox *reverseX = qobject_cast<QCheckBox *>
            (layout->itemAtPosition(xDim + _headerRows, _reversePos)->widget());
    QCheckBox *reverseY = qobject_cast<QCheckBox *>
            (layout->itemAtPosition(yDim + _headerRows, _reversePos)->widget());
    bool mirrorH = reverseX->isChecked();
    bool mirrorV = reverseY->isChecked();
    imageLabel->setMirror(mirrorH, mirrorV);
}

void ImageWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_W && event->modifiers().testFlag(Qt::ControlModifier))
        close();
    else
        QMainWindow::keyPressEvent(event);
}
