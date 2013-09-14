#ifndef LOOKUPTABLESELECTOR_H
#define LOOKUPTABLESELECTOR_H

#include <QComboBox>
#include <QPixmap>
#include <QIcon>
#include <QImage>

#include <string>
#include <map>

#include "lookupTable.h"

namespace luticon {

class LutIcon : public QIcon {
    static QPixmap pixmapFromLut(const LookupTable* lut);

public:
    explicit LutIcon(const LookupTable* lut);

    static const int WIDTH = LookupTable::LUTROWS;
    static const int HEIGHT = 14;

};

}

class LookupTableSelector : public QComboBox
{
    Q_OBJECT

    static bool initialized;
    static std::map<int, const LookupTable*> luts;
    static std::map<int, const luticon::LutIcon*> lutIcons;
    static const string defaultLUTName;
    static int defaultLUTIndex;

    static void loadLookupTables();


public:
    explicit LookupTableSelector(QWidget *parent = 0);
    virtual QSize sizeHint() const { return QSize(luticon::LutIcon::WIDTH,
                                    luticon::LutIcon::HEIGHT); }
    void resizeEvent(QResizeEvent *e);

signals:

public slots:

};

#endif // LOOKUPTABLESELECTOR_H
