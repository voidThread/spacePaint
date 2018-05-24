#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T00:05:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spacePaint
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    GlobalNames.cpp \
    MainWindow/MainWindow.cpp \
    PaintViewWidget/PaintViewWidget.cpp \
    MdiChild/MdiChild.cpp \
    PaintToolsPalette/PaintToolsPalette.cpp \
    NewFileDialog/NewFileDialog.cpp

HEADERS += \
    GlobalNames.h \
    MainWindow/MainWindow.h \
    PaintViewWidget/PaintTool.h \
    PaintViewWidget/PaintViewWidget.h \
    MdiChild/MdiChild.h \
    PaintToolsPalette/PaintToolsPalette.h \
    NewFileDialog/NewFileDialog.h

FORMS += \
    MainWindow/MainWindow.ui \
    PaintToolsPalette/PaintToolsPalette.ui \
    NewFileDialog/NewFileDialog.ui

RESOURCES += \
    resources.qrc
