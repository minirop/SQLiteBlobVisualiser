SOURCES += \
    src/main.cpp \
    src/variantdialog.cpp \
    src/sqlitequerymodel.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/blobinterface.h \
    include/variantdialog.h \
    include/sqlitequerymodel.h \
    include/mainwindow.h

INCLUDEPATH += include
QT += widgets sql
DESTDIR = ../bin
TARGET = SQLiteBlobVisualiser
