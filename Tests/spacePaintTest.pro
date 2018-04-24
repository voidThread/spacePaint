QT += core gui widgets testlib

DEFINES += UNIT_TESTS

SOURCES += \
    PaintViewWidgetTest.cpp \
    ../PaintViewWidget/PaintViewWidget.cpp

HEADERS += \
    ../PaintViewWidget/PaintViewWidget.h

# install
target.path = Tests
INSTALLS += target
