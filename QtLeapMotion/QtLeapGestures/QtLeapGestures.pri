#/****************************************************************************
#**
#** Copyright (C) Paul Lemire
#** Contact: paul.lemire@epitech.eu
#**
#**
#** GNU Lesser General Public License Usage
#** This file may be used under the terms of the GNU Lesser
#** General Public License version 2.1 as published by the Free Software
#** Foundation and appearing in the file LICENSE.LGPL included in the
#** packaging of this file.  Please review the following information to
#** ensure the GNU Lesser General Public License version 2.1 requirements
#** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#**
#** GNU General Public License Usage
#** Alternatively, this file may be used under the terms of the GNU
#** General Public License version 3.0 as published by the Free Software
#** Foundation and appearing in the file LICENSE.GPL included in the
#** packaging of this file.  Please review the following information to
#** ensure the GNU General Public License version 3.0 requirements will be
#** met: http://www.gnu.org/copyleft/gpl.html.
#**
#**
#****************************************************************************/

SOURCES += $$PWD/QtLeapCircleGesture.cpp \
           $$PWD/QtLeapKeyTapGesture.cpp \
           $$PWD/QtLeapScreenTapGesture.cpp \
           $$PWD/QtLeapSwipeGesture.cpp \
           $$PWD/QtLeapTapGesture.cpp \
           $$PWD/Handlers/DefaultQtLeapTapGestureHandler.cpp \
           $$PWD/Handlers/DefaultQtLeapCircleGestureHandler.cpp \
           $$PWD/Handlers/DefaultQtLeapSwipeGestureHandler.cpp \
           $$PWD/Qml/SwipeLeapGestureArea.cpp \
           $$PWD/Qml/CircleLeapGestureArea.cpp \
           $$PWD/Qml/ScreenTapLeapGestureArea.cpp \
           $$PWD/Qml/KeyTapLeapGestureArea.cpp \
           $$PWD/Qml/AbstractGestureArea.cpp


HEADERS += $$PWD/QtLeapCircleGesture.h \
           $$PWD/QtLeapGesture.h \
           $$PWD/QtLeapKeyTapGesture.h \
           $$PWD/QtLeapScreenTapGesture.h \
           $$PWD/QtLeapSwipeGesture.h \
           $$PWD/QtLeapTapGesture.h \
           $$PWD/Handlers/QtLeapGestureHandlerInterface.h \
           $$PWD/Handlers/DefaultQtLeapTapGestureHandler.h \
           $$PWD/Handlers/DefaultQtLeapCircleGestureHandler.h \
           $$PWD/Handlers/DefaultQtLeapSwipeGestureHandler.h \
           $$PWD/Listeners/QtLeapGestureListenerInterface.h \
           $$PWD/Qml/SwipeLeapGestureArea.h \
           $$PWD/Qml/CircleLeapGestureArea.h \
           $$PWD/Qml/ScreenTapLeapGestureArea.h \
           $$PWD/Qml/KeyTapLeapGestureArea.h \
           $$PWD/Qml/AbstractGestureArea.h

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Qml
INCLUDEPATH += $$PWD/Listeners
INCLUDEPATH += $$PWD/Handlers
