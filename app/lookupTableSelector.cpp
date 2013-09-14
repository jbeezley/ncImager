
#include "lookupTableSelector.h"

#include <cmath>
#include <iostream>

using namespace luticon;

QPixmap LutIcon::pixmapFromLut(const LookupTable *lut, const int w, const int h) {
    uint8_t *A = new uint8_t [w * h];
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            A[i*w + j] = (uint8_t) round( (WIDTH-1)*(((double) j )/(w-1)) );
            //std::cout << i*w+j << " " << (int) A[i*w+j] << endl;
        }
    }
    uint8_t *pixelData = new uint8_t [w*h*LookupTable::PIXELELEMENTS];
    lut->makePColor(h * w, A, pixelData);
    delete [] A;
    return QPixmap::fromImage(QImage((uchar *) pixelData, w, h, QImage::Format_ARGB32));
}

LutIcon::LutIcon(const LookupTable *lut) : QIcon() {
    //QIcon(LutIcon::pixmapFromLut(lut)) {
    QPixmap pixmap;

    for(int i=MINWIDTH; i<=MAXWIDTH; i+=8) {
        pixmap = LutIcon::pixmapFromLut(lut, i, HEIGHT);
        addPixmap(pixmap);
    }
}

bool LookupTableSelector::initialized = false;
std::map<int, const LookupTable*> LookupTableSelector::luts;
std::map<int, const LutIcon*> LookupTableSelector::lutIcons;
const string LookupTableSelector::defaultLUTName("jet");
int LookupTableSelector::defaultLUTIndex = 0;

void LookupTableSelector::loadLookupTables() {
    for(int i=0; i<LookupTable::getNTables(); i++) {
        const LookupTable& lut = LookupTable::getLUT(i);
        string name(LookupTable::getTableName(i));
        if (name == defaultLUTName) defaultLUTIndex = i;
        luts[i] = &lut;
        lutIcons[i] = new LutIcon(&lut);
    }
    initialized = true;
}

LookupTableSelector::LookupTableSelector(QWidget *parent) :
    QComboBox(parent)
{
    if(!initialized) {
        loadLookupTables();
    }
    for(unsigned int i = 0; i<luts.size(); i++) {
        //insertSeparator(2*i+2);
        addItem(*lutIcons[i], QString());
    }
    setIconSize(QSize(LutIcon::WIDTH, LutIcon::HEIGHT));
    setSizeAdjustPolicy(AdjustToContents);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setCurrentIndex(defaultLUTIndex);
    setMinimumWidth(LutIcon::MINWIDTH);
    setMaximumWidth(LutIcon::MAXWIDTH);
}

void LookupTableSelector::resizeEvent(QResizeEvent *e) {
    setIconSize(QSize(size().width(), size().height()));
    QComboBox::resizeEvent(e);
}

const LookupTable* LookupTableSelector::getLUT(const int i) const {
    return luts[i];
}
