#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T14:01:12
#
#-------------------------------------------------

TARGET = pixmap
TEMPLATE = lib
CONFIG += plugin

DEFINES += PIXMAP_LIBRARY

SOURCES += pixmap.cpp

INCLUDEPATH += ../../application/include
HEADERS += \
    pixmap.h\
    pixmap_global.h \
    ../../application/include/blobinterface.h

DESTDIR = ../../bin/plugins
