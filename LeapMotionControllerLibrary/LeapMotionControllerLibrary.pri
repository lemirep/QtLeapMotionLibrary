

SOURCES += $$PWD/LeapMotionController.cpp \
           $$PWD/LeapMotionListener.cpp \
           $$PWD/LeapMotionTouchDevice.cpp

HEADERS += $$PWD/LeapMotionController.h \
           $$PWD/LeapMotionListener.h \
           $$PWD/LeapMotionTouchDevice.h


INCLUDEPATH += $$PWD/Leap/include
INCLUDEPATH += $$PWD

win32: {
 !contains(QMAKE_HOST.arch, x86_64) {
        message("x86 build")
        LIBS += $$PWD/Leap/x86/Leap.lib
        install_folder.files += $$PWD/Leap/x86/Leap.dll
    } else {
        message("x86_64 build")

#        LIBS += ./Leap/x64/Leapd.lib
        LIBS += $$PWD/Leap/x64/Leap.lib
        install_folder.files += $$PWD/Leap/x64/Leap.dll
#        install_folder.files += ./Leap/x64/Leapd.dll
    }
}

linux-g++-32 {
    LIBS += $$PWD/Leap/x86/libLeap.so
    install_folder.files += $$LIBS
}

linux-g++-64 {
    LIBS += $$PWD/Leap/x64/libLeap.so
    install_folder.files += $$LIBS
}

install_folder.path = .

# Copy LeapMotion Lib to executable path

INSTALLS += install_folder
DEPLOYMENT += install_folder
