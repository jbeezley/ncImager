
#include "lookupTableSelector.h"

#include <cmath>
#include <iostream>

using namespace luticon;

QPixmap LutIcon::pixmapFromLut(const LookupTable *lut) {
    uint8_t A[WIDTH * HEIGHT];
    for(int i=0; i<HEIGHT; i++) {
        for(int j=0; j<WIDTH; j++) {
            A[i*WIDTH + j] = (uint8_t) round( (WIDTH-1)*(((double) j )/(WIDTH-1)) );
        }
    }
    uint8_t pixelData[WIDTH*HEIGHT*LookupTable::PIXELELEMENTS];
    lut->makePColor(HEIGHT * WIDTH, A, pixelData);
    return QPixmap::fromImage(QImage((uchar *) pixelData, WIDTH, HEIGHT, QImage::Format_ARGB32));
}

LutIcon::LutIcon(const LookupTable *lut) : QIcon(LutIcon::pixmapFromLut(lut)) {
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
        addItem(*lutIcons[i], QString());
    }
    setIconSize(QSize(LutIcon::WIDTH, LutIcon::HEIGHT));
    setSizeAdjustPolicy(AdjustToContents);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    setCurrentIndex(defaultLUTIndex);
    setMinimumWidth(64);
}

void LookupTableSelector::resizeEvent(QResizeEvent *e) {
    setIconSize(QSize(size().width(), size().height()));
    QComboBox::resizeEvent(e);
}
