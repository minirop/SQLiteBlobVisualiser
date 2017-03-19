#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T14:01:12
#
#-------------------------------------------------

QT = core

TARGET = base64
TEMPLATE = lib
CONFIG += plugin

DEFINES += BASE64_LIBRARY

SOURCES += base64.cpp

INCLUDEPATH += ../../application/include
HEADERS +=\
    base64.h \
    base64_global.h \
    ../../application/include/blobinterface.h

DESTDIR = ../../bin/plugins
