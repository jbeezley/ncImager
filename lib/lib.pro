#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T23:18:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = ncpcolor
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=  \
    lookupTable.cpp \
    ncFileReader.cpp \
    ncvalues.cpp \
    netcdf.cpp

HEADERS += \
    lookupTable.h \
    lutData.h \
    ncFileReader.h \
    ncvaluesCompat.h \
    netcdfCompat.h \
    norm.h \
    luts/gist_rainbow.h \
    luts/gist_earth.h \
    luts/gist_stern.h \
    luts/cubehelix.h \
    luts/gist_gray.h \
    luts/gist_heat.h \
    luts/gist_ncar.h \
    luts/gist_yarg.h \
    luts/coolwarm.h \
    luts/gnuplot2.h \
    luts/Spectral.h \
    luts/gnuplot.h \
    luts/Oranges.h \
    luts/Pastel1.h \
    luts/Pastel2.h \
    luts/Purples.h \
    luts/rainbow.h \
    luts/seismic.h \
    luts/terrain.h \
    luts/Accent.h \
    luts/afmhot.h \
    luts/autumn.h \
    luts/binary.h \
    luts/CMRmap.h \
    luts/copper.h \
    luts/Greens.h \
    luts/Paired.h \
    luts/PuBuGn.h \
    luts/RdYlBu.h \
    luts/RdYlGn.h \
    luts/spring.h \
    luts/summer.h \
    luts/winter.h \
    luts/YlGnBu.h \
    luts/YlOrBr.h \
    luts/YlOrRd.h \
    luts/Blues.h \
    luts/Dark2.h \
    luts/Greys.h \
    luts/ocean.h \
    luts/prism.h \
    luts/bone.h \
    luts/BrBG.h \
    luts/BuGn.h \
    luts/BuPu.h \
    luts/cool.h \
    luts/flag.h \
    luts/GnBu.h \
    luts/gray.h \
    luts/OrRd.h \
    luts/pink.h \
    luts/PiYG.h \
    luts/PRGn.h \
    luts/PuBu.h \
    luts/PuOr.h \
    luts/PuRd.h \
    luts/RdBu.h \
    luts/RdGy.h \
    luts/RdPu.h \
    luts/Reds.h \
    luts/Set1.h \
    luts/Set2.h \
    luts/Set3.h \
    luts/YlGn.h \
    luts/brg.h \
    luts/bwr.h \
    luts/hot.h \
    luts/hsv.h \
    luts/jet.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

include(../ncImager.pri)
