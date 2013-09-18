#-------------------------------------------------
#
# Project created by QtCreator 2013-09-08T18:45:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../ncImager
TEMPLATE = app
LIBS += -L../lib -lncpcolor
INCLUDEPATH += ../lib

SOURCES += main.cpp\
        mainwindow.cpp \
    fixedAspectLabel.cpp \
    imageScrollArea.cpp \
    imageWindow.cpp \
    fileWindow.cpp \
    lookupTableSelector.cpp \
    ncImagerSettings.cpp \
    fileObject.cpp

HEADERS  += mainwindow.h \
    fixedAspectLabel.h \
    imageScrollArea.h \
    imageWindow.h \
    fileWindow.h \
    lookupTableSelector.h \
    ncImagerSettings.h \
    fileObject.h \
    common.h


include(../ncImager.pri)
