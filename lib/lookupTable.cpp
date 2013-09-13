#include "lookupTable.h"
#include <fstream>

#include "lutData.h"
#include <cassert>

bool LookupTable::lutmap_init = false;
map<string, LookupTable> LookupTable::lutmap;
map<string, LookupTable> LookupTable::lutmap_r;

LookupTable::LookupTable() {
    lut_r = &(lut[LUTROWS * READ_LUT_RED]);
    lut_g = &(lut[LUTROWS * READ_LUT_GREEN]);
    lut_b = &(lut[LUTROWS * READ_LUT_BLUE]);
    initialized = 0;
    _reverse = false;
}

void LookupTable::setData(const uint8_t lutData[]) {
    uint8_t *ir = lut_r, *ig = lut_g, *ib = lut_b;

    for(unsigned int i = 0; i < LUTROWS; i++) {
        *(ir++) = lutData[i * LUTCOLORS + READ_LUT_RED];
        *(ig++) = lutData[i * LUTCOLORS + READ_LUT_GREEN];
        *(ib++) = lutData[i * LUTCOLORS + READ_LUT_BLUE];
    }
    initialized = 1;
}

bool LookupTable::readData(const string& fileName) {
    ifstream file(fileName.c_str(), ios::in | ios::binary | ios::ate);
    if( !file.is_open() ) return false;
    unsigned int size = (unsigned int) file.tellg();
    file.seekg(0, ios::beg);
    if( size != LUTSIZE * sizeof(uint8_t) ) return false;
    file.read((char*)lut, size);
    file.close();
    initialized = true;
    return true;
}

void LookupTable::makePColor(const size_t N, const uint8_t TArray[], uint8_t PArray[]) const {
    assert(initialized);
    if(!_reverse) {
        for(size_t i=0; i<N; i++) {
            PArray[i*pixelSize() + LUT_ALPHA] = 255;
            PArray[i*pixelSize() + LUT_RED]   = lut_r[TArray[i]]; 
            PArray[i*pixelSize() + LUT_GREEN] = lut_g[TArray[i]];
            PArray[i*pixelSize() + LUT_BLUE]  = lut_b[TArray[i]];
        }
    }
    else {
        for(size_t i=0; i<N; i++) {
            PArray[i*pixelSize() + LUT_ALPHA] = 255;
            PArray[i*pixelSize() + LUT_RED]   = lut_r[255-TArray[i]]; 
            PArray[i*pixelSize() + LUT_GREEN] = lut_g[255-TArray[i]];
            PArray[i*pixelSize() + LUT_BLUE]  = lut_b[255-TArray[i]];
        }
    }
}

bool LookupTable::loadTable(const string& tableName) {
    for(int i=0; i<lut::NTables; i++) {
        if((string)lut::lookupTables[i].name == tableName) {
            setData((uint8_t*)lut::lookupTables[i].data);
            return true;
        }
    }
    return false;
}

const LookupTable& LookupTable::getLUT(const string &tableName, bool reversed) {
    if(!lutmap_init) loadAll();
    if(!reversed)
        return lutmap[tableName];
    else
        return lutmap_r[tableName];
}

const LookupTable& LookupTable::getLUT(const int iLUT, bool reversed) {
    assert(iLUT >=0 && iLUT < getNTables());
    return getLUT((string) getTableName(iLUT), reversed);
}

void LookupTable::loadAll() {
    LookupTable lut_p, lut_r;
    std::string lutName;
    for(int i=0; i<lut::NTables; i++) {
        lutName = lut::lookupTables[i].name;
        lut_p.loadTable(lutName);
        lut_r.loadTable(lutName);
        lut_r.setReverse(true);
        lutmap[string(lut::lookupTables[i].name)] = lut_p;
        lutmap_r[string(lut::lookupTables[i].name)] = lut_r;
    }
    lutmap_init = true;
}

int LookupTable::getNTables() {
    return lut::NTables;
}

const char* LookupTable::getTableName(const int i) {
    return lut::lookupTables[i].name;
}
