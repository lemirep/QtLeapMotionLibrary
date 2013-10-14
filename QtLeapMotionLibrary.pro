
QT += qml
QT += quick

OBJECTS_DIR = tmp

MOC_DIR = tmp

SOURCES += main.cpp \
          LeapMotionQQuickView.cpp

HEADERS += LeapMotionQQuickView.h

OTHER_FILES += main.qml

linux : {
    QMAKE_LFLAGS += -Wl,--rpath=$$PWD
    QMAKE_RPATH=
}

win32:DESTDIR = ./

include(LeapMotionControllerLibrary/LeapMotionControllerLibrary.pri)
include(LeapGestureArea/LeapGestureArea.pri)
